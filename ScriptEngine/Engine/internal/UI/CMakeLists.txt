project(UI)

set(UILibrary
	src/UIelement.h
	src/UIelement.cpp
	src/Button.h
	src/Button.cpp
	src/Panel.h
	src/Panel.cpp
	src/Canvas.h
	src/Canvas.cpp
)

add_library(UI INTERFACE)

target_sources(UI INTERFACE
	${UILibrary}
)

source_group(UI FILES ${UILibrary})

target_compile_features(UI INTERFACE cxx_std_20)