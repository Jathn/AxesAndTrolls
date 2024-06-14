cmake_minimum_required(VERSION 3.12)

project(A_T)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized")

set(SFML_DIR "lib/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

file(GLOB_RECURSE HEADERS "include/*.hpp")

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(A_T ${TEST_SOURCES} ${SOURCES} ${HEADERS})
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_link_libraries(A_T PRIVATE sfml-graphics-d sfml-window-d sfml-system-d)
else()
    target_link_libraries(A_T PRIVATE sfml-graphics sfml-window sfml-system)
endif()
target_include_directories(A_T PRIVATE "include")

add_custom_command(TARGET A_T POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:A_T>/resources
)

add_custom_command(TARGET A_T POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/lib/SFML-2.6.1/bin
    $<TARGET_FILE_DIR:A_T>
)
