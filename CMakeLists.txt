if(OHOS)
	cmake_minimum_required(VERSION 3.6)
	project(external)

	add_subdirectory(Box2D)
	add_subdirectory(chipmunk)
	add_subdirectory(freetype2)
	add_subdirectory(recast)
	add_subdirectory(bullet)
	add_subdirectory(jpeg)
	add_subdirectory(openssl)
	add_subdirectory(tiff)
	add_subdirectory(uv)
	add_subdirectory(webp)
	add_subdirectory(websockets)
	add_subdirectory(tinyxml2)
	add_subdirectory(xxhash)
	add_subdirectory(xxtea)
	add_subdirectory(clipper)
	add_subdirectory(edtaa3func)
	add_subdirectory(ConvertUTF)
	add_subdirectory(poly2tri)
	add_subdirectory(md5)
 
 

	# use lua/js specific libs by property to prevent conflict
	if(BUILD_JS_LIBS)
	    add_subdirectory(spidermonkey) 
	endif()
	if(BUILD_LUA_LIBS)
	    add_subdirectory(lua/luajit)
	    add_subdirectory(lua/tolua)
	    add_subdirectory(lua/luasocket) 
	endif()

    add_subdirectory(curl)
    add_subdirectory(png) 
    message("******** ohos add pvmp3dec and tremolo ***********")
    #add_subdirectory(ohos-specific/cpufeatures) TBD need fixed?
    add_subdirectory(ohos-specific/pvmp3dec)
    add_subdirectory(ohos-specific/tremolo) 
    add_subdirectory(zlib) 

	# unzip depend on zlib
	add_subdirectory(unzip) 
endif()
