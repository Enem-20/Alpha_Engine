cmake_minimum_required(VERSION 3.14)

project(dx)

#add_library(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(dx ${DIRECTX_D3DX9_LIBRARIES})