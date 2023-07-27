cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(AlphaEngine)

add_executable(${PROJECT_NAME} src/main.cpp)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})



target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

add_subdirectory(ScriptEngine)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")

target_link_libraries(${PROJECT_NAME} ScriptEngine)

target_include_directories(${PROJECT_NAME} PRIVATE external/sol2/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
					
