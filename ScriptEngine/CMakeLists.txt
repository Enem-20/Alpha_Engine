project(ScriptEngine)

add_library(${PROJECT_NAME} STATIC
			src/ScriptEngine.h
			src/ScriptEngine.cpp
			src/LuaParser.h
			src/LuaParser.cpp
			src/ClassRegistrator.h
			src/ClassRegistrator.cpp
			src/Headers.h
			)

add_subdirectory(Engine/)

target_include_directories(${PROJECT_NAME} PUBLIC external/sol2/include)
target_link_libraries(${PROJECT_NAME} Engine)