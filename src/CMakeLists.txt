add_subdirectory(Math)
add_subdirectory(Graphic)
add_subdirectory(Lights)
add_subdirectory(Primitives)
add_subdirectory(Parser)
add_subdirectory(GraphicRenderer)
add_subdirectory(Core)

target_include_directories(raytracer PRIVATE
    ./
)
