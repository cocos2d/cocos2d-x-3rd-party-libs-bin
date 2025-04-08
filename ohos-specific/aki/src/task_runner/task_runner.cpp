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

#include "aki/task_runner/task_runner.h"
#include "aki/logging/logging.h"
#include "status/status.h"
#include "aki/binding.h"

namespace aki {

std::unordered_map<std::string, std::unique_ptr<TaskRunner>> TaskRunner::runners;

// | static |
const TaskRunner* TaskRunner::Create(std::string taskName)
{
    napi_env env = Binding::GetScopedEnv();
    AKI_DCHECK(env != nullptr) << "should be created at js thread.";
    std::unique_ptr<TaskRunner> taskRunner;
    taskRunner.reset(new TaskRunner(env));
    runners[taskName] = std::move(taskRunner);

    return runners[taskName].get();
}

// | static |
void TaskRunner::PostTask(const std::string& taskName, Closure task)
{
    return runners[taskName].get()->PostTask(std::move(task));
}

TaskRunner::TaskRunner(napi_env env) : env_(env)
{
    napi_status status;
    status = napi_get_uv_event_loop(env_, &loop_);
    AKI_DCHECK(status == napi_ok) << "status(" << status << "): " << GetStatusDesc(status);
}

void TaskRunner::PostTask(Closure task) const
{
    uv_work_t* work = new uv_work_t;
    auto context = new Context(env_, task);

    work->data = context;
    uv_queue_work(loop_,
                  work,
                  [] (uv_work_t* work) {},
                  [] (uv_work_t* work, int status) {
                    Context* ctx = static_cast<Context*>(work->data);
                    ctx->task();

                    delete ctx;
                    delete work;
                  });
}
} // namespace aki
