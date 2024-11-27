cmake_minimum_required(VERSION 3.29)

project(imgui)

file(GLOB IMGUI_HEADER include/imgui/*.h)
file(GLOB IMGUI_SOURCE include/imgui/*.cpp)

add_library(imgui STATIC ${IMGUI_HEADER} ${IMGUI_SOURCE})
