# gui_project_cpp

GUI project in C++ using ImGui-SFML.
 
|          |                                                                                                                                     Status |
|----------|-------------------------------------------------------------------------------------------------------------------------------------------:|
| Travis   |        [![Build Status](https://travis-ci.org/spjuanjoc/gui_project_cpp.svg?branch=main)](https://travis-ci.org/spjuanjoc/gui_project_cpp) |
| Coverage | [![codecov](https://codecov.io/gh/spjuanjoc/gui_project_cpp/branch/main/graph/badge.svg)](https://codecov.io/gh/spjuanjoc/gui_project_cpp) |


## Install dependencies with Conan

1. Set up the `bincrafters` repository for the ImGui+SFML package


    conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan

## Requirements 
 
| Compiler       |
|:---------------|
| GCC >= 8.3.0   |
| Clang >= 7.0.0 |
| MSVC >= 14.16  |
 
 
## Install dependencies for Linux 
 
1. Install extra packages required for imgui in Linux:
 
    ```shell 
    sudo apt install -y          \ 
        libgl1-mesa-dev          \ 
        xorg-dev                 \ 
        libxcb-render-util0-dev  \ 
        libxcb-xkb-dev           \ 
        libxcb-icccm4-dev        \ 
        libxcb-image0-dev        \ 
        libxcb-keysyms1-dev      \ 
        libxcb-xinerama0-dev     \ 
    ``` 
 
## Build 
 
1. Build 

    ```` 
    cmake -DCMAKE_MODULE_PATH=$PWD \ 
          -DCMAKE_BUILD_TYPE=Debug \ 
          -DCMAKE_C_COMPILER=gcc-8 -DCMAKE_CXX_COMPILER=g++-8 .. 
    cmake --build ./ -- -j8 
    ```` 
 
## Run
 
    ./build/gui_project_cpp
 
## spdlog and fmt::format
 
See about [spdlog](https://github.com/gabime/spdlog/wiki/3.-Custom-formatting)

## Notes

To install conan: `pip install --user conan`

To install ninja: `pip install --user ninja`
