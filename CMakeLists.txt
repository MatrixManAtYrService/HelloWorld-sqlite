cmake_minimum_required(VERSION 2.8.9)
project(HelloWorld C CXX)
message(STATUS "Processing ${CMAKE_CURRENT_LIST_FILE}")

# paths in comments are relative to PROECT_ROOT, 
# which is the directory containing this file.
get_filename_component(PROJECT_ROOT ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
set(TEST_ROOT ${PROJECT_ROOT}/test)
set(TEST_BIN ${CMAKE_BINARY_DIR}/testBin)

message(STATUS "Project Root:" ${PROJECT_ROOT})

# Compiled libraries go in ./lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_ROOT}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_ROOT}/lib)

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

# Look for dlls too
#SET(CMAKE_FIND_LIBRARY_PREFIXES "" "lib")
#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a" ".dll" ".lib")

# Use Boost Unit Test Framework
enable_testing()
SET(BOOST_ROOT "C:/Boost")                             # FindBoost.cmake handles this on its own in the linux case
SET(BOOST_LIBRARYDIR "C:/Boost/lib")
SET(BOOST_INCLUDEDIR "C:/Boost/include/boost-1_60")
find_package(Boost 1.60.0 COMPONENTS unit_test_framework REQUIRED)
list(APPEND INCLUDE_DIRS ${Boost_INCLUDE_DIRS})

if(MSVC)                        # Microsoft uses magic to handle this
    SET(BOOST_LINK_FLAG "")
else()
    SET(BOOST_LINK_FLAG "-lboost_unit_test_framework")
endif()

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${BOOST_LINK_FLAG}" )
MESSAGE(STATUS "boost flags: " ${BOOST_LINK_FLAG})
MESSAGE(STATUS "boost libraries: " ${Boost_LIBRARIES})

# Use SQLite3
# see ./cmake/FindSQLite3.cmake for details about where find_package looks
set(SQLITE3_FOUND False)
find_package(SQLite3)

SET(SQLITE3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/sqlite3")
list(APPEND INCLUDE_DIRS ${SQLITE3_INCLUDE_DIR})

find_package(Threads REQUIRED)

# List source files here
set(HELLO_SOURCE 
    src/main.cpp
    src/helloPrinter.cpp)

# List test dependencies here
add_library(dbAccess
    src/dbAccess.cpp)

set_target_properties(dbAccess PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(dbAccess ${SQLITE3_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

list(REMOVE_DUPLICATES INCLUDE_DIRS)
include_directories(${INCLUDE_DIRS})

project(helloWorld C CXX)
list(REMOVE_DUPLICATES HELLO_SOURCE)
add_executable(hello.exe ${HELLO_SOURCE})
target_link_libraries(hello.exe ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

add_executable(test_dbAccess ${TEST_ROOT}/sampleDB.cpp)
target_link_libraries(test_dbAccess ${Boost_LIBRARIES} ${SQLITE_LIBRARY} dbAccess)
set_target_properties(test_dbAccess PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin)
add_test(NAME test_dbAccess
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin 
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )

# Look for tests in ./test
## source for this loop: http://neyasystems.com/an-engineers-guide-to-unit-testing-cmake-and-boost-unit-tests/
#file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
#foreach(testSrc ${TEST_SRCS})
#        get_filename_component(testName ${testSrc} NAME_WE)
#        add_executable(${testName} ${testSrc})
#
#        #link to Boost libraries AND your targets and dependencies
#        target_link_libraries(${testName} ${Boost_LIBRARIES} ${SQLITE_LIBRARY} testDepends)
#  
#
#        # Compiled test binaries go in ./testBin
#        set_target_properties(${testName} PROPERTIES 
#            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin)
#
#        #Notice the WORKING_DIRECTORY and COMMAND
#        add_test(NAME ${testName} 
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin 
#                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
#endforeach(testSrc)

