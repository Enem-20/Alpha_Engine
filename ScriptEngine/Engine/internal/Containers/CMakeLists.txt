project(Containers)

add_library(Containers INTERFACE)

target_sources(Containers INTERFACE 
	UniversalDictionaryInterface.h
	UniversalDictionaryInterface.cpp
)