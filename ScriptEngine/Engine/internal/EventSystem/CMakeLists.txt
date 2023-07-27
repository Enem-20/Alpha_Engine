project(EventSystem)

add_library(EventSystem INTERFACE)

target_sources(EventSystem INTERFACE src/InitializeEventsInterface.h src/InitializeEventsInterface.cpp)