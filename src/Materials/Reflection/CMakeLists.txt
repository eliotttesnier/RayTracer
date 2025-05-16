add_library(ReflectionMaterial SHARED
        ReflectionMaterial.cpp
        EntryPoint.cpp
        ../AMaterial.cpp
)

add_custom_command(TARGET ReflectionMaterial POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:ReflectionMaterial>/libReflectionMaterial.so"
        "${CMAKE_BINARY_DIR}/plugins/libReflectionMaterial.so"
)

add_custom_target(copy_ReflectionMaterial ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libReflectionMaterial.so" "${CMAKE_BINARY_DIR}/../plugins/libReflectionMaterial.so"
        DEPENDS ReflectionMaterial
)

target_link_libraries(ReflectionMaterial PRIVATE
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
