# AtlasRenderer

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-26-blue?style=for-the-badge&logo=cplusplus" alt="C++26">
  <img src="https://img.shields.io/badge/OpenGL-4.6-blue?style=for-the-badge&logo=opengl" alt="OpenGL">
  <img src="https://img.shields.io/badge/GLM-Math-lightgrey?style=for-the-badge" alt="GLM">
  <img src="https://img.shields.io/badge/Premake5-Build-orange?style=for-the-badge&logo=premake" alt="Premake5">
</p>

> ⚠️ **Work in Progress**

AtlasRenderer is a modern C++ rendering library designed to provide graphics functionality for the Atlas ecosystem. It builds on AtlasLib's core and OpenGL context infrastructure while providing abstractions for rendering, buffers, shaders, textures, cameras, and other graphics functionality.

AtlasRenderer is designed as a separate library from AtlasLib so that core application functionality and rendering functionality remain independent.

## Features

* OpenGL rendering
* Vertex and index buffer abstractions
* Vertex array management
* Shader abstraction
* Texture support
* Camera and projection utilities
* Render command abstraction
* Renderer interface
* GLM-based mathematics
* C++26 support

## Dependencies

AtlasRenderer currently uses:

* [AtlasLib](https://github.com/MSh103/AtlasLib) — Core application and graphics infrastructure
* [GLAD](https://github.com/Dav1dde/glad) — OpenGL function loading
* [GLM](https://github.com/g-truc/glm) — Mathematics library

Dependencies are included through Git submodules where applicable.

## Requirements

### Windows

* Windows 10 or newer
* Visual Studio 2022 or newer
* C++26-compatible compiler
* Git
* Premake5

AtlasRenderer currently targets **x64**.

## Workspace Requirement

AtlasRenderer's `build.lua` is intended to be included by a **Premake workspace** alongside AtlasLib and an application or sandbox project.

For example:

```lua
workspace "AtlasEcosystem"
        architecture "x64"

        configurations
        {
                "Debug",
                "Release"
        }

include "AtlasLib/dependencies.lua"
include "AtlasRenderer/dependencies.lua"

include "AtlasLib/build.lua"
include "AtlasRenderer/build.lua"
include "AtlasSandbox/build.lua"

```

This allows AtlasRenderer to be developed and tested alongside AtlasLib and AtlasSandbox within the same workspace.

## Building

Clone the repository and initialize its dependencies:

```bash
git clone https://github.com/MSh103/AtlasRenderer.git
cd AtlasRenderer

git submodule update --init --recursive
```

AtlasRenderer is normally built as part of an Atlas ecosystem workspace rather than as a standalone application.

Generate the Visual Studio project files using Premake:

```bash
premake5 vs2022
```

Then open the generated solution and build the desired configuration.

Available configurations:

```text
Debug
Release
```

AtlasRenderer is currently developed and tested primarily on Windows with Visual Studio.

## Usage

AtlasRenderer is intended to be used by applications built on top of the Atlas ecosystem.

A typical application can use AtlasLib for application and platform functionality while using AtlasRenderer for graphics functionality:

```text
Application
    │
    ├── AtlasLib
    │   ├── Application
    │   ├── Window
    │   ├── Events
    │   ├── Input
    │   └── OpenGL Context
    │
    └── AtlasRenderer
        ├── Buffers
        ├── Vertex Arrays
        ├── Shaders
        ├── Textures
        ├── Cameras
        └── Rendering
```

This separation keeps AtlasLib focused on core application functionality while AtlasRenderer handles graphics and rendering.

## License

AtlasRenderer is licensed under the MIT License. See [LICENSE](LICENSE) for more information.
