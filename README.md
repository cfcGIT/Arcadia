# Arcadia

Game-render engine based on [https://github.com/TheCherno/Hazel](https://github.com/TheCherno/Hazel).

Selected Vulkan as principal render API.

Focus and tested on Windows OS.

# Getting started

## Requisites

- Visual Studio (Visual Studio 2022 17.9 recommended)
- Vulkan SDK (version 1.3.275.0 recommended)
- CMake (version 3.29.0 recommended)

## Clone

Clone the repository with `--recursive` parameter to download the submodules too:
```
git clone --recursive https://github.com/cfcGIT/Arcadia.git
```

## Generate project

Run the [SetupCMake.bat](https://github.com/cfcGIT/Arcadia/blob/main/scripts/SetupCMake.bat) script located in scripts folder to generate the project solution.

# Third-Party libraries

- [spdlog](https://github.com/gabime/spdlog)
- [glfw](https://github.com/glfw/glfw)
- [imgui](https://github.com/ocornut/imgui)

## Others

- [C++ Standard Library (STL)](https://learn.microsoft.com/en-us/cpp/standard-library/cpp-standard-library-overview?view=msvc-170)

# Generate Doxygen documentation

You can generate doxygen documentation running [GenerateDoc.bat](https://github.com/cfcGIT/Arcadia/blob/main/doxygen/GenerateDoc.bat) script located in doxygen folder.

# TODO List

## General

- [ ] CVar system. See [CVarSystem of DOOM-3](https://github.com/id-Software/DOOM-3/blob/master/neo/framework/CVarSystem.h)
- [ ] Command system.

## Render

### Vulkan

- [ ] Basics (initialization and draw triangle)
- [ ] Cubemaps
- [ ] Planar reflections
- [ ] SSR
- [ ] Ray tracing

### OpenGL

- [ ] Basics (initialization and draw triangle)

### DirectX12

- [ ] Basics (initialization and draw triangle)
