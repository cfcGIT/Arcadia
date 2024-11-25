# Arcadia
# multi-config generator

cmake_minimum_required(VERSION 3.29) # 3.29 because it's the version that I have installed and with which I have tested

## global vars
set(NAME Arcadia)
set(SAND Sandbox)

file(GLOB ROOT_HEADER src/*.h)
file(GLOB ROOT_SOURCE src/*.cpp)
file(GLOB PLATFORM_HEADER src/Platform/*.h)
file(GLOB PLATFORM_SOURCE src/Platform/*.cpp)
file(GLOB PLATFORM_WINDOWS_HEADER src/Platform/Windows/*.h)
file(GLOB PLATFORM_WINDOWS_SOURCE src/Platform/Windows/*.cpp)
file(GLOB ARC_ROOT_HEADER src/${NAME}/*.h)
file(GLOB ARC_ROOT_SOURCE src/${NAME}/*.cpp)
file(GLOB ARC_EVENTS_HEADER src/${NAME}/Events/*.h)
file(GLOB ARC_EVENTS_SOURCE src/${NAME}/Events/*.cpp)

## library
# Headers added to show in filters
# SHARED because it's a dynamic library (.dll)
add_library(${NAME} SHARED
        ${ROOT_HEADER} ${ROOT_SOURCE}
        ${PLATFORM_HEADER} ${PLATFORM_SOURCE}
        ${PLATFORM_WINDOWS_HEADER} ${PLATFORM_WINDOWS_SOURCE}
        ${ARC_ROOT_HEADER} ${ARC_ROOT_SOURCE}
        ${ARC_EVENTS_HEADER} ${ARC_EVENTS_SOURCE})

## TODO: Filters with folders in vs
# ...

## compile definitios
add_compile_definitions(ARC_BUILD_DLL)
add_compile_definitions("$<$<CONFIG:Debug>:ARC_ENABLE_ASSERT>")
if (WIN32)
    add_compile_definitions(ARC_PLATFORM_WINDOWS)
endif(WIN32)

## compile options
if(MSVC)
    target_compile_options(${NAME} PRIVATE /std:c++20 /MP) # /MP: Build with multiple processes
    target_link_options(${NAME} PUBLIC /ignore:4099)
endif(MSVC)
target_compile_options(${NAME} PRIVATE /utf-8) # To avoid "...\third_party\spdlog\include\spdlog\fmt\bundled\base.h(458,28): error C2338: static_assert failed: 'Unicode support requires compiling with /utf-8'"

## link libraries
# GLFW
add_subdirectory(third_party/glfw) # With source code
target_link_libraries(${NAME} glfw)
# OpenGL
find_package(OpenGL REQUIRED) # Without source code (found in Windows Kits)
target_link_libraries(${NAME} OpenGL::GL)

## output-dir and post build event
set(OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_VS_PLATFORM_NAME}/${NAME}")
if(MSVC)
    set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
    set_target_properties(${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
    set_target_properties(${NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")

    add_custom_command(TARGET ${NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OUTPUT_DIRECTORY}/${NAME}.dll" "${OUTPUT_DIRECTORY}/../${SAND}/${NAME}.dll" COMMENT "ARC_DBG: Copy ${NAME}.dll to ${SAND} project")
endif()

## includes
include_directories(src)
include_directories(third_party/spdlog/include)
include_directories(third_party/glfw/include)

## precompiled headers
target_precompile_headers(${NAME} PUBLIC src/arcpch.h)
