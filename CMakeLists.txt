cmake_minimum_required(VERSION 3.10)

project(gui_project_cpp
  VERSION "0.0.2"
  DESCRIPTION "GUI project"
  LANGUAGES CXX
)


option(ENABLE_PCH   "Enable Precompiled Headers"  False)
option(ENABLE_TESTS "Enable tests"                False)


file(GLOB_RECURSE
  SOURCE_FILES
    src/*.cpp
    src/main.cpp
)


## Set the project as an executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


## Compiler options
include(cmake/CompilerOptions.cmake)
set_project_options(${PROJECT_NAME})


## Setup Conan
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD
      "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
      "${CMAKE_BINARY_DIR}/conan.cmake"
      )
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)
#conan_add_remote(NAME conancenter URL https://center.conan.io)
conan_check(REQUIRED)
conan_cmake_autodetect(settings)
#conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_CURRENT_SOURCE_DIR}/conanfile.txt BUILD missing SETTINGS ${settings})
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP NO_OUTPUT_DIRS BUILD missing SETTINGS ${settings})


## Find third-party packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(fmt REQUIRED)
find_package(ImGui-SFML REQUIRED)
find_package(spdlog REQUIRED)
find_package(docopt REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    fmt::fmt
    ImGui-SFML::ImGui-SFML
    spdlog::spdlog
    docopt::docopt
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE include)


## Check custom options
if (ENABLE_PCH) # Since CMake 3.15
  target_precompile_headers(${PROJECT_NAME} INTERFACE <vector> <string> <map> <utility>)
  message("PCH enabled")
endif ()

if (ENABLE_TESTS)
  message(STATUS "Tests enabled")
  enable_testing() # Must be placed before add_subdirectory
  add_subdirectory(test)
endif ()


## Copy resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


## Install commands
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "/opt/${PROJECT_NAME}"
    )

SET(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Juan Jose Castellanos <juancho.312@hotmail.com>")
include(CPack)
