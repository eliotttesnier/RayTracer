add_subdirectory(core)
add_subdirectory(Lights)
add_subdirectory(Primitives)

target_include_directories(raytracer PRIVATE
    ./
)