# Sandbox

cmake_minimum_required(VERSION 3.29) # 3.29 because it's the version that I have installed and with which I have tested

set(NAME Sandbox)
set(ARC Arcadia)
set(ARC_PATH ../Arcadia)

add_executable(${NAME} src/SandboxApp.cpp)
include_directories(${ARC_PATH}/src)
target_link_libraries(${NAME} ${ARC})

if(MSVC)
    target_compile_options(${NAME} PRIVATE /std:c++20 /MP) # /MP: Build with multiple processes
    target_link_options(${NAME} PUBLIC /ignore:4099)
endif(MSVC)

if(WIN32)
    add_compile_definitions(ARC_PLATFORM_WINDOWS)
endif()

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
endif()

target_compile_options(${NAME} PRIVATE /utf-8) # To avoid "...\third_party\spdlog\include\spdlog\fmt\bundled\base.h(458,28): error C2338: static_assert failed: 'Unicode support requires compiling with /utf-8'"

include_directories(${ARC_PATH}/third_party/spdlog/include)

message(STATUS "BUILD_TYPE '${CMAKE_BUILD_TYPE}' generated for '${NAME}'")
