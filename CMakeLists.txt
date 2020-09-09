cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

set(PROJECT_NAME Test2)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/Algorithms/FindPaths.h
	src/Renderer/ShaderProgram.h
	src/Renderer/ShaderProgram.cpp
	src/Renderer/Texture2D.cpp
	src/Renderer/Texture2D.h
	src/Renderer/Sprite.h
	src/Renderer/Sprite.cpp
	src/renderer/AnimatedSprite.h
	src/renderer/AnimatedSprite.cpp
	src/Resources/ResourceManager.h
	src/Resources/ResourceManager.cpp
	src/Resources/stb_image.h
	src/Game/GObject.h
	src/Game/GObject.cpp
	src/Game/Game.h
	src/Game/Game.cpp
	src/Algorithms/hash_table.h
	src/Algorithms/hash_table.cpp
	)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)