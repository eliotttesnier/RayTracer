cmake_minimum_required(VERSION 3.25)
project(raytracer)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
add_compile_options("-fno-gnu-unique")

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_subdirectory(src)
