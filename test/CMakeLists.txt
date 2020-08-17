
set(TEST_SOURCES
    Foo/FooTest.cpp
)

set(TEST_NAME FooTest)
#  add_definitions(-DGTEST_LANGUAGE_CXX11)
add_executable(${TEST_NAME} ${TEST_SOURCES})
add_test(${TEST_NAME} ${TEST_NAME})
message("Tests included")

# Link googletest with the current project
# Needs to add gtest/1.10.0 to conanfile
#if (ENABLE_CONAN)
#  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#  conan_basic_setup(TARGETS)
#  conan_target_link_libraries(${TEST_NAME} CONAN_PKG::gtest CONAN_PKG::gmock)
#endif ()
