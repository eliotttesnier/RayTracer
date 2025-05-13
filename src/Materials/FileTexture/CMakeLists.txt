add_library(FileTextureMaterial SHARED
        FileTextureMaterial.cpp
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

add_custom_command(TARGET FileTextureMaterial POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:FileTextureMaterial>/libFileTextureMaterial.so"
        "${CMAKE_BINARY_DIR}/plugins/libFileTextureMaterial.so")


add_custom_target(copy_FileTextureMaterial ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libFileTextureMaterial.so" "${CMAKE_BINARY_DIR}/../plugins/libFileTextureMaterial.so"
        DEPENDS FileTextureMaterial)

if(NOT SFML_FOUND)
        find_package(SFML COMPONENTS graphics window system REQUIRED)
endif()

target_link_libraries(FileTextureMaterial
        sfml-graphics
        sfml-window
        sfml-system
)
