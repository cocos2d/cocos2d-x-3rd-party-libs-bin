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

#ifndef AKI_JS_FUNCTION_H
#define AKI_JS_FUNCTION_H

#include "aki/logging/logging.h"
#include "aki/callback/napi/safety_callback.h"

namespace aki {
class JSFunction {
public:
    JSFunction(napi_env env, napi_value cb)
        : ctx_(std::make_shared<ThreadSafeContext>(env, cb))
    { }

    template<typename R, typename... P>
    R Invoke (P... args) const
    {
        ctx_->forwardCallJs = SafetyCallback<R (P...)>::CallJs;
        return(ctx_->template Invoke<R, P...>(std::move(args)...));
    }

private:
    std::shared_ptr<ThreadSafeContext> ctx_;
};
} // namespace aki
#endif //AKI_JS_FUNCTION_H
