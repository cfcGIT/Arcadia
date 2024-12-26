# Arcadia

Game-render engine based on [https://github.com/TheCherno/Hazel](https://github.com/TheCherno/Hazel).

Selected Vulkan as principal render API.

Focus and tested on Windows OS.

# Getting started

## Requisites

- Visual Studio (Visual Studio 2022 17.9 recommended)
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) (version 1.3.275.0 recommended)
- [CMake](https://cmake.org/download/) (version 3.29.0 recommended)

## Clone

Clone the repository with `--recursive` parameter to download the submodules too:
```
git clone --recursive https://github.com/cfcGIT/Arcadia.git
```

Existing repositories can be updated manually:
```
git submodule init
git submodule update
```

## Generate project files

(In root folder):
```
mkdir build
cd build
cmake ..
```

> [!NOTE]
> If you are on Windows OS you can generate project files running the [SetupCMake.bat](https://github.com/cfcGIT/Arcadia/blob/main/scripts/SetupCMake.bat) script located in scripts folder.

# Third-Party libraries

- [spdlog](https://github.com/gabime/spdlog). TODO: Make my own.
- [glfw](https://github.com/glfw/glfw)
- [imgui](https://github.com/ocornut/imgui)
- [glm](https://github.com/g-truc/glm)

## Others

- [C++ Standard Library (STL)](https://learn.microsoft.com/en-us/cpp/standard-library/cpp-standard-library-overview?view=msvc-170). TODO: Make my own. References: [EASTL](https://github.com/electronicarts/EASTL)

# Generate Doxygen documentation

To generate doxygen documentation you need to install doxygen (version 1.12.0 recommended).

(In root folder):
```
cd doxygen
Doxygen Doxyfile.dox
```
and you can see the index.html generated in ..\docs\index.html.

> [!NOTE]
> If you are on Windows OS you can generate doxygen documentation running [GenerateDoc.bat](https://github.com/cfcGIT/Arcadia/blob/main/doxygen/GenerateDoc.bat) script located in doxygen folder.

# Task List

## General

- [ ] CVar system. References: [DOOM-3](https://github.com/id-Software/DOOM-3/blob/master/neo/framework/CVarSystem.h), [vkguide](https://vkguide.dev/docs/extra-chapter/cvar_system/).
- [ ] Command system.
- [ ] Shaders hot reload.
- [ ] Debug.cpp with stack trace and other stuff like this.
- [ ] Memory management. Make my own. References: [DOOM-3](https://github.com/id-Software/DOOM-3/blob/master/neo/idlib/Heap.h). In progress.
    - [ ] System to detect memory leaks. In progress.
    - [ ] Vulkan Memory Allocator. Make my own. References: [VMA](https://gpuopen.com/vulkan-memory-allocator/)
- [ ] Perfetto traces. Make my own. At first I can use [the sdk](https://perfetto.dev/docs/instrumentation/tracing-sdk).
- [ ] CPU Multithreading. GameThread-RenderThread at least and async parallel tasks (e.g.: load textures/models/etc. in parallel). Make my own. At first I can use the stl. References: [vkguide](https://vkguide.dev/docs/extra-chapter/multithreading/).
- [ ] Auto-install vulkan sdk when executing cmake if not already installed.

## Render

### Vulkan

- [ ] Basics (initialization and draw triangle)
- [ ] Shadow mapping
- [ ] Ambient occlusion
    - [ ] SSAO
    - [ ] GTAO
- [ ] Global illumination
    - [ ] RTGI
    - [ ] DDGI
- [ ] PBR
- [ ] Reflections
    - [ ] Cubemaps
    - [ ] Planar reflections
    - [ ] SSR
    - [ ] Ray tracing
- [ ] Tessellation
- [ ] Bloom
- [ ] Compute shaders

### OpenGL

- [ ] Basics (initialization and draw triangle)

### DirectX12

- [ ] Basics (initialization and draw triangle)

# Github branches

- `main` is the "stable" branch.
- `dev` is the development branch with the latest features.
