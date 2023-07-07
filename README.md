# flappy_bird_cpp

Flappy Bird in C++ using ImGui-SFML.

## Requirements

| Compiler             | 
| :------------------- | 
| GCC >= 8.3.0         | 
| Clang >= 7.0.0       | 
| MSVC >= 14.16        | 


## Install dependencies for Linux

2. Install extra packages required for imgui in Linux:

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

    ./build/flappy_bird_cpp

---


## TO DO

github actions
conan + android

señales sigc++
argparse

flappy bird into the matrix
log configurations
   level
   name
update clang-format
create TODO file
