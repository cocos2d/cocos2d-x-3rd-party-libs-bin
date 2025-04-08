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

#ifndef AKI_OVERLOADER_TEST_H
#define AKI_OVERLOADER_TEST_H

#include <string>

class OverloaderTest {
public:
    OverloaderTest() = default;

    OverloaderTest(bool value1);

    OverloaderTest(bool value1, int value2);

    OverloaderTest(bool value1, int value2, std::string value3);

    void SetValue1(bool value);

    bool GetValue1();

    void SetValue2(int value);

    int GetValue2();

    void SetValue3(std::string value);

    std::string GetValue3();

private:
    bool value1_;

    int value2_;

    std::string value3_;
};

#endif //AKI_OVERLOADER_TEST_H
