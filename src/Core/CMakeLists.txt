set(INCROOT ${PROJECT_SOURCE_DIR}/src/Core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Core)

set(SRC
    ${SRCROOT}/main.cpp
    ${SRCROOT}/Renderer.cpp
)

set(HEADER_DIRECTORIES ${INCROOT})
include_directories(${HEADER_DIRECTORIES})

add_executable(raytracer
    ${SRC}
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
    Graphic
    math
    graphic_renderer
    sfml-graphics
    sfml-window
    sfml-system
)

target_include_directories(raytracer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command(TARGET raytracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:raytracer>"
        "${PROJECT_SOURCE_DIR}/raytracer")
