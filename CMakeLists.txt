cmake_minimum_required(VERSION 3.12)

project(Axes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized")

set(SFML_DIR "lib/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

file(GLOB_RECURSE HEADERS "include/*.hpp")

file(GLOB_RECURSE SOURCES "src/*.cpp")

set(RESOURCE_FILES "../resources/app.rc")
add_executable(Axes ${TEST_SOURCES} ${SOURCES} ${HEADERS} ${RESOURCE_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_link_libraries(Axes PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
else()
    target_link_libraries(Axes PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
endif()
target_include_directories(Axes PRIVATE "include")

add_custom_command(TARGET Axes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:Axes>/resources
)

add_custom_command(TARGET Axes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/lib/SFML-2.6.1/bin
    $<TARGET_FILE_DIR:Axes>
)
