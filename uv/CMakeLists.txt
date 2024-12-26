cmake_minimum_required(VERSION 3.6)

if(OHOS)
	set(lib_name uv)
	set(target_name ext_${lib_name})

	project(${lib_name})

	add_library(${target_name} STATIC IMPORTED GLOBAL)

	set_target_properties(${target_name} PROPERTIES
	  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
	)

	set_target_properties(${target_name} PROPERTIES
	IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/ohos/lib${lib_name}_a.a"
	)

endif()
