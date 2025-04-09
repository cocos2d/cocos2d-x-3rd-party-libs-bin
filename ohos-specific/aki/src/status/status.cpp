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

#include "status.h"

const char* GetStatusDesc(napi_status status)
{
    static const char* desc[] = {
        "ok",                                   // napi_ok
        "invalid arg",                          // napi_invalid_arg
		"object expected",                      // napi_object_expected,
		"string expected",	                    // napi_string_expected,
		"name expected",                        // napi_name_expected,
		"function expected",                    // napi_function_expected,
		"number expected",                      // napi_number_expected,
		"boolean expected",	                    // napi_boolean_expected,
		"array expected",                       // napi_array_expected,
		"generic failure",	                    // napi_generic_failure,
		"pending exception",                    // napi_pending_exception,
		"cancelled",		                    // napi_cancelled,
		"escape called twice",                  // napi_escape_called_twice,
		"handle scope mismatch",                // napi_handle_scope_mismatch,
		"callback scope mismatch",              // napi_callback_scope_mismatch,
		"queue full",		                    // napi_queue_full,
		"closing",                              // napi_closing,
		"bigint expected",                      // napi_bigint_expected,
		"date expected",                        // napi_date_expected,
		"arraybuffer expected",                 // napi_arraybuffer_expected,
		"detachable arraybuffer expected",      // napi_detachable_arraybuffer_expected,
		"would deadlock",	                    // napi_would_deadlock,  /* unused */
    };

    if (status <= napi_would_deadlock) {
    	return desc[status];
	} else {
		return "not napi status";
	}
}