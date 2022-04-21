cmake_minimum_required(VERSION 3.21)
project(Final_Project)

set(CMAKE_CXX_STANDARD 14)

# check for windows
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(SOURCE_FILES main.cpp)

include_directories(sqlite_dir)

add_subdirectory(sqlite_dir)

add_executable(main_executable ${SOURCE_FILES})

target_link_libraries(main_executable f_func)

#add_executable("${PROJECT_NAME}" main.cpp)
#include_directories("C:\\sqlite3\\sqlite3.h")
#include_directories("C:\\sqlite3\\sqlite3.c")
#
#add_library(sqlite_dir/sqlite3.c main.cpp)
#add_library(sqlite_dir/sqlite3.h main.cpp)