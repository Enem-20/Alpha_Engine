project(ComponentSystem)

add_library(ComponentSystem INTERFACE)

target_sources(ComponentSystem INTERFACE
	src/Component.h
	src/Component.cpp
	src/LuaScript.h
	src/LuaScript.cpp
	src/Transform.h
	src/Transform.cpp
)

#add_Subdirectory(external/glfw)
#add_subdirectory(external/VulkanHpp)
#
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
#
#if(WIN32)
#	target_link_libraries(${PROJECT_NAME} INTERFACE 
#		"$ENV{VULKAN_SDK}/Lib/vulkan-1.lib"
#		)
#endif(WIN32)
#
#if(UNIX)
#	target_link_libraries(${PROJECT_NAME} INTERFACE 
#		"$ENV{VULKAN_SDK}/Lib/vulkan-1.a"
#		)
#endif(UNIX)
#
#target_link_libraries(${PROJECT_NAME} INTERFACE 
#	glfw
#	)
#
#target_include_directories(${PROJECT_NAME} INTERFACE 
#	external/VulkanHpp/Vulkan-Headers/include
#	external/glm
#	external/stb
#)