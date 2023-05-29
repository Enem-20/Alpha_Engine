project(ComponentSystemLibrary)

set(ComponentSystemSRC 
	src/Component.h
	src/Component.cpp
	src/ComponentFabric.h
	src/ComponentFabric.cpp
	src/Collider2D.h
	src/Collider2D.cpp
	src/Script.h
	src/Script.cpp
	src/LuaScript.h
	src/LuaScript.cpp
	src/Transform.h
	src/Transform.cpp
)

add_library(ComponentSystemLibrary INTERFACE)

target_sources(ComponentSystemLibrary INTERFACE
	${ComponentSystemSRC}
)