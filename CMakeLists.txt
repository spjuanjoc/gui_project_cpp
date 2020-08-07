cmake_minimum_required(VERSION 3.10)

project(game_project_cpp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Options
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
option(ENABLE_TESTS "Enable tests" OFF)
option(ENABLE_CONAN "Enable Conan" OFF)

# Sources common for all platforms .cpp .hpp
set(SOURCES
    src/main.cpp
    src/Foo/Foo.cpp
    # src/other.cpp
    )

# Setup file extensions for platform specific sources: Linux, Windows, and Apple (Darwin)
#if(${CMAKE_SYSTEM_NAME} MATCHES "Linux") # .cc .hh
#  set(PLATFORM_EXTENSION cc)
#elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows") # .cxx .hxx
#  set(PLATFORM_EXTENSION cxx)
#elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # .mm .h
#  set(PLATFORM_EXTENSION mm)
#endif()
#
#set(SOURCES ${SOURCES} src/Foo/Foo.${PLATFORM_EXTENSION})

message("Platform: ${CMAKE_SYSTEM_NAME}")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lImGui-SFML -lsfml-graphics-s -lsfml-window-s -lsfml-network-s")

# Set the project as an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# --
# --
# target instructions must be after add_executable or add_library instructions

# Specific features
# target_compile_features(starter_cpp PRIVATE cxx_lambda_init_captures)

# Get the headers
set(INCLUDES include include/Foo)
include_directories(PUBLIC ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

# Compiler options
include(cmake/CompilerOptions.cmake)
set_project_options(${PROJECT_NAME})

# Check enabled options
if (ENABLE_PCH)
  # Since CMake 3.15
  target_precompile_headers(${PROJECT_NAME} INTERFACE <vector> <string> <map> <utility>)
  message("PCH enabled")
endif ()

if (ENABLE_TESTS)
  enable_testing()
  add_subdirectory(test)
elseif ()
  message("Tests not included")
endif ()

if (ENABLE_FUZZ_TESTS)
  add_subdirectory(fuzz_test)
elseif ()
  message("Fuzz Tests not included")
endif ()

if (ENABLE_CONAN)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#  conan_basic_setup()
  conan_basic_setup(TARGETS)

  message("Conan libs: ${CONAN_LIBS}")
  message("Conan dir libs: ${CONAN_LIB_DIRS}")

#  target_include_directories(${PROJECT_NAME} PRIVATE ${CONAN_LIB_DIRS})
  conan_target_link_libraries(${PROJECT_NAME})
endif ()
