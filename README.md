# game_project_cpp
Game project

## Install dependencies with Conan

Setup bincrafters
    
    `$ conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`


````
    libgl1-mesa-dev
    xorg-dev
    libxcb-render-util0-dev
    libxcb-xkb-dev
    libxcb-icccm4-dev
    libxcb-image0-dev
    libxcb-keysyms1-dev
    libxcb-xinerama0-dev
    
    mkdir build
    cd build
    conan install .. --build imgui-sfml -s build_type=Debug
````