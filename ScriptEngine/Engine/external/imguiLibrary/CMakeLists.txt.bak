set(IMGUI_PATH  "imgui")
    
file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp) 
add_library("ImGui" STATIC ${IMGUI_SOURCES})

target_compile_definitions("ImGui" PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})