project(ComponentSystemLibrary)

add_library(${PROJECT_NAME} INTERFACE)

FILE(GLOB_RECURSE headers "*.h")
FILE(GLOB_RECURSE sources "*.cpp")

message(STATUS ${headers})

target_sources(${PROJECT_NAME} INTERFACE
	${headers}
	${sources}
)