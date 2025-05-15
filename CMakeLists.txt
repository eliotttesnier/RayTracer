cmake_minimum_required(VERSION 3.25)
project(raytracer LANGUAGES CXX CUDA)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
add_compile_options("-fno-gnu-unique")

# Activation de CUDA
find_package(CUDA)
if(CUDA_FOUND)
    message(STATUS "CUDA trouvé: ${CUDA_VERSION}")
    # Activer le code GPU
    add_definitions(-DUSE_CUDA)
    include_directories(${CUDA_INCLUDE_DIRS})
endif()

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_subdirectory(src)
