cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(PROJECT_NAME Engine)

project(${PROJECT_NAME})

set(UI
src/UI/WindowManager.h
src/UI/WindowManager.cpp
src/UI/Window.h
src/UI/Window.cpp
src/UI/UIelement.h
src/UI/UIelement.cpp
src/UI/Button.h
src/UI/Button.cpp
# src/UI/Canvas.h
# src/UI/Canvas.cpp
# src/UI/ColorBuffer.h
# src/UI/ColorBuffer.cpp
# src/UI/Text.h
# src/UI/Text.cpp
)

set(Renderer
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
)

set(Components
	src/Components/Component.h
	src/Components/Component.cpp
	src/Components/LuaScript.h
	src/Components/LuaScript.cpp
	src/Components/Transform.h
	src/Components/Transform.cpp
	# src/Components/Vision.h
	# src/Components/Vision.cpp
)

set(Resources
	src/Resources/ResourceManager.h
	src/Resources/ResourceManager.cpp
	src/Resources/stb_image.h
	src/Resources/Serializer.h
	src/Resources/Serializer.cpp
)

set(Other
	src/EngineMain.h
	src/EngineMain.cpp
	src/Timer.h
	# src/Timer.cpp
)

set(Scene
	# src/Scene/Scene.h
	# src/Scene/Scene.cpp
	src/Scene/Hierarchy.h
	src/Scene/Hierarchy.cpp
	# src/Scene/Camera.h
	# src/Scene/Camera.cpp
)
set(GameTypes
	src/GameTypes/GameObject.h
	src/GameTypes/GameObject.cpp
)
set(Physycs
	# src/Physics/Raycast2D.h
	# src/Physics/Raycast2D.cpp
	# src/Physics/Collider.h
	# src/Physics/Collider.cpp
)
set(Input
	src/Input/Input.h
	src/Input/Input.cpp
)
set(GLPref
	src/GLPref/GLPref.h
	src/GLPref/GLPref.cpp
)

set(Helpers
	src/Helpers/StringFuncs.h
	src/Helpers/casts.h
	# src/Helpers/casts.cpp
)

add_library(${PROJECT_NAME} STATIC
	${Other}
	${UI}
	${Renderer}
	${Resources}
	${Scene}
	${GameTypes}
	${Physycs}
	${Input}	
	${Components}
	${GLPref}
	${Helpers}
	)
source_group("Other" 	  	FILES ${Other})
source_group("UI" 		  	FILES ${UI})
source_group("Renderer"   	FILES ${Renderer})
source_group("Resources" 	FILES ${Resources})
source_group("Scene" 		FILES ${Scene})
source_group("GameTypes" 	FILES ${GameTypes})
source_group("Physycs" 		FILES ${Physycs})
source_group("Input" 	  	FILES ${Input})
source_group("Components" 	FILES ${Components})
source_group("GLPref" 		FILES ${GLPref})
source_group("Helpers" FILES ${Helpers})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_precompile_headers(${PROJECT_NAME} PUBLIC 
	src/Components/Components.pch
	src/GameTypes/GameTypes.pch
	src/Renderer/RendererObjects.pch
	src/Resources/Resources.pch
	src/Scene/SceneClasses.pch
	src/UI/UI.pch)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/Lua)
add_subdirectory(external/P7)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC external/glm)
target_include_directories(${PROJECT_NAME} PUBLIC external/sol2/include)
target_include_directories(${PROJECT_NAME} PUBLIC external/rapidjson/include)

target_link_libraries(${PROJECT_NAME} PUBLIC lua_static)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC p7)



set(IMGUI_INCLUDES
	external/imgui/imgui.h
	external/imgui/backends/imgui_impl_glfw.h
	external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES
	external/imgui/imgui.cpp
	external/imgui/backends/imgui_impl_glfw.cpp
	external/imgui/backends/imgui_impl_opengl3.cpp
	external/imgui/imgui_demo.cpp
	external/imgui/imgui_draw.cpp
	external/imgui/imgui_widgets.cpp
	external/imgui/imgui_tables.cpp
)


add_library(ImGUI STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(ImGUI PUBLIC external/)
target_include_directories(ImGUI PUBLIC external/imgui/)
target_link_libraries(ImGUI PRIVATE glad glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGUI)