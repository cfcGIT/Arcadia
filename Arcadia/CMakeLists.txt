# Arcadia
# multi-config generator

cmake_minimum_required(VERSION 3.29) # 3.29 because it's the version that I have installed and with which I have tested

project(Arcadia)

## global vars
set(NAME Arcadia)
set(SAND Sandbox)

file(GLOB ROOT_HEADER src/*.h)
file(GLOB ROOT_SOURCE src/*.cpp)
file(GLOB PLATFORM_WINDOWS_HEADER src/Platform/Windows/*.h)
file(GLOB PLATFORM_WINDOWS_SOURCE src/Platform/Windows/*.cpp)
file(GLOB ARC_ROOT_HEADER src/${NAME}/*.h)
file(GLOB ARC_ROOT_SOURCE src/${NAME}/*.cpp)
file(GLOB ARC_EVENTS_HEADER src/${NAME}/Events/*.h)
file(GLOB ARC_EVENTS_SOURCE src/${NAME}/Events/*.cpp)
file(GLOB ARC_IMGUI_HEADER src/${NAME}/ImGui/*.h)
file(GLOB ARC_IMGUI_SOURCE src/${NAME}/ImGui/*.cpp)
file(GLOB ARC_RENDERER_HEADER src/${NAME}/Renderer/*.h)
file(GLOB ARC_RENDERER_SOURCE src/${NAME}/Renderer/*.cpp)
file(GLOB ARC_RENDERER_VULKAN_HEADER src/${NAME}/Renderer/Vulkan/*.h)
file(GLOB ARC_RENDERER_VULKAN_SOURCE src/${NAME}/Renderer/Vulkan/*.cpp)
file(GLOB ARC_CORE_HEADER src/${NAME}/Core/*.h)
file(GLOB ARC_CORE_SOURCE src/${NAME}/Core/*.cpp)

## library
# Headers added to show in filters
# STATIC because it's a static library (.lib)
add_library(${NAME} STATIC
        ${ROOT_HEADER} ${ROOT_SOURCE}
        ${PLATFORM_WINDOWS_HEADER} ${PLATFORM_WINDOWS_SOURCE}
        ${ARC_ROOT_HEADER} ${ARC_ROOT_SOURCE}
        ${ARC_EVENTS_HEADER} ${ARC_EVENTS_SOURCE}
        ${ARC_IMGUI_HEADER} ${ARC_IMGUI_SOURCE}
        ${ARC_RENDERER_HEADER} ${ARC_RENDERER_SOURCE}
        ${ARC_RENDERER_VULKAN_HEADER} ${ARC_RENDERER_VULKAN_SOURCE}
        ${ARC_CORE_HEADER} ${ARC_CORE_SOURCE})

## filters
source_group("" FILES ${ROOT_HEADER} ${ROOT_SOURCE})
source_group("${NAME}" FILES ${ARC_ROOT_HEADER} ${ARC_ROOT_SOURCE})
source_group("${NAME}/Events" FILES ${ARC_EVENTS_HEADER} ${ARC_EVENTS_SOURCE})
source_group("${NAME}/ImGui" FILES ${ARC_IMGUI_HEADER} ${ARC_IMGUI_SOURCE})
source_group("${NAME}/Renderer" FILES ${ARC_RENDERER_HEADER} ${ARC_RENDERER_SOURCE})
source_group("${NAME}/Renderer/Vulkan" FILES ${ARC_RENDERER_VULKAN_HEADER} ${ARC_RENDERER_VULKAN_SOURCE})
source_group("Platform/Windows" FILES ${PLATFORM_WINDOWS_HEADER} ${PLATFORM_WINDOWS_SOURCE})
source_group("${NAME}/Core" FILES ${ARC_CORE_HEADER} ${ARC_CORE_SOURCE})

## compile definitios
add_compile_definitions("$<$<CONFIG:Debug>:ARC_ENABLE_ASSERT>")
add_compile_definitions("$<$<CONFIG:Debug>:ARC_VK_DEBUG>")
add_compile_definitions(ARC_TRACK_MEMORY)
if (WIN32)
    add_compile_definitions(ARC_PLATFORM_WINDOWS)
endif(WIN32)

## compile options
if(MSVC)
    target_compile_options(${NAME} PRIVATE /std:c++20)
    # /MD here and in another projects to avoid having different heaps and pottential crashes (e.g. spdlog was trying to free memory allocated by different heap)
    # To link the right runtime version of the right runtime library version
    target_compile_options(${NAME} PRIVATE $<IF:$<CONFIG:Debug>,/MDd /Zi,/MD>)
    target_compile_options(${NAME} PRIVATE /Wall) # All warnings
    target_compile_options(${NAME} PRIVATE /external:I third_party /external:W0) # No warnings in third party libs
    target_compile_options(${NAME} PRIVATE /MP) # Multiprocessor compilation
    target_link_options(${NAME} PUBLIC /ignore:4099)
endif(MSVC)
target_compile_options(${NAME} PRIVATE /utf-8) # To avoid "...\third_party\spdlog\include\spdlog\fmt\bundled\base.h(458,28): error C2338: static_assert failed: 'Unicode support requires compiling with /utf-8'"

## link libraries
# git submodules (with source code) #
# GLFW
add_subdirectory(third_party/glfw)
target_link_libraries(${NAME} glfw)
# imgui
add_subdirectory(third_party/imgui)
target_link_libraries(${NAME} imgui)
# glm
add_subdirectory(third_party/glm)
target_link_libraries(${NAME} glm)
# spdlog
add_subdirectory(third_party/spdlog)
target_link_libraries(${NAME} spdlog)

# installed packages (without source code) # TODO: install if not found
# OpenGL (not principal render API)
find_package(OpenGL)
target_link_libraries(${NAME} OpenGL::GL)
# Vulkan (principal render API)
find_package(Vulkan REQUIRED)
target_link_libraries(${NAME} Vulkan::Vulkan)

## output-dir and post build event
set(OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_VS_PLATFORM_NAME}/${NAME}")
if(MSVC)
    set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
    set_target_properties(${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
    set_target_properties(${NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
endif()

## includes
include_directories(src)
include_directories(third_party/spdlog/include)
include_directories(third_party/glfw/include)
include_directories(third_party/imgui/include)
include_directories(third_party/imgui/include/imgui) # Because backends/imgui_impl_vulkan.h has '#include "imgui.h"' and I don't want to modify the include path
include_directories(third_party/glm)

## precompiled headers
target_precompile_headers(${NAME} PUBLIC src/arcpch.h)
