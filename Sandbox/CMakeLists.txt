# Sandbox
# multi-config generator

cmake_minimum_required(VERSION 3.29) # 3.29 because it's the version that I have installed and with which I have tested

## global vars
set(NAME Sandbox)
set(ARC Arcadia)
set(ARC_PATH ../Arcadia)

## executable
add_executable(${NAME} src/SandboxApp.cpp)

## filters
source_group("" FILES src/SandboxApp.cpp)

## compile definitios
if(WIN32)
    add_compile_definitions(ARC_PLATFORM_WINDOWS)
endif()

## compile options
if(MSVC)
    target_compile_options(${NAME} PRIVATE /std:c++20 /MP) # /MP: Build with multiple processes
    target_link_options(${NAME} PUBLIC /ignore:4099)
endif(MSVC)
target_compile_options(${NAME} PRIVATE /utf-8) # To avoid "...\third_party\spdlog\include\spdlog\fmt\bundled\base.h(458,28): error C2338: static_assert failed: 'Unicode support requires compiling with /utf-8'"

## link libraries
# Arcadia
target_link_libraries(${NAME} ${ARC})

## output-dir and post build event
set(OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_VS_PLATFORM_NAME}/${NAME}")
if(MSVC)
    set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
    set_target_properties(${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
    set_target_properties(${NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
endif()

## includes
include_directories(${ARC_PATH}/src)
include_directories(${ARC_PATH}/third_party/spdlog/include)
#include_directories(${ARC_PATH}/third_party/glfw/include)

## TODO: precompiled headers here too?
#target_precompile_headers(${NAME} PUBLIC src/arcpch.h)
