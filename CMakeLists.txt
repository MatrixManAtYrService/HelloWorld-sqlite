cmake_minimum_required(VERSION 2.8.9)

# Compiled libraries go in ./build/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiled binaries go in ./build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Use C++ 11
set(CMAKE_CXX_STANDARD 11)

# Use high warning levels and treat warnings as errors
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wconversion -pedantic")
endif()

# Declare "helloWorld" as C++ project
project(helloWorld CXX)

# look for header files in ./include
SET(INCLUDE_DIRS "include")

# Use Boost Unit Test Framework
enable_testing()
find_package(Boost 1.60.0 COMPONENTS unit_test_framework REQUIRED)
list(APPEND INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
SET(BOOST_LINK_FLAG "-lboost_unit_test_framework")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${BOOST_LINK_FLAG}" )


# List source files here
set(HELLO_SOURCE 
    src/main.cpp 
    src/helloPrinter.cpp)
#include/helloPrinter.h 


# List test dependencies here
add_library(testDepends 
    src/helloPrinter.cpp 
    src/goodbyePrinter.cpp)

set_target_properties(testDepends PROPERTIES LINKER_LANGUAGE CXX)

list(REMOVE_DUPLICATES INCLUDE_DIRS)
include_directories(${INCLUDE_DIRS})

list(REMOVE_DUPLICATES HELLO_SOURCE)
add_executable(hello.exe ${HELLO_SOURCE})

# Look for tests in ./test
# source for this loop: http://neyasystems.com/an-engineers-guide-to-unit-testing-cmake-and-boost-unit-tests/
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
foreach(testSrc ${TEST_SRCS})
        get_filename_component(testName ${testSrc} NAME_WE)
        add_executable(${testName} ${testSrc})

        #link to Boost libraries AND your targets and dependencies
        target_link_libraries(${testName} ${Boost_LIBRARIES} testDepends)

        # Compiled test binaries go in ./testBin
        set_target_properties(${testName} PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin)

        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName} 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
endforeach(testSrc)

