add_library(PerlinNoiseMaterial SHARED
        PerlinNoiseMaterial.cpp
        EntryPoint.cpp
        ../AMaterial.cpp
)

add_custom_command(TARGET PerlinNoiseMaterial POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:PerlinNoiseMaterial>/libPerlinNoiseMaterial.so"
        "${CMAKE_BINARY_DIR}/plugins/libPerlinNoiseMaterial.so"
)

add_custom_target(copy_PerlinNoiseMaterial ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libPerlinNoiseMaterial.so" "${CMAKE_BINARY_DIR}/../plugins/libPerlinNoiseMaterial.so"
        DEPENDS PerlinNoiseMaterial
)

target_link_libraries(PerlinNoiseMaterial PRIVATE
        Cone
        Cylinder
        Sphere
        OBJ
        Plane
        Torus
        Triangles
        Tanglecube
        FractaleCube
        InfiniteCone
        InfiniteCylinder
        Rectangle
)
