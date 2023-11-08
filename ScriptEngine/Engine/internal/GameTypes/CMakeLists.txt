project(GameTypes)
add_library(${PROJECT_NAME} INTERFACE)

FILE(GLOB_RECURSE headers "*.h")
FILE(GLOB_RECURSE sources "*.cpp")

target_sources(${PROJECT_NAME} INTERFACE
	${headers}
	${sources}
)

#target_include_directories(${PROJECT_NAME} INTERFACE ../API/src)
#target_include_directories(${PROJECT_NAME} INTERFACE ../UI/src)
#target_include_directories(${PROJECT_NAME} INTERFACE ../ComponentSystem/src)
#target_include_directories(${PROJECT_NAME} INTERFACE ../Resources/src)
#target_include_directories(${PROJECT_NAME} INTERFACE ../Renderer/src)
#target_include_directories(${PROJECT_NAME} INTERFACE ../Tools/src)
#target_include_directories(${PROJECT_NAME} INTERFACE ../Logging/src)