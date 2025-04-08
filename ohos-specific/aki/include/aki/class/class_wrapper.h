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

#ifndef AKI_CLASS_WRAPPER_H
#define AKI_CLASS_WRAPPER_H

#include <memory>
#include <unordered_map>
#include <node_api.h>

#include "aki/config.h"
#include "aki/type/type_flag.h"
#include "aki/logging/logging.h"

namespace aki {

class AKI_EXPORT ClassWrapperBase {
public:
    ClassWrapperBase(void* obj, TypeFlag flag);
    ~ClassWrapperBase() = default;

protected:
    void* unsafeObj_;

    TypeFlag flag_;
};

template <class C>
class ClassWrapper : public ClassWrapperBase {
public:
    ClassWrapper(C *instance, TypeFlag flag)
        : ClassWrapperBase(instance, flag) { }
    ClassWrapper(std::shared_ptr<C> instance, TypeFlag flag)
        : ClassWrapperBase(instance.get(), flag), nativeObj_(instance) { }

    ~ClassWrapper()
    {
        AKI_DLOG(DEBUG) << "~ClassWrapper unsafe obj: " << unsafeObj_;
        if (flag_ == TypeFlag::IS_SHARED_PTR) {
            AKI_DLOG(DEBUG) << "~ClassWrapper SHARED_PTR use count : " << nativeObj_.use_count();
        }
    }

    template<typename... Args>
    static void ConstructorWrapper(napi_env env, napi_value jsThis, Args&&... args)
    {
        (new ClassWrapper(std::make_shared<C>(std::forward<Args>(args)...),
                          TypeFlag::IS_SHARED_PTR
        ))->WrapThis(env, jsThis);

        return;
    }

    static napi_value ExternalWrapper(napi_env env, napi_callback_info info)
    {
        napi_status status;
        napi_value jsThis;
        size_t argc = 2;
        napi_value args[2];
        status = napi_get_cb_info(env, info, &argc, args, &jsThis, nullptr);
        AKI_DCHECK(status == napi_ok);

        C* instance = nullptr;
        status = napi_get_value_external(env, args[0], ((void**)&instance));
        AKI_DCHECK(status == napi_ok);

        uint32_t result;
        status = napi_get_value_uint32(env, args[1], &result);
        TypeFlag flag = static_cast<TypeFlag>(result);

        ClassWrapper* wrapperObj = nullptr;
        if (flag == TypeFlag::IS_SHARED_PTR) {
            std::shared_ptr<C> sharedPtr;
            sharedPtr.reset(instance);
            wrapperObj = new ClassWrapper(sharedPtr, flag);
        } else {
            wrapperObj = new ClassWrapper(instance, flag);
        }
        wrapperObj->WrapThis(env, jsThis);

        return jsThis;
    }

    void WrapThis(napi_env env, napi_value jsThis)
    {
        napi_status status;
        status = napi_wrap(env,
                           jsThis,
                           this,
                           DestroyInstance,
                           nullptr,  // finalize_hint
                           nullptr);
        AKI_DCHECK(status == napi_ok);

        AKI_DLOG(DEBUG) << "ClassWrapperBase wrap obj: " << this;
    }

    static C* UnWrapper(napi_env env, napi_value jsThis)
    {
        napi_status status;
        ClassWrapper* wrapperObj = nullptr;
        status = napi_unwrap(env, jsThis, reinterpret_cast<void**>(&wrapperObj));
        AKI_DCHECK(status == napi_ok);
        AKI_DLOG(DEBUG) << "ClassWrapperBase unwrap obj: " << wrapperObj->unsafeObj_;

        return reinterpret_cast<C*>(wrapperObj->unsafeObj_);
    }

    static std::shared_ptr<C>* GetShared(napi_env env, napi_value jsThis)
    {
        napi_status status;
        ClassWrapper* wrapperObj = nullptr;
        status = napi_unwrap(env, jsThis, reinterpret_cast<void**>(&wrapperObj));
        AKI_DCHECK(status == napi_ok);

        return &(wrapperObj->nativeObj_);
    }

private:
    static void DestroyInstance(napi_env env, void* nativeInstance, void* finalize_hint)
    {
        AKI_DLOG(DEBUG) << "ClassWrapperBase destroy obj: " << nativeInstance;
        delete reinterpret_cast<ClassWrapper*>(nativeInstance);
    }

    std::shared_ptr<C> nativeObj_;
};
} // namespace aki
#endif //AKI_CLASS_WRAPPER_H
