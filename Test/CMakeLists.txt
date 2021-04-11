project("DIMENSIONALITY_TEST")

cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories($(CMAKE_CURRENT_SOURCE_DIR)/source)

add_executable(cmake_test Dimensionality_Test/Dimensionality_Test.cpp)