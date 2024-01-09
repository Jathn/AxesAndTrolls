cmake_minimum_required(VERSION 3.12)

project(A_T)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "lib/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

file(GLOB_RECURSE HEADERS "include/*.hpp")

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")

add_executable(A_T ${TEST_SOURCES} ${SOURCES} ${HEADERS})
target_link_libraries(A_T PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(A_T PRIVATE "include")
