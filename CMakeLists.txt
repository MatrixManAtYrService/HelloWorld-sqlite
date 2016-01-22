project(helloWorld)

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


# look for header files in ./include
SET(INCLUDE_DIRS "include")

# Add custom Find-.cmake path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

message("CMAKE_FIND_LIBRARY_SUFFIXES:  ${CMAKE_FIND_LIBRARY_SUFFIXES}")

# Use Boost Unit Test Framework
enable_testing()
SET(BOOST_ROOT "C:/local/boost_1_60_0")                             # FindBoost.cmake handles this on its own in the linux case
SET(BOOST_LIBRARYDIR "C:/local/boost_1_60_0/lib32-msvc-14.0")
find_package(Boost 1.60.0 COMPONENTS unit_test_framework REQUIRED)
list(APPEND INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
SET(BOOST_LINK_FLAG "-lboost_unit_test_framework")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${BOOST_LINK_FLAG}" )

# Use SQLite3
find_package(SQLite3)                                               # ./cmake/FindSQLite3.cmake handles this on its own in the linux case
if(NOT SQLite3_FOUND)
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a" ".dll" ".lib")
    find_library(SQLITE3_LIBRARY NAMES sqlite3 libsqlite3-dev HINTS "${CMAKE_SOURCE_DIR}/lib")
    if (${SQLITE3})
        MESSAGE(STATUS "Found SQLite3")
    else()
        MESSAGE(STATUS "SQLite3 library not found, see dependency.md to ensure it is in the right place.")
    endif()
    SET(SQLITE3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/sqlite3")
endif()
list(APPEND INCLUDE_DIRS ${SQLITE3_INCLUDE_DIR})

find_package(Threads REQUIRED)

# List source files here
set(HELLO_SOURCE 
    src/main.cpp
    src/helloPrinter.cpp)

# List test dependencies here
add_library(testDepends 
    src/dbAccess.cpp)

set_target_properties(testDepends PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(testDepends ${SQLITE3_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

list(REMOVE_DUPLICATES INCLUDE_DIRS)
include_directories(${INCLUDE_DIRS})

project(helloWorld C CXX)
list(REMOVE_DUPLICATES HELLO_SOURCE)
add_executable(hello.exe ${HELLO_SOURCE})
target_link_libraries(hello.exe sqlite3 ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

# Look for tests in ./test
# source for this loop: http://neyasystems.com/an-engineers-guide-to-unit-testing-cmake-and-boost-unit-tests/
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
foreach(testSrc ${TEST_SRCS})
        get_filename_component(testName ${testSrc} NAME_WE)
        add_executable(${testName} ${testSrc})

        #link to Boost libraries AND your targets and dependencies
        target_link_libraries(${testName} ${Boost_LIBRARIES} ${SQLITE_LIBRARY} sqlite3 testDepends)
  

        # Compiled test binaries go in ./testBin
        set_target_properties(${testName} PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin)

        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName} 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
endforeach(testSrc)

