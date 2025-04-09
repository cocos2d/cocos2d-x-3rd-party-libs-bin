/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AKI_NAPI_PMETHOD_BINDER_H
#define AKI_NAPI_PMETHOD_BINDER_H
#include "aki/binder/method_binder.h"
#include "aki/config.h"

namespace aki {

template <typename C, typename M, typename R, typename... P>
class NapiPMethodBinder : public MethodBinder<NapiPMethodBinder<C, M, R, P...>, C, M, R, P...> {
public:
    typedef MethodBinder<NapiPMethodBinder<C, M, R, P...>, C, M, R, P...> ParentType;

    static napi_value Wrapper (napi_env env, napi_callback_info info)
    {
        AKI_DLOG(DEBUG) << "NapiPMethodBinder::Wrapper";
        if (!Checker<P...>::IsArityValid(env, info)) {
            std::string msg = std::string("JSBind: Wrong number of arguments, expected: ").append(std::to_string(sizeof...(P)));
            napi_throw_error(env, nullptr, msg.c_str());
            return nullptr;
        }
        if (!Checker<typename ValueDefiner<P>::RawType...>::TypesAreValid(env, info)) {
            std::string msg = Checker<typename ValueDefiner<P>::RawType...>::GetTypeError(env, info);
            napi_throw_type_error(env, "JSBind: Wrong type of arguments", msg.c_str());
            return nullptr;
        }
        return SafetyWrapper(env, info, std::make_index_sequence<sizeof...(P)>());
    }

private:
    struct InvokeWorkInfo {
        // napi work
        napi_async_work worker;
        // napi deferred
        napi_deferred deferred;

        C* receiver;

        aki::BindInfo* bindInfo;

        std::tuple<typename ValueDefiner<P>::RawType...> params;
    };
    
    struct InvokeWorkWithReturnInfo : public InvokeWorkInfo {

        R result;
    };

    template<size_t... Index>
    static napi_value SafetyWrapper(napi_env env, napi_callback_info info, std::index_sequence<Index...>)
    {
        napi_status status;
        aki::BindInfo* bindInfo = nullptr;
        size_t argc = sizeof...(Index);
        napi_value jsThis;

        std::array<napi_value, sizeof...(Index)> args;
        status = napi_get_cb_info(env, info, &argc, args.data(), &jsThis, ((void**)&bindInfo));
        AKI_DCHECK(status == napi_ok);
        AKI_DCHECK(bindInfo != nullptr);
        auto tuple = std::make_tuple(NapiValueMaker<typename ValueDefiner<P>::RawType>(env, args[Index])...);
        auto valueTuple = std::make_tuple(NapiValueTrait<typename ValueDefiner<P>::RawType>::Cast(std::get<Index>(tuple))...);

        /// 获取ClassType对象实例
        C* receiver = ClassWrapper<C>::UnWrapper(env, jsThis);

        // 异步执行
        struct InvokeWorkInfo* workData = nullptr;
        
        if constexpr (std::is_void<R>::value) {
            workData = new(std::nothrow) InvokeWorkInfo;
        } else {
            workData = new(std::nothrow) InvokeWorkWithReturnInfo;
        }

        workData->receiver = receiver;
        workData->bindInfo = bindInfo;
        workData->params = valueTuple;

        return AsyncForward(env, workData);

    }

    static napi_value AsyncForward(napi_env env, InvokeWorkInfo* workData)
    {
        napi_status status;
        napi_value promise;
        napi_value workName;
        status = napi_create_promise(env, &workData->deferred, &promise);
        AKI_DCHECK(status == napi_ok);
        status = napi_create_string_utf8(env, "JSBind Deferred Promise from Async Work Item", NAPI_AUTO_LENGTH, &workName);
        AKI_DCHECK(status == napi_ok);
        status = napi_create_async_work(env,
                               nullptr,
                               workName,
                               AsyncInvokeWork,
                               AsyncInvokeDone,
                               (void*) workData,
                               &workData->worker);
        AKI_DCHECK(status == napi_ok);
        status = napi_queue_async_work(env, workData->worker);
        AKI_DCHECK(status == napi_ok);

        return promise;
    }

    // native方法调用 子线程任务
    static void AsyncInvokeWork(napi_env env, void *data)
    {
        AKI_DCHECK(data != nullptr);
        struct InvokeWorkInfo *arg = (struct InvokeWorkInfo *)data;

        if constexpr (std::is_void<R>::value) {
            WrapperForward(arg, std::make_index_sequence<sizeof...(P)>());
        } else {
            InvokeWorkWithReturnInfo *info = static_cast<InvokeWorkWithReturnInfo *>(arg);
            info->result = WrapperForward(info, std::make_index_sequence<sizeof...(P)>());
        }
    }

    // native方法调用 结果回调 回到主线程
    static void AsyncInvokeDone(napi_env env, napi_status status, void *data)
    {
        AKI_DCHECK(status == napi_ok);
        AKI_DCHECK(data != nullptr);
        struct InvokeWorkInfo *arg = (struct InvokeWorkInfo *)data;

        napi_value result = nullptr;
        // 失败调用返回错误码
        if constexpr (!std::is_void<R>::value) {
            InvokeWorkWithReturnInfo *info = static_cast<InvokeWorkWithReturnInfo *>(arg);
            result = NapiValue<R>::ToNapiValue(env, std::forward<R>(info->result));
        }

        if (!result) {
            napi_get_undefined(env, &result);
        }

        status = napi_resolve_deferred(env, arg->deferred, result);
        AKI_DCHECK(status == napi_ok);
        status = napi_delete_async_work(env, arg->worker);
        AKI_DCHECK(status == napi_ok);
        arg->deferred = nullptr;
        delete arg;
    }

    template<size_t... Index>
    static R WrapperForward(struct InvokeWorkInfo *arg, std::index_sequence<Index...>)
    {
        C* receiver = arg->receiver;
        aki::BindInfo* bindInfo = arg->bindInfo;
        std::tuple<typename ValueDefiner<P>::RawType...>& params = arg->params;
        return ParentType::InnerWrapper(*receiver, bindInfo, std::get<Index>(params)...);
    }
};

} // namespace aki
#endif //AKI_NAPI_PMETHOD_BINDER_H
