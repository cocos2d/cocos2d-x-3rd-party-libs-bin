if(OHOS)
	cmake_minimum_required(VERSION 3.6)
	set(lib_name luajit)

	add_library(${lib_name} STATIC IMPORTED GLOBAL)

	set(_path_prefix ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/)

	set(platform_name ohos)
	set(platform_spec_path ohos) 

	set(platform_spec_path "${_path_prefix}${platform_spec_path}")


	set_target_properties(${lib_name} PROPERTIES
	        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
	        )
	set_target_properties(${lib_name} PROPERTIES
	    IMPORTED_LOCATION "${platform_spec_path}/lib${lib_name}.a"
	    )
endif()