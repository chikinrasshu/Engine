cmake_minimum_required(VERSION 3.28)
project(chk_engine
    DESCRIPTION "Simple 2D engine"
    VERSION 0.0.1
    LANGUAGES C
)

add_subdirectory("ext")
add_subdirectory("lib")
add_subdirectory("bin")
