set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

find_package(Vulkan REQUIRED)
find_library(Vulkan_LIBRARY NAMES vulkan-1 PATHS ${VULKAN_SDK}/Lib NO_DEFAULT_PATH)

add_library(IMGUI STATIC)

target_sources( IMGUI
                PRIVATE
                    ${IMGUI_DIR}/imgui_demo.cpp
                    ${IMGUI_DIR}/imgui_draw.cpp
                    ${IMGUI_DIR}/imgui_tables.cpp
                    ${IMGUI_DIR}/imgui_widgets.cpp
					${IMGUI_DIR}/imgui.h
                    ${IMGUI_DIR}/imgui.cpp

                PRIVATE
                    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
					${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
					${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
                    #${IMGUI_DIR}/backends/imgui_impl_sdl.cpp
                )

target_include_directories( IMGUI
                            PRIVATE ${Vulkan_INCLUDE_DIRS}
                            PRIVATE ${IMGUI_DIR}
                            PRIVATE ${IMGUI_DIR}/backends
                            PRIVATE ../glfw/include
                            #PRIVATE ${IMGUI_DIR}/examples/libs/glfw/include

                            )

target_link_libraries(  IMGUI 
                        PRIVATE $ENV{Vulkan_SDK}/Lib/vulkan-1.lib
                        PRIVATE glfw
                    )




