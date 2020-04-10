cmake_minimum_required(VERSION 3.0.0)
project(proptest VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(./rapidcheck)

add_executable(proptest
    proptest.cpp
)

target_link_libraries(proptest
    PRIVATE rapidcheck
)
