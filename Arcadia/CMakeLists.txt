# Arcadia

cmake_minimum_required(VERSION 3.29) # 3.29 because it's the version that I have installed and with which I have tested

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


# Headers added to show in filters
# SHARED because it's a dynamic library (.dll)
add_library(${NAME} SHARED
        ${ROOT_HEADER} ${ROOT_SOURCE}
        ${PLATFORM_HEADER} ${PLATFORM_SOURCE}
        ${PLATFORM_WINDOWS_HEADER} ${PLATFORM_WINDOWS_SOURCE}
        ${ARC_ROOT_HEADER} ${ARC_ROOT_SOURCE}
        ${ARC_EVENTS_HEADER} ${ARC_EVENTS_SOURCE})

# GLFW
add_subdirectory(third_party/glfw) # With source code
target_link_libraries(${NAME} glfw)
# OpenGL
find_package(OpenGL REQUIRED) # Without source code (found in Windows Kits)
target_link_libraries(${NAME} OpenGL::GL)


add_compile_definitions(ARC_BUILD_DLL)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(ARC_ENABLE_ASSERT)
endif()

if (WIN32)
    add_compile_definitions(ARC_PLATFORM_WINDOWS)
endif(WIN32)

if(MSVC)
    target_compile_options(${NAME} PRIVATE /std:c++20 /MP) # /MP: Build with multiple processes
    target_link_options(${NAME} PUBLIC /ignore:4099)
endif(MSVC)

target_compile_options(${NAME} PRIVATE /utf-8) # To avoid "...\third_party\spdlog\include\spdlog\fmt\bundled\base.h(458,28): error C2338: static_assert failed: 'Unicode support requires compiling with /utf-8'"

# TODO: Use cmake to build different build types (release, debug, ...)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

list (FIND CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} index_)
if (${index_} EQUAL -1)
    message(FATAL_ERROR "BUILD_TYPE '${CMAKE_BUILD_TYPE}' not defined. Try with one of this configuration types: ${CMAKE_CONFIGURATION_TYPES}")
endif()

set(OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_VS_PLATFORM_NAME}/${NAME}")

if(MSVC)
    string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE_UPPER)
    set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${BUILD_TYPE_UPPER} "${OUTPUT_DIRECTORY}")
    set_target_properties(${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${BUILD_TYPE_UPPER} "${OUTPUT_DIRECTORY}")
    set_target_properties(${NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${BUILD_TYPE_UPPER} "${OUTPUT_DIRECTORY}")

    add_custom_command(TARGET ${NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OUTPUT_DIRECTORY}/${NAME}.dll" "${OUTPUT_DIRECTORY}/../${SAND}/${NAME}.dll" COMMENT "Copy ${NAME}.dll to ${SAND} project")
endif()


include_directories(src)

# third party includes
include_directories(third_party/spdlog/include)
include_directories(third_party/glfw/include)

# precompiled headers
target_precompile_headers(${NAME} PUBLIC src/arcpch.h)

message(STATUS "BUILD_TYPE '${CMAKE_BUILD_TYPE}' generated for '${NAME}'")
