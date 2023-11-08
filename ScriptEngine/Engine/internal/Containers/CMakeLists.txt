project(Containers)
add_library(${PROJECT_NAME} INTERFACE)

FILE(GLOB_RECURSE headers "*.h")
FILE(GLOB_RECURSE sources "*.cpp")

target_sources(${PROJECT_NAME} INTERFACE
	${headers}
	${sources}
)