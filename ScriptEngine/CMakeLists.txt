project(ScriptEngine)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


add_library(${PROJECT_NAME} SHARED
			src/ScriptEngine.h
			src/ScriptEngine.cpp
			# src/LuaParser.h
			# src/LuaParser.cpp
			src/ClassRegistrator.h
			src/ClassRegistrator.cpp
			src/API/ExportProperty.h
			)
target_compile_features(ScriptEngine PRIVATE cxx_std_20)


add_subdirectory(Engine/)

if (MSVC)
	if(NOT NDEBUG)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")

add_compile_definitions(SCRIPT_ENGINE_EXPORTS)
target_link_libraries(${PROJECT_NAME} PRIVATE
 Engine
 glad
 glfw
 PUBLIC
 lua_static
 )

target_include_directories(${PROJECT_NAME} PRIVATE 
#Engine/external/imguiLibrary
Engine/src
external/sol2/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)