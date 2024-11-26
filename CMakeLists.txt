# General

cmake_minimum_required(VERSION 3.29) # 3.29 because it's the version that I have installed and with which I have tested

set(CMAKE_CXX_STANDARD 20) # this does nothing for MSVC, use target_compile_options below
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

project(Arcadia VERSION 1.0
        DESCRIPTION "Arcadia Engine"
        LANGUAGES CXX)

# Add Arcadia Engine
add_subdirectory(Arcadia)

# Add Sandbox App
add_subdirectory(Sandbox)

# Set VS startup project
if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
endif()