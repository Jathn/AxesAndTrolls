cmake_minimum_required(VERSION 3.12)

project(A_T)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(A_T ${SOURCES} ${HEADERS})

target_include_directories(A_T PRIVATE "include")
