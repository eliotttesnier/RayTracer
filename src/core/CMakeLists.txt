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
)

target_link_libraries(raytracer PRIVATE ${LIGHTS} ${PRIMITIVES})