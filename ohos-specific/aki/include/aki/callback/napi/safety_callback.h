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

#ifndef AKI_SAFETY_CALLBACK_H
#define AKI_SAFETY_CALLBACK_H

#include <node_api.h>
#include <future>
#include <thread>

#include "aki/config.h"
#include "aki/callback/napi/callback.h"
#include "aki/logging/logging.h"

namespace aki {
struct ThreadSafeContext {
    template<typename R, typename... P>
    struct Data {
        std::tuple<typename ValueDefiner<P>::RawType...> params;

        std::promise<R> result;
    };

    ThreadSafeContext(const napi_env env,
                      const napi_value cb)
        : env(env), mainId_(std::this_thread::get_id())
    {
        napi_status status;
        napi_value workName;

        status = napi_create_string_utf8(env,
                                         "JSBind Thread-safe Call from Async Work Item",
                                         NAPI_AUTO_LENGTH,
                                         &workName);
        AKI_DCHECK(status == napi_ok) << "status: " << status;

        status = napi_create_threadsafe_function(env,
                                                 cb,
                                                 nullptr,
                                                 workName,
                                                 0,
                                                 1,
                                                 nullptr,
                                                 FinalizeThreadsafeFunction,
                                                 this,
                                                 CallJs,
                                                 &(ts));
        AKI_DCHECK(status == napi_ok) << "status: " << status;

        status = napi_create_reference(env,
                                       cb,
                                       1,
                                       &cbRef);
        AKI_DCHECK(status == napi_ok) << "status: " << status;
    }

    ~ThreadSafeContext()
    {
        napi_status status = napi_release_threadsafe_function(ts,
                                                              napi_tsfn_release);
        AKI_DCHECK(status == napi_ok) << "status: " << status;
        status = napi_delete_reference(env, cbRef);
        AKI_DCHECK(status == napi_ok) << "status: " << status;
    }

    template<typename R, typename... P>
    R Invoke(P&&... args) const
    {
        napi_status status;

        if (std::this_thread::get_id() == mainId_) {
            napi_value cb;
            AKI_DCHECK(cbRef != nullptr);
            status = napi_get_reference_value(env, cbRef, &cb);
            AKI_DCHECK(status == napi_ok) << "status: " << status;

            Callback<R (P...)> jsCallback(env, cb);
            return jsCallback(std::forward<P>(args)...);
        } else {
            Data<R, P...> data = {
                .params = std::make_tuple(std::forward<P>(args)...),
                .result = {}
            };

            Invoke(&data);

            return data.result.get_future().get();
        }
    }

    void Invoke(void* data) const
    {
        napi_status status;

        status = napi_acquire_threadsafe_function(ts);
        AKI_DCHECK(status == napi_ok) << "status: " << status;

        status = napi_call_threadsafe_function(ts,
                                               data,
                                               napi_tsfn_blocking);
        AKI_DCHECK(status == napi_ok) << "status: " << status;
    }

    const napi_env env;

    napi_ref cbRef = nullptr;

    napi_threadsafe_function ts = nullptr;

    std::thread::id mainId_;

    void (*forwardCallJs)(napi_env env, napi_value cb, void* data) = nullptr;

private:
    static void FinalizeThreadsafeFunction(napi_env env, void* raw, void* hint)
    {
        AKI_DLOG(DEBUG) << "FinalizeThreadsafeFunction";
    }

    static void CallJs(napi_env env, napi_value noUsed, void* context, void* data)
    {
        AKI_DCHECK(context != nullptr);
        napi_status status;
        ThreadSafeContext* ctx = (ThreadSafeContext*)(context);

        napi_value cb;
        AKI_DCHECK(ctx->cbRef != nullptr);
        status = napi_get_reference_value(env, ctx->cbRef, &cb);
        AKI_DCHECK(status == napi_ok) << "status: " << status;

        AKI_DCHECK(ctx->forwardCallJs != nullptr);
        return ctx->forwardCallJs(env, cb, data);
    }
};

template<typename T>
class SafetyCallback;

template<typename R, typename... P>
class SafetyCallback<R (P...)> {
public:
    explicit SafetyCallback(const napi_env env, const napi_value cb)
        : ctx_(std::make_shared<ThreadSafeContext>(env, cb))
    {
        ctx_->forwardCallJs = CallJs;
    }

    // 禁止调用方法时，阻塞JS线程，否则会导致进程挂死。
    R operator() (P... args) const
    {
        return(ctx_->template Invoke<R, P...>(std::move(args)...));
    }

    static void CallJs(napi_env env, napi_value cb, void* recvData)
    {
        AKI_DCHECK(env != nullptr);
        AKI_DCHECK(cb != nullptr);
        AKI_DCHECK(recvData != nullptr);

        ThreadSafeContext::Data<R, P...>* data = (ThreadSafeContext::Data<R, P...>*)recvData;
        return ForwardCallJs(env, cb, data, std::make_index_sequence<sizeof...(P)>());
    }

private:
    template<size_t... I>
    static void ForwardCallJs(napi_env env, napi_value cb, ThreadSafeContext::Data<R, P...>* data, std::index_sequence<I...>)
    {
        Callback<R (P...)> jsCallback(env, cb);

        napi_status status;
        napi_handle_scope scope;
        status = napi_open_handle_scope(env, &scope);
        AKI_DCHECK(status == napi_ok) << "status: " << status;

        if constexpr(std::is_void<R>::value) {
            jsCallback(std::get<I>(data->params)...);
            data->result.set_value();
        } else {
            R r = jsCallback(std::get<I>(data->params)...);
            data->result.set_value(r);
        }
        
        status = napi_close_handle_scope(env, scope);
        AKI_DCHECK(status == napi_ok) << "status: " << status;
        return;
    }

    std::shared_ptr<ThreadSafeContext> ctx_;
};

} // namespace aki
#endif //AKI_SAFETY_CALLBACK_H
