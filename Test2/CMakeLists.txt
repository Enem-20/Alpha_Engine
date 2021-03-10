cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(API)

add_executable(${PROJECT_NAME} src/main.cpp src/main.h)

add_subdirectory(ScriptEngine)
add_subdirectory(external/pugixml)

target_link_libraries(${PROJECT_NAME} ScriptEngine pugixml)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)