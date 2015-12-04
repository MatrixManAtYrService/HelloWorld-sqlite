cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(helloWorld C CXX)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories (include)

set(SOURCE 
    src/main.cpp 
    include/helloPrinter.h 
    src/helloPrinter.cpp)

add_executable(hello.exe ${SOURCE})


