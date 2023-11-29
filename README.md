# gui_project_cpp

GUI project in C++ using ImGui-SFML.

| Pipeline |                                                                                                                                                                               Status |
|----------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| Actions  | [![linux](https://github.com/spjuanjoc/gui_project_cpp/actions/workflows/linux.yml/badge.svg?branch=main)](https://github.com/spjuanjoc/gui_project_cpp/actions/workflows/linux.yml) |

[//]: # (| Coverage | [![codecov]&#40;https://codecov.io/gh/spjuanjoc/gui_project_cpp/branch/main/graph/badge.svg&#41;]&#40;https://codecov.io/gh/spjuanjoc/gui_project_cpp&#41; |)

## Install dependencies with Conan

This configuration is required for conan version lower than 2.0.
That version still lacks the migration of some libraries related to ImGui and
SFML.

1. Set up the `bincrafters` repository for the ImGui+SFML package

    ```shell
    conan config set general.revisions_enabled=1
    conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
    ```


## Requirements

| Tool  | Version  |
|:------|----------|
| GCC   | >= 8.3.0 |
| Clang | >= 7.0.0 |
| MSVC  | >= 14.16 |
| Conan | 1.61.0   |


## Install dependencies for Linux

1. Install extra packages required for ImGui and SFML in Linux:

    ```shell 
    conan profile update conf.tools.system.package_manager:mode=install default
    
    sudo apt install -y libgl1-mesa-dev \
      xorg-dev                          \
      libxcb-render-util0-dev           \
      libxcb-xkb-dev                    \
      libxcb-icccm4-dev                 \
      libxcb-image0-dev                 \
      libxcb-keysyms1-dev               \
      libxcb-xinerama0-dev              \
      libx11-xcb-dev                    \
      libxcb-randr0-dev                 \
      libxcb-shape0-dev                 \
      libxcb-sync-dev                   \
      libxcb-xfixes0-dev                \
      libxcb-dri3-dev                   \
      libxcb-cursor-dev                 \
      libxcb-util0-dev
    ``` 

## Compilation

1. Build

    ```shell
    cmake -DCMAKE_MODULE_PATH=$PWD \ 
          -DCMAKE_BUILD_TYPE=Debug \ 
          -DCMAKE_C_COMPILER=gcc-8 -DCMAKE_CXX_COMPILER=g++-8 .. 
    cmake --build ./ -- -j8 
    ```

2. Run

    ```shell
    ./build/gui_project_cpp
    ```

## spdlog and fmt::format

See about [spdlog](https://github.com/gabime/spdlog/wiki/3.-Custom-formatting)

## Notes

To install conan: 

```shell
sudo pip3 install conan==1.61.0
```

To install ninja: 

```shell
pip install --user ninja
```
