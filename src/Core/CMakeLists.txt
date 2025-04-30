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

target_link_libraries(raytracer PRIVATE
    ${LIGHTS}
    ${PRIMITIVES}
    Graphic
    math
    parser
)

add_custom_command(TARGET raytracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:raytracer>/raytracer"
        "$<TARGET_FILE_DIR:raytracer>/../../raytracer")


add_custom_target(copy_raytracer ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:raytracer>/../../.."
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:raytracer>" "$<TARGET_FILE_DIR:raytracer>/../../../raytracer"
        DEPENDS raytracer)
