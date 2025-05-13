add_library(ChessPatternMaterial SHARED
        ChessPatternMaterial.cpp
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

add_custom_command(TARGET ChessPatternMaterial POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:ChessPatternMaterial>/libChessPatternMaterial.so"
        "${CMAKE_BINARY_DIR}/plugins/libChessPatternMaterial.so")


add_custom_target(copy_ChessPatternMaterial ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libChessPatternMaterial.so" "${CMAKE_BINARY_DIR}/../plugins/libChessPatternMaterial.so"
        DEPENDS ChessPatternMaterial)
