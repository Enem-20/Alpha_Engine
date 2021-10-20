project(ScriptEngine)

add_library(${PROJECT_NAME} SHARED
			src/ScriptEngine.h
			src/ScriptEngine.cpp
			# src/LuaParser.h
			# src/LuaParser.cpp
			src/ClassRegistrator.h
			src/ClassRegistrator.cpp
			)

add_subdirectory(Engine/)

if (MSVC)
	if(NOT NDEBUG)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

target_link_libraries(${PROJECT_NAME} Engine)