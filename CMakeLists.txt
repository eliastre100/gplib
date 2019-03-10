cmake_minimum_required(VERSION 3.13)
project(gplib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

###########################
## GTest
###########################
ADD_SUBDIRECTORY (vendors/gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

##########################
## gpLib
##########################
find_package(LibZip)

include_directories(includes)

set(SOURCE_FILES gplib/filesystem/ZipFilesystem.cpp includes/exceptions/NoSuchFile.hpp gplib/exceptions/NoSuchFile.cpp gplib/exceptions/BadFileFormat.cpp includes/exceptions/BadFileFormat.hpp)

add_library(gplib ${SOURCE_FILES})
target_link_libraries(gplib ${LIBZIP_LIBRARY})

##########################
## Unit tests
##########################
add_executable(runUnitTests tests/filesystem/ZipFilesystem.spec.cpp)
target_link_libraries(runUnitTests gtest gtest_main gplib)
add_test(runUnitTests runUnitTests)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})