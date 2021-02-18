cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

set(PROJECT_NAME Test2)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/Messenger.h
	src/Messenger.cpp
	src/Helpers/casts.h
	src/Helpers/casts.cpp
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
	src/Scene/Scene.h
	src/Scene/Scene.cpp
	src/Scene/Hierarchy.h
	src/Scene/Hierarchy.cpp
	src/Game/GObject.h
	src/Game/GObject.cpp
	src/Game/Desk.h
	src/Game/Desk.cpp
	src/Game/Game.h
	src/Game/Game.cpp
	src/Game/AllowedCell.h
	src/Game/AllowedCell.cpp
	src/Game/Figure.h
	src/Game/Figure.cpp
	src/Game/AI.h
	src/Game/AI.cpp
	src/Algorithms/Node.h
	src/Algorithms/Node.cpp
	src/Algorithms/Move.h
	src/Algorithms/Move.cpp
	src/Algorithms/hash_table.h
	src/Algorithms/hash_table.cpp
	src/Algorithms/FindPaths.h
	src/Algorithms/FindPaths.cpp
	src/Algorithms/StandartDebut.h
	src/Algorithms/StandartDebut.cpp
	src/Input/Input.h
	src/Input/Input.cpp
	src/GLPref/GLPref.h
	src/GLPref/GLPref.cpp
	src/Components/Component.h
	src/Components/Component.cpp
	src/Components/Physics/Collider.h
	src/Components/Physics/Collider.cpp
	)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/pugixml)
add_subdirectory(external/Lua)

add_subdirectory(external/Lua)
target_link_libraries(${PROJECT_NAME} lua_static)

include_directories(external/glm)
include_directories(external/LuaBridge)

target_link_libraries(${PROJECT_NAME} glad glfw pugixml lua_static)


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)