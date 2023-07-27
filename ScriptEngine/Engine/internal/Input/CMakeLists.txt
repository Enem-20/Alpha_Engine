project(Input)

add_library(Input INTERFACE)

target_sources(Input INTERFACE
	src/Input.h
	src/Input.cpp
	)