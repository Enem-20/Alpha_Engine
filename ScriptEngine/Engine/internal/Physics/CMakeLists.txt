project(Physics)

add_library(Physics INTERFACE)

target_sources(Physics INTERFACE
	src/Physics.h
	src/Physics.cpp
	src/Raycast.h
	src/Raycast.cpp
	)