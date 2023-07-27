project(ScriptEngine)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)
set(ENV{LUA_PATH} ${CMAKE_BINARY_DIR}/bin/)

add_executable(${PROJECT_NAME} #SHARED
			src/ScriptEngine.h
			src/ScriptEngine.cpp
			# src/LuaParser.h
			# src/LuaParser.cpp
			src/ClassRegistrator.h
			src/ClassRegistrator.cpp
			)
target_compile_features(ScriptEngine PRIVATE cxx_std_20)

target_compile_definitions(ScriptEngine PRIVATE GLFW_INCLUDE_VULKAN  GLM_FORCE_DEPTH_ZERO_TO_ONE GLM_FORCE_RADIANS)
#target_compile_definitions(ScriptEngine PUBLIC  _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION)

if (MSVC)
	if(NOT NDEBUG)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

if(NOT NDEBUG)
#add_compile_options(-fsanitize=address)
endif()

add_subdirectory(Engine/)



set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")

add_compile_definitions(SCRIPT_ENGINE_EXPORTS)

target_link_libraries(${PROJECT_NAME} PRIVATE
 Engine
 #glad
 #glfw
 lua_static
 )

target_include_directories(${PROJECT_NAME} PRIVATE 
#Engine/external/imguiLibrary
Engine/src
Engine/internal
external/sol2/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#					COMMAND ${CMAKE_COMMAND} -E copy_directory
#					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)