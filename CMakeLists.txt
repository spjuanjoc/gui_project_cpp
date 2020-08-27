cmake_minimum_required(VERSION 3.10)

project(gui_project_cpp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

## Available Options
option(ENABLE_PCH   "Enable Precompiled Headers" OFF)
option(ENABLE_TESTS "Enable tests" OFF)
option(ENABLE_CONAN "Enable Conan" OFF)

## Sources common for all platforms .cpp .hpp
set(SOURCES
    src/main.cpp
    src/Events/Events.cpp
    )

#set(SOURCES ${SOURCES} src/Foo/Foo.${PLATFORM_EXTENSION})

message("Platform: ${CMAKE_SYSTEM_NAME}")

## Set the project as an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# --
# --
##! target instructions must be after add_executable or add_library instructions

## Specific features
# target_compile_features(${PROJECT_NAME} PRIVATE cxx_lambda_init_captures)

## Get the headers
set(INCLUDES include include/Events include/Window)
include_directories(PUBLIC ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

## Compiler options
include(cmake/CompilerOptions.cmake)
set_project_options(${PROJECT_NAME})

## Check custom options
if (ENABLE_PCH) # Since CMake 3.15
  target_precompile_headers(${PROJECT_NAME} INTERFACE <vector> <string> <map> <utility>)
  message("PCH enabled")
endif ()

if (ENABLE_TESTS)
  enable_testing()
  add_subdirectory(test)
elseif ()
  message("Tests not included")
endif ()

#if (ENABLE_FUZZ_TESTS)
#  add_subdirectory(fuzz_test)
#elseif ()
#  message("Fuzz Tests not included")
#endif ()

if (ENABLE_CONAN)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
  conan_target_link_libraries(${PROJECT_NAME} PRIVATE
      CONAN_PKG::ImGui-SFML
      CONAN_PKG::spdlog
      CONAN_PKG::fmt
      CONAN_PKG::docopt
      )
#  message("Conan libs: ${CONAN_LIBS}")
endif ()


## Install commands
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "/opt/gui_project_cpp"
    )

SET(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Juan Caste <juancho.312@hotmail.com>")
include(CPack)