add_library(TransparencyMaterial SHARED
        TransparencyMaterial.cpp
        EntryPoint.cpp
        ../AMaterial.cpp
)

add_custom_command(TARGET TransparencyMaterial POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:TransparencyMaterial>/libTransparencyMaterial.so"
        "${CMAKE_BINARY_DIR}/plugins/libTransparencyMaterial.so"
)

add_custom_target(copy_TransparencyMaterial ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libTransparencyMaterial.so" "${CMAKE_BINARY_DIR}/../plugins/libTransparencyMaterial.so"
        DEPENDS TransparencyMaterial
)

target_link_libraries(TransparencyMaterial PRIVATE
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
