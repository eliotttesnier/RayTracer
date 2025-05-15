add_library(NormalMappingMaterial SHARED
        NormalMappingMaterial.cpp
        EntryPoint.cpp
        ../AMaterial.cpp
        ../../Primitives/APrimitive.cpp
        ../../Math/Point3D.cpp
        ../../Primitives/Plane/Plane.cpp
        ../../Primitives/InfiniteCone/InfiniteCone.cpp
        ../../Primitives/InfiniteCylinder/InfiniteCylinder.cpp
        ../../Primitives/Sphere/Sphere.cpp
        ../../Primitives/Cone/Cone.cpp
        ../../Primitives/Cylinder/Cylinder.cpp
)

add_custom_command(TARGET NormalMappingMaterial POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:NormalMappingMaterial>/libNormalMappingMaterial.so"
        "${CMAKE_BINARY_DIR}/plugins/libNormalMappingMaterial.so")


add_custom_target(copy_NormalMappingMaterial ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libNormalMappingMaterial.so" "${CMAKE_BINARY_DIR}/../plugins/libNormalMappingMaterial.so"
        DEPENDS NormalMappingMaterial)

if(NOT SFML_FOUND)
        find_package(SFML COMPONENTS graphics window system REQUIRED)
endif()

target_link_libraries(NormalMappingMaterial
        sfml-graphics
        sfml-window
        sfml-system
)
