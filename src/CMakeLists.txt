add_subdirectory(Core)
add_subdirectory(Math)
add_subdirectory(Graphic)
add_subdirectory(Lights)
add_subdirectory(Primitives)
add_subdirectory(Parser)

target_include_directories(raytracer PRIVATE
    ./
)