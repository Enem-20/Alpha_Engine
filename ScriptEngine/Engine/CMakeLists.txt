cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(PROJECT_NAME Engine)

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(${PROJECT_NAME})

set(ResourcesSRC
	src/Resources/ResourceBase.h
	src/Resources/ResourceBase.cpp
	src/Resources/ResourceManager.h
	src/Resources/ResourceManager.cpp
	src/Resources/stb_image.h
	src/Resources/Serializer.h
	src/Resources/Serializer.cpp
	src/Resources/Mesh.h
	src/Resources/Mesh.cpp
)

set(OtherSRC
	src/Timer.h
	src/Timer.cpp
	src/ExportPropety.h
	src/main.cpp
)

set(Scene

)
set(GameTypesSRC
	src/GameTypes/GameObject.h
	src/GameTypes/GameObject.cpp
)

#set(InputSRC
#	src/Input/Input.h
#	src/Input/Input.cpp
#)

set(HelpersSRC
	src/Helpers/StringFuncs.h
	src/Helpers/casts.cpp
	src/Helpers/casts.h
)

set(LoggingSRC
	src/Logging/Clerk.cpp
	src/Logging/Clerk.h
)

#add_compile_definitions(LOG_INFO LOG_ERR)
add_compile_definitions(ENGINE_EXPORTS)

#add_compile_definitions(NLOG_FULL NLOG_NOERR NLOG_ONLYERRS NLOG_INFO NLOG_CRIT NLOG_ERR NLOG_WARN NLOG_DBG)

add_library(Engine SHARED
	)
	
target_sources(Engine PRIVATE
	${OtherSRC}
	${UI}
	${ResourcesSRC}
	${Scene}
	${GameTypesSRC}
	${Physics}
	#${Input}	
	${HelpersSRC}
	${LoggingSRC}
)
source_group("Other" 	  		FILES ${OtherSRC})
source_group("UI" 		  		FILES ${UI})
source_group("Resources" 		FILES ${ResourcesSRC})
source_group("Scene" 			FILES ${Scene})
source_group("GameTypes" 		FILES ${GameTypesSRC})
source_group("Physics" 			FILES ${Physics})
#source_group("Input" 	  		FILES ${InputSRC})
source_group("Helpers" 			FILES ${HelpersSRC})
source_group("Logging" 			FILES ${LoggingSRC})

target_compile_definitions(Engine PUBLIC  _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION)
target_compile_definitions(Engine PRIVATE SHOWONBUILD GLFW_INCLUDE_VULKAN  GLM_FORCE_DEPTH_ZERO_TO_ONE GLM_FORCE_RADIANS)
#target_compile_definitions(Engine PRIVATE OGL)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

	
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
set_target_properties(Engine PROPERTIES PUBLIC_HEADER "")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(internal/Renderer)
add_subdirectory(internal/UI)
add_subdirectory(internal/ComponentSystem)
add_subdirectory(internal/Physics)
add_subdirectory(internal/Input)
add_subdirectory(internal/Containers)
add_subdirectory(internal/EventSystem)

#add_subdirectory(external/glfw)
#add_subdirectory(external/glad)
add_subdirectory(external/Lua)
add_subdirectory(external/P7)
add_subdirectory(external/imguiLibrary)
add_subdirectory(external/reactphysics3d)
add_subdirectory(external/obj-io)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

#target_link_libraries(${PROJECT_NAME} PUBLIC
#	p7
# 	ReactPhysics3D::reactphysics3d
#	glfw
#	lua_static
#	Renderer
#	Input
#	Physics
#	UI
#	ComponentSystemLibrary
# )

target_link_libraries(Engine PUBLIC
	ReactPhysics3D::reactphysics3d
)

target_link_libraries(Engine PRIVATE 
	Containers
	IMGUI
	p7
	glfw
	lua_static
	Renderer
	Input
	Physics
	UI
	ComponentSystemLibrary
	EventSystem
	)

target_include_directories(${PROJECT_NAME} PUBLIC external)
target_include_directories(${PROJECT_NAME} PRIVATE external/obj-io/include)
target_include_directories(${PROJECT_NAME} PUBLIC external/glm)
target_include_directories(${PROJECT_NAME} PRIVATE external/sol2/include)
target_include_directories(${PROJECT_NAME} PUBLIC external/rapidjson/include)
target_include_directories(${PROJECT_NAME} PRIVATE external/imguiLibrary)
target_include_directories(${PROJECT_NAME} PRIVATE external/imguiLibrary/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE external/reactphysics3d/include)

#target_include_directories(${PROJECT_NAME} PRIVATE external/VulkanHpp/Vulkan-Headers/include)


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
#set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)




