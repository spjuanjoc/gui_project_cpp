cmake_minimum_required(VERSION 3.24)

project(gui_project_cpp
  VERSION "0.1.0"
  DESCRIPTION "A GUI in C++ with ImGui+SFML"
  LANGUAGES CXX
)

# Options
option(ENABLE_COVERAGE "Enable gcov coverage"              False)
option(ENABLE_PCH      "Enable Precompiled Headers"        False)
option(ENABLE_TESTS    "Enable tests"                      False)
option(ENABLE_WERROR   "Treat compiler warnings as errors" False)


# GLOB source files
file(GLOB_RECURSE
  SOURCE_FILES
    src/*.cpp
    src/main.cpp
)


## Set the project as an executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


## Compiler options
include(cmake/CompilerOptions.cmake)
set_compiler_options(${PROJECT_NAME})


## Find third-party packages
find_package(argparse REQUIRED)
find_package(fmt      REQUIRED)
find_package(ImGui-SFML REQUIRED)
find_package(spdlog   REQUIRED)


## Target
target_include_directories(${PROJECT_NAME}
  SYSTEM PRIVATE # These directories must be placed before other non-system directories
    ${argparse_INCLUDE_DIRS}
  PUBLIC
    include
)


target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${fmt_LIBRARIES}
    ${ImGui-SFML_LIBRARIES}
    ${sigc++-3_LIBRARIES}
    ${spdlog_LIBRARIES}
)


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
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "/opt/${PROJECT_NAME}")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/share/" DESTINATION "/opt/${PROJECT_NAME}/share")
install(DIRECTORY "${PROJECT_BINARY_DIR}/logs" DESTINATION "/opt/${PROJECT_NAME}/logs")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Juan Jose Castellanos <juancho.312@hotmail.com>")
include(CPack)
