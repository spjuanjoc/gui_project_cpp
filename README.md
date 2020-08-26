# gui_project_cpp

GUI project using ImGui-SFML.

## Install dependencies with Conan

1. Setup bincrafters

    `conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`

2. Install extra packages required in Linux for imgui:

    ````
    sudo apt install -y 
        libgl1-mesa-dev
        xorg-dev
        libxcb-render-util0-dev
        libxcb-xkb-dev
        libxcb-icccm4-dev
        libxcb-image0-dev
        libxcb-keysyms1-dev
        libxcb-xinerama0-dev
    ````

3. Install the dependencies with conan and build `sfml`

   ````
    mkdir build
    cd build
    conan install .. --build imgui-sfml -s build_type=Debug
    ````

## Build

1. Build in debug mode:

    ````
    cmake .. -DENABLE_CONAN=ON -DENABLE_TESTS=ON -O0 -g
    cmake --build ./ -- -j8
    ````

2. Build in release mode:

    ````
    cmake .. -DENABLE_CONAN=ON -G "Ninja" -O3 
    ninja -j8
    ````

## Run 

    ./build/gui_project_cpp

---

## spdlog and fmt::format

See about [spdlog](https://github.com/gabime/spdlog/wiki/3.-Custom-formatting)

## Notes

To install conan: `pip install --user conan`

To install ninja: `pip install --user ninja`