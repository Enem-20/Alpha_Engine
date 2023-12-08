cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

set(PROJECT_NAME Engine)

set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(${PROJECT_NAME})

#add_compile_definitions(LOG_INFO LOG_ERR)
add_compile_definitions(ENGINE_EXPORTS)

#add_compile_definitions(NLOG_FULL NLOG_NOERR NLOG_ONLYERRS NLOG_INFO NLOG_CRIT NLOG_ERR NLOG_WARN NLOG_DBG)

FILE(GLOB_RECURSE internal_headers "internal/*.h")
FILE(GLOB_RECURSE internal_sources "internal/*.cpp")

add_library(Engine SHARED
	)
	
target_sources(Engine PRIVATE
)

#target_compile_definitions(Engine PUBLIC  _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION)
target_compile_definitions(Engine PRIVATE SHOWONBUILD GLFW_INCLUDE_VULKAN  GLM_FORCE_DEPTH_ZERO_TO_ONE GLM_FORCE_RADIANS)
#target_compile_definitions(Engine PRIVATE OGL)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

	
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
set_target_properties(Engine PROPERTIES PUBLIC_HEADER "")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

target_include_directories(${PROJECT_NAME} PRIVATE internal)

file(GLOB V_GLOB LIST_DIRECTORIES true "internal/*")
foreach(item ${V_GLOB})
	if(IS_DIRECTORY ${item})
		add_subdirectory(${item})
	endif()
endforeach()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${internal_headers} ${internal_sources})


add_subdirectory(external/Lua)
add_subdirectory(external/P7)
add_subdirectory(external/imguiLibrary)
add_subdirectory(external/reactphysics3d)
add_subdirectory(external/obj-io)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

target_link_libraries(Engine PUBLIC
	ReactPhysics3D::reactphysics3d
)

target_link_libraries(Engine PRIVATE
	ComponentSystemLibrary
	Containers
	DependencyResolvers
	EventSystem
	GameTypes
	Input
	Logging
	Physics
	Renderer
	Resources
	Tools
	UI
)

target_link_libraries(Engine PRIVATE 
	IMGUI
	p7
	lua_static
	)

target_include_directories(${PROJECT_NAME} PUBLIC external)
target_include_directories(${PROJECT_NAME} PRIVATE external/obj-io/include)
target_include_directories(${PROJECT_NAME} PUBLIC external/glm)
target_include_directories(${PROJECT_NAME} PRIVATE external/sol2/include)
target_include_directories(${PROJECT_NAME} PUBLIC external/rapidjson/include)
target_include_directories(${PROJECT_NAME} PRIVATE external/imguiLibrary)
target_include_directories(${PROJECT_NAME} PRIVATE external/imguiLibrary/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE external/reactphysics3d/include)


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
#set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)




