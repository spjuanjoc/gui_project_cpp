set(TEST_NAME FooTest)

set(TEST_SOURCES
    Foo/FooTest.cpp
)

#  add_definitions(-DGTEST_LANGUAGE_CXX11)
add_executable(${TEST_NAME} ${TEST_SOURCES})
add_test(${TEST_NAME} ${TEST_NAME})
message("Tests included")

target_include_directories(${TEST_NAME} PRIVATE include)
# Coverage with gcov
#target_compile_options(profile-arcs test-coverage)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
# Link googletest with the current project
# Needs to add gtest/1.10.0 to conanfile
#if (ENABLE_CONAN)
#  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#  conan_basic_setup(TARGETS)
#  conan_target_link_libraries(${TEST_NAME} CONAN_PKG::gtest CONAN_PKG::gmock)
#endif ()
