cmake_minimum_required(VERSION 3.6)

set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

#set(CMAKE_GENERATOR_PLATFORM x64)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)
set(ENV{LUA_PATH} ${CMAKE_BINARY_DIR}/bin/)
set(GLM_TEST_ENABLE OFF CACHE BOOL "Disable GLM tests" FORCE)

if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

if (MSVC)
	if(NOT NDEBUG)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} x64 /bigobj")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} x64 /MP")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -BIGOBJ -Wno-microsoft-enum-forward-reference")
endif()


if(NOT NDEBUG)
#add_compile_options(-fsanitize=address)
endif()

find_package(Vulkan REQUIRED)

project(ScriptEngine)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)




add_subdirectory(Engine/)

add_executable(${PROJECT_NAME} #SHARED
			src/ScriptEngine.h
			src/ScriptEngine.cpp
			src/ClassRegistrator.h
			src/ClassRegistrator.cpp
			)

target_compile_definitions(ScriptEngine PRIVATE GLFW_INCLUDE_VULKAN  GLM_FORCE_DEPTH_ZERO_TO_ONE GLM_FORCE_RADIANS)
#target_compile_definitions(ScriptEngine PUBLIC  _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION)



add_compile_definitions(SCRIPT_ENGINE_EXPORTS)

target_link_libraries(${PROJECT_NAME} PRIVATE
	Vulkan::Vulkan
 	Engine
 	lua_static
)

target_include_directories(${PROJECT_NAME} PRIVATE 
	Engine/src
	Engine/internal
	external/sol2/include
	${Vulkan_INCLUDE_DIRS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)