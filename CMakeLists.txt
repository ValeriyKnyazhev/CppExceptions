cmake_minimum_required(VERSION 3.6)
project(CppExceptions)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MyException.h)
add_executable(CppExceptions ${SOURCE_FILES})