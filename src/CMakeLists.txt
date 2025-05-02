add_subdirectory(Math)
add_subdirectory(Graphic)
add_subdirectory(Lights)
add_subdirectory(Primitives)
add_subdirectory(Parser)
add_subdirectory(GraphicRenderer)
add_subdirectory(Core)
add_subdirectory(Factory)

add_executable(raytracer
    main.cpp
)

set(LIGHTS
        AmbientLight
        DirectionalLight
)

set(PRIMITIVES
        Sphere
        Plane
        Cylinder
        Cone
)

target_link_libraries(raytracer PRIVATE
        ${LIGHTS}
        ${PRIMITIVES}
        Factory
        Graphic
        Core
        math
        parser
        graphic_renderer
        sfml-graphics
        sfml-window
        sfml-system
)

target_include_directories(raytracer PRIVATE
    ./
)

add_custom_command(TARGET raytracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:raytracer>"
        "${CMAKE_BINARY_DIR}/raytracer")

add_custom_command(TARGET raytracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:raytracer>"
        "${CMAKE_BINARY_DIR}/../raytracer")

target_include_directories(PrimitivesFactory PUBLIC
./
)

