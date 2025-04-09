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

#ifndef AKI_ARG_STORAGE_H
#define AKI_ARG_STORAGE_H

namespace aki {

class ArgStorage {
public:
    ArgStorage(uint32_t overloadId)
        : overloadId_(overloadId) {}

    virtual ~ArgStorage() = default;

    uint32_t GetOverloadGroupId() const { return(overloadId_); }

    virtual void* GetTemplate() = 0;

private:
    const uint32_t overloadId_;

};

template <typename C>
class TemplatedArgStorage : public ArgStorage {
public:
    TemplatedArgStorage(uint32_t overloadId)
        : ArgStorage(overloadId),
          data_(nullptr) {}

    ~TemplatedArgStorage()
    {
        if(data_)
            delete data_;
    }

    void* GetTemplate() override { return this; }

    template <typename... Args>
    void Init(Args&&... args)
    {
        data_ = new C(std::forward<Args>(args)...);
    }

    C* TaskClass()
    {
        C* temp = data_;
        data_ = nullptr;
        return temp;
    }

private:
    C* data_;
};
} // namespace aki
#endif //AKI_ARG_STORAGE_H
