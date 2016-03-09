cmake_minimum_required(VERSION 3.3)
project(seriously)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    test_seriously.cpp
    catch.hpp
    Seriously.h
    Seriously.impl.hpp)

add_executable(test_seriously ${SOURCE_FILES})
