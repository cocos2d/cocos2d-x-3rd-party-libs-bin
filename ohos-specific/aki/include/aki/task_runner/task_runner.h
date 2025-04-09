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

#ifndef AKI_TASK_RUNNER_H
#define AKI_TASK_RUNNER_H

#include <node_api.h>
#include <uv.h>
#include <unordered_map>
#include <functional>

#include "aki/config.h"

namespace aki {
class AKI_EXPORT TaskRunner {
public:
    using Closure = std::function<void ()>;

    static const TaskRunner* Create(std::string taskName);

    static void PostTask(const std::string& taskName, Closure task);

    void PostTask(Closure task) const;
private:
    struct Context {
        Context(napi_env env, Closure task) : env(env), task(task) {}

        napi_env env;

        Closure task;
    };
    
    TaskRunner(napi_env env);

    static std::unordered_map<std::string, std::unique_ptr<TaskRunner>> runners;

    napi_env env_;

    uv_loop_s* loop_;
};

} // namespace aki
#endif // AKI_TASK_RUNNER_H
