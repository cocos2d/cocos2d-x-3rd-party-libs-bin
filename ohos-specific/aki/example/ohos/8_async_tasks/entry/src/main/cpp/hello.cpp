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
#include <aki/jsbind.h>

struct TaskRunnerData {
    TaskRunnerData() = default;
    TaskRunnerData(std::string name) : name(name) {}
    std::string name;
};

JSBIND_CLASS(TaskRunnerData) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_PROPERTY(name);
}

class TaskRunner {
public:
    TaskRunner() = default;
    int DoTask() {
        AKI_LOG(INFO) << "DoTask";
        return 1;
    }
    void DoTaskReturnVoid() {
        return;
    }
    TaskRunnerData DoTaskReturnData() {
        AKI_LOG(INFO) << "DoTaskReturnData";
        return TaskRunnerData("aki");
    }
};

JSBIND_CLASS(TaskRunner) {
    JSBIND_CONSTRUCTOR<>();
    JSBIND_PMETHOD(DoTask);
    JSBIND_PMETHOD(DoTaskReturnVoid);
    JSBIND_PMETHOD(DoTaskReturnData);
}

void AsyncTaskReturnVoid() {}

long AsyncTaskLongReturnLong(long num) { return num; }

long AsyncTaskLongLongFunctionReturnLong(long min, long max, std::function<long (long, long, char *)> f) {
    return f(min, max, "aki from c++");
}

JSBIND_GLOBAL() {
    JSBIND_PFUNCTION(AsyncTaskReturnVoid);
    JSBIND_PFUNCTION(AsyncTaskLongReturnLong);
    JSBIND_PFUNCTION(AsyncTaskLongLongFunctionReturnLong);
}
JSBIND_ADDON(async_tasks);