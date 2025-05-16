add_library(RefractionMaterial SHARED
        RefractionMaterial.cpp
        EntryPoint.cpp
        ../AMaterial.cpp
)

add_custom_command(TARGET RefractionMaterial POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:RefractionMaterial>/libRefractionMaterial.so"
        "${CMAKE_BINARY_DIR}/plugins/libRefractionMaterial.so"
)

add_custom_target(copy_RefractionMaterial ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libRefractionMaterial.so" "${CMAKE_BINARY_DIR}/../plugins/libRefractionMaterial.so"
        DEPENDS RefractionMaterial
)

target_link_libraries(RefractionMaterial PRIVATE
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