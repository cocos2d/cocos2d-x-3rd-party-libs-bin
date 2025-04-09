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

#ifndef AKI_NAPI_GETTER_BINDER_H
#define AKI_NAPI_GETTER_BINDER_H
#include "aki/binder/getter_binder.h"

namespace aki {

template <typename C, typename M, typename R>
class NapiGetterBinder : public GetterBinder<NapiGetterBinder<C, M, R>, C, M, R> {
public:
    typedef GetterBinder<NapiGetterBinder<C, M, R>, C, M, R> ParentType;

    static napi_value Wrapper (napi_env env, napi_callback_info info)
    {
        AKI_DLOG(DEBUG) << "NapiGetterBinder::Wrapper";
        return SafetyWrapper(env, info);
    }

private:
    static napi_value SafetyWrapper(napi_env& env, napi_callback_info info)
    {
        napi_status status;
        aki::BindInfo* bindInfo = nullptr;
        napi_value jsThis;
        size_t argc = 0; /// 默认get访问器无入参
        status = napi_get_cb_info(env, info, &argc, NULL, &jsThis, ((void**)&bindInfo));
        AKI_DCHECK(status == napi_ok);
        AKI_DCHECK(bindInfo != nullptr);

        /// 获取ClassType对象实例
        C* receiver = ClassWrapper<C>::UnWrapper(env, jsThis);

        AKI_DLOG(DEBUG) << "NapiGetterBinder::SafetyWrapper: " << receiver;
        return WrapperForward(env, bindInfo, receiver);
    }

    static napi_value WrapperForward(napi_env& env, aki::BindInfo* bindInfo, C* receiver)
    {
        return NapiValue<R>::ToNapiValue(env, ParentType::InnerWrapper(*receiver, bindInfo));
    }
};
} // namespace aki
#endif //AKI_NAPI_GETTER_BINDER_H
