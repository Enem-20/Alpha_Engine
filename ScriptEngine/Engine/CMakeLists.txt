cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(PROJECT_NAME Engine)

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


project(${PROJECT_NAME})

#find_package(imgui REQUIRED)

set(UI
#src/UI/WindowManager.h
#src/UI/WindowManager.cpp
#src/UI/Window.h
#src/UI/Window.cpp
#src/UI/UIelement.h
#src/UI/UIelement.cpp
#src/UI/Button.h
#src/UI/Button.cpp
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
	
	#internal/Renderer/src/Renderer.h
	#internal/Renderer/src/Renderer.cpp
	#internal/Renderer/src/Texture2D.h
	#internal/Renderer/src/Texture2D.cpp
	#internal/Renderer/src/Window.h
	#internal/Renderer/src/Window.cpp
	#internal/Renderer/src/WindowManager.h
	#internal/Renderer/src/WindowManager.cpp
	#
	#internal/Renderer/src/Vulkan/CommandBuffer.h
	#internal/Renderer/src/Vulkan/CommandBuffer.cpp
	#internal/Renderer/src/Vulkan/CommandPool.h
	#internal/Renderer/src/Vulkan/CommandPool.cpp
	#internal/Renderer/src/Vulkan/DebugMessenger.h
	#internal/Renderer/src/Vulkan/DebugMessenger.cpp
	#internal/Renderer/src/Vulkan/DescriptionSets.h
	#internal/Renderer/src/Vulkan/DescriptionSets.cpp
	#internal/Renderer/src/Vulkan/DescriptorPool.h
	#internal/Renderer/src/Vulkan/DescriptorPool.cpp
	#internal/Renderer/src/Vulkan/DescriptorSetLayout.h
	#internal/Renderer/src/Vulkan/DescriptorSetLayout.cpp
	#internal/Renderer/src/Vulkan/GeneralVulkanStorage.h
	#internal/Renderer/src/Vulkan/GeneralVulkanStorage.cpp
	#internal/Renderer/src/Vulkan/ImageView.h
	#internal/Renderer/src/Vulkan/ImageView.cpp
	#internal/Renderer/src/Vulkan/IndexBuffer.h
	#internal/Renderer/src/Vulkan/IndexBuffer.cpp
	#internal/Renderer/src/Vulkan/Instance.h
	#internal/Renderer/src/Vulkan/Instance.cpp
	#internal/Renderer/src/Vulkan/LogicalDevice.h
	#internal/Renderer/src/Vulkan/LogicalDevice.cpp
	#internal/Renderer/src/Vulkan/PhysicalDevice.h
	#internal/Renderer/src/Vulkan/PhysicalDevice.cpp
	#internal/Renderer/src/Vulkan/RenderPipeline.h
	#internal/Renderer/src/Vulkan/RenderPipeline.cpp
	#internal/Renderer/src/Vulkan/SingleTimeBuffer.h
	#internal/Renderer/src/Vulkan/SingleTimeBuffer.cpp
	#internal/Renderer/src/Vulkan/SwapChain.h
	#internal/Renderer/src/Vulkan/SwapChain.cpp
	#internal/Renderer/src/Vulkan/SyncObjects.h
	#internal/Renderer/src/Vulkan/SyncObjects.cpp
	#internal/Renderer/src/Vulkan/UniformBuffer.h
	#internal/Renderer/src/Vulkan/UniformBuffer.cpp
	#internal/Renderer/src/Vulkan/Vertex.h
	#internal/Renderer/src/Vulkan/Vertex.cpp
	#internal/Renderer/src/Vulkan/VertexBuffer.h
	#internal/Renderer/src/Vulkan/VertexBuffer.cpp
	#internal/Renderer/src/Vulkan/WindowSurface.h
	#internal/Renderer/src/Vulkan/WindowSurface.cpp
	
)

set(Components
	internal/ComponentSystem/src/Component.h
	internal/ComponentSystem/src/Component.cpp
	internal/ComponentSystem/src/LuaScript.h
	internal/ComponentSystem/src/LuaScript.cpp
	internal/ComponentSystem/src/Transform.h
	internal/ComponentSystem/src/Transform.cpp
	#src/Components/Component.h
	#src/Components/Component.cpp
	#src/Components/LuaScript.h
	#src/Components/LuaScript.cpp
	#src/Components/Transform.h
	#src/Components/Transform.cpp

	# src/Components/Vision.h
	# src/Components/Vision.cpp
)

set(Resources
	src/Resources/ResourceBase.h
	src/Resources/ResourceBase.cpp
	src/Resources/ResourceManager.h
	src/Resources/ResourceManager.cpp
	src/Resources/stb_image.h
	src/Resources/Serializer.h
	src/Resources/Serializer.cpp
)

set(Other
	src/Timer.h
	src/Timer.cpp
	src/ExportPropety.h
	src/main.cpp
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

set(Logging
	src/Logging/Clerk.cpp
	src/Logging/Clerk.h
)

#add_compile_definitions(LOG_INFO LOG_ERR)
add_compile_definitions(ENGINE_EXPORTS)

#add_compile_definitions(NLOG_FULL NLOG_NOERR NLOG_ONLYERRS NLOG_INFO NLOG_CRIT NLOG_ERR NLOG_WARN NLOG_DBG)

add_executable(${PROJECT_NAME} #SHARED
	${Other}
	${UI}
	#${Renderer}
	${Resources}
	${Scene}
	${GameTypes}
	${Physycs}
	${Input}	
	#${Components}
	#${GLPref}
	${Helpers}
	${Logging}
	)
source_group("Other" 	  		FILES ${Other})
source_group("UI" 		  		FILES ${UI})
#source_group("Renderer"   		FILES ${Renderer})
source_group("Resources" 		FILES ${Resources})
source_group("Scene" 			FILES ${Scene})
source_group("GameTypes" 		FILES ${GameTypes})
source_group("Physycs" 			FILES ${Physycs})
source_group("Input" 	  		FILES ${Input})
#source_group("Components" 		FILES ${Components})
#source_group("GLPref" 			FILES ${GLPref})
source_group("Helpers" 			FILES ${Helpers})
source_group("Logging" 			FILES ${Logging})

target_compile_definitions(Engine PRIVATE GLFW_INCLUDE_VULKAN)
#target_compile_definitions(Engine PRIVATE OGL)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
#target_precompile_headers(${PROJECT_NAME} PRIVATE 
#	src/Components/Components.pch
#	src/GameTypes/GameTypes.pch
#	src/Renderer/RendererObjects.pch
#	src/Resources/Resources.pch
#	src/Scene/SceneClasses.pch
#	src/UI/UI.pch
#)
	
add_subdirectory(internal/Renderer)
add_subdirectory(internal/UI)
add_subdirectory(internal/ComponentSystem)

#target_include_directories(${PROJECT_NAME} INTERFACE internal/Renderer/src)
	
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

#add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/Lua)
add_subdirectory(external/P7)
add_subdirectory(external/imguiLibrary)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
 p7
 )

target_link_libraries(Engine PRIVATE Renderer)

target_link_libraries(${PROJECT_NAME} PRIVATE 
UI
ComponentSystem
lua_static 
glad #glfw
IMGUI
 )

target_include_directories(${PROJECT_NAME} PUBLIC external)
target_include_directories(${PROJECT_NAME} PUBLIC external/glm)
target_include_directories(${PROJECT_NAME} PRIVATE external/sol2/include)
target_include_directories(${PROJECT_NAME} PUBLIC external/rapidjson/include)
target_include_directories(${PROJECT_NAME} PRIVATE external/imguiLibrary)
target_include_directories(${PROJECT_NAME} PRIVATE external/imguiLibrary/imgui)
#target_include_directories(${PROJECT_NAME} PRIVATE external/VulkanHpp/Vulkan-Headers/include)


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

#set_target_properties(Engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)




