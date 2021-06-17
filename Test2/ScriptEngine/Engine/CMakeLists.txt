cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

set(PROJECT_NAME Engine)

project(${PROJECT_NAME})

# set(UI
	# src/UI/WindowManager.h
	# src/UI/WindowManager.cpp
	# src/UI/Window.h
	# src/UI/Window.cpp
	# src/UI/UIelement.h
	# src/UI/UIelement.cpp
	# src/UI/Button.h
	# src/UI/Button.cpp
	# src/UI/Canvas.h
	# src/UI/Canvas.cpp
	# src/UI/ColorBuffer.h
	# src/UI/ColorBuffer.cpp
	# src/UI/Text.h
	# src/UI/Text.cpp)

# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}\src" PREFIX "UI" FILES ${UI})

add_library(${PROJECT_NAME} STATIC
	src/EngineMain.h
	src/EngineMain.cpp
	src/Timer.h
	src/Timer.cpp
	
	src/UI/WindowManager.h
	src/UI/WindowManager.cpp
	src/UI/Window.h
	src/UI/Window.cpp
	src/UI/UIelement.h
	src/UI/UIelement.cpp
	src/UI/Button.h
	src/UI/Button.cpp
	src/UI/Canvas.h
	src/UI/Canvas.cpp
	src/UI/ColorBuffer.h
	src/UI/ColorBuffer.cpp
	src/UI/Text.h
	src/UI/Text.cpp
	
	src/Renderer/ShaderProgram.h
	src/Renderer/ShaderProgram.cpp
	src/Renderer/Texture2D.cpp
	src/Renderer/Texture2D.h
	src/Renderer/Sprite.h
	src/Renderer/Sprite.cpp
	src/Renderer/AnimatedSprite.h
	src/Renderer/AnimatedSprite.cpp
	src/Renderer/VertexBuffer.h
	src/Renderer/VertexBuffer.cpp
	src/Renderer/IndexBuffer.h
	src/Renderer/IndexBuffer.cpp
	src/Renderer/VertexArray.h
	src/Renderer/VertexArray.cpp
	src/Renderer/VertexBufferLayout.h
	src/Renderer/VertexBufferLayout.cpp
	src/Renderer/Renderer.h
	src/Renderer/Renderer.cpp
	
	src/Resources/ResourceManager.h
	src/Resources/ResourceManager.cpp
	src/Resources/stb_image.h
	src/Resources/Serializer.h
	src/Resources/Serializer.cpp
	src/Resources/Resources.h
	
	src/Scene/Scene.h
	src/Scene/Scene.cpp
	src/Scene/Hierarchy.h
	src/Scene/Hierarchy.cpp
	src/Scene/Camera.h
	src/Scene/Camera.cpp
	
	src/GameTypes/GameObject.h
	src/GameTypes/GameObject.cpp
	src/GameTypes/GameTypes.h
	
	src/Physics/Raycast2D.h
	src/Physics/Raycast2D.cpp
	src/Physics/Collider.h
	src/Physics/Collider.cpp
	
#	src/Game/AI.h
#	src/Game/AI.cpp
	
#	src/Algorithms/Node.h
#	src/Algorithms/Node.cpp
#	src/Algorithms/Move.h
#	src/Algorithms/Move.cpp
#	src/Algorithms/hash_table.h
#	src/Algorithms/hash_table.cpp
#	src/Algorithms/FindPaths.h
#	src/Algorithms/FindPaths.cpp
#	src/Algorithms/StandartDebut.h
#	src/Algorithms/StandartDebut.cpp
	
	src/Input/Input.h
	src/Input/Input.cpp
	
	src/GLPref/GLPref.h
	src/GLPref/GLPref.cpp
	
	src/Components/Component.h
	src/Components/Component.cpp
	src/Components/Components.h
#	src/Components/Physics/Collider.h
#	src/Components/Physics/Collider.cpp
	src/Components/LuaScript.h
	src/Components/LuaScript.cpp
	src/Components/Transform.h
	src/Components/Transform.cpp
	)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/Lua)
add_subdirectory(external/freetype)

target_include_directories(${PROJECT_NAME} PUBLIC external/glm)
target_include_directories(${PROJECT_NAME} PUBLIC external/sol2/include)
target_include_directories(${PROJECT_NAME} PUBLIC external/rapidjson/include)

target_link_libraries(${PROJECT_NAME} PUBLIC lua_static)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw freetype)