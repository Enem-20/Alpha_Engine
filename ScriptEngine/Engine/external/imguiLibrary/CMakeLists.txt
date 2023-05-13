set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
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
                            PRIVATE ${IMGUI_DIR}
                            PRIVATE ${IMGUI_DIR}/backends
							PRIVATE ${IMGUI_DIR}/examples/libs/glfw/include
							PRIVATE ../../internal/Renderer/external/VulkanHpp/Vulkan-Headers/include
                            )


