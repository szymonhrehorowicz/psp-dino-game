cmake_minimum_required(VERSION 3.11)

project(tests)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)

add_subdirectory(../library library)

add_executable(${PROJECT_NAME} 
    signal_test.cpp
    edge_detector_test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    library
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})