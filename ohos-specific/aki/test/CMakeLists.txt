

add_library(unittest SHARED
    async_tasks/async_tasks.cpp
    callback/callback_test.cpp
    callback.cpp
    callback_object.cpp
    function_arguments.cpp
    object_wrap.cpp
    nested_class.cpp
    equivalence/equivalence_test.cpp
    json_object/json_object_test.cpp
    overloader/overloader_test.cpp
    promise/promise_test.cpp
    property/property_test.cpp
    array/array_test.cpp
    array_buffer/array_buffer_test.cpp
    number/number_test.cpp
    js_function/js_function_test.cpp
    napi/napi_test.cpp
    reference_4_object/reference_4_object_test.cpp
    value/value_test.cpp
    )

target_compile_definitions(unittest PUBLIC AKI_ENABLE_NAPI=1)

target_link_libraries(unittest PUBLIC
    libace_napi.z.so
    libc++.a
    libhilog_ndk.z.so
    aki_jsbind)