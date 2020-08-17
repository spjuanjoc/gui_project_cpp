# game_project_cpp

Game project.
 
1. Install ImGui-SFML using conan
2. Use ImGui-SFML to show a sample window

## Install dependencies with Conan

Setup bincrafters

    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

Extra packages required for imgui:
````
    libgl1-mesa-dev
    xorg-dev
    libxcb-render-util0-dev
    libxcb-xkb-dev
    libxcb-icccm4-dev
    libxcb-image0-dev
    libxcb-keysyms1-dev
    libxcb-xinerama0-dev
````

Install the dependencies with conan
````
    mkdir build
    cd build
    conan install .. --build imgui-sfml -s build_type=Debug
````

## Build
Build using cmake with default unix generator:

````
    cmake .. -DENABLE_CONAN=ON
    cmake --build ./ -- -j8
````

Build using ninja generator:

````
    cmake .. -DENABLE_CONAN=ON -G "Ninja"
    ninja -j8
````

## Run 

    ./game_project_cpp

## spdlog format
[spdlog](https://github.com/gabime/spdlog/wiki/3.-Custom-formatting)
