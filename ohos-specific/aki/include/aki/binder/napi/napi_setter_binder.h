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

#ifndef AKI_NAPI_SETTER_BINDER_H
#define AKI_NAPI_SETTER_BINDER_H
#include "aki/binder/setter_binder.h"

namespace aki {

template <typename C, typename M, typename R, typename P>
class NapiSetterBinder : public SetterBinder<NapiSetterBinder<C, M, R, P>, C, M, R, P> {
public:
    typedef SetterBinder<NapiSetterBinder<C, M, R, P>, C, M, R, P> ParentType;

    static napi_value Wrapper (napi_env env, napi_callback_info info)
    {
        AKI_DLOG(DEBUG) << "NapiSetterBinder::Wrapper";
        return SafetyWrapper(env, info);
    }

private:
    static napi_value SafetyWrapper(napi_env& env, napi_callback_info info)
    {
        napi_status status;
        aki::BindInfo* bindInfo = nullptr;
        napi_value jsThis;
        size_t argc = 1; /// 默认set访问器只有一个入参
        napi_value args[1];
        status = napi_get_cb_info(env, info, &argc, args, &jsThis, ((void**)&bindInfo));
        AKI_DCHECK(status == napi_ok);
        AKI_DCHECK(bindInfo != nullptr);

        /// 获取ClassType对象实例
        C* receiver = ClassWrapper<C>::UnWrapper(env, jsThis);

        auto tuple = std::make_tuple(NapiValueMaker<typename ValueDefiner<P>::RawType>(env, args[0]));
        std::array<internal::Value*, 1> result = { static_cast<internal::Value*>(std::get<0>(tuple))};

        return WrapperForward(env, bindInfo, receiver, result.data());
    }

    static napi_value WrapperForward(napi_env& env, aki::BindInfo* bindInfo, C* receiver, internal::Value* values[])
    {
        ParentType::InnerWrapper(*receiver, bindInfo, NapiValueTrait<P>::Cast(*values[0]));
        return nullptr;
    }
};
} // namespace aki
#endif //AKI_NAPI_SETTER_BINDER_H
