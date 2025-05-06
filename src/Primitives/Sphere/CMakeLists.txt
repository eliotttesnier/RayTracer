add_library(Sphere SHARED
    Sphere.cpp
    Sphere.hpp
    EntyPoint.cpp
    ../APrimitive.cpp
)

add_custom_command(TARGET Sphere POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Sphere>/libSphere.so"
        "${CMAKE_BINARY_DIR}/plugins/libSphere.so")


add_custom_target(copy_Sphere ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libSphere.so" "${CMAKE_BINARY_DIR}/../plugins/libSphere.so"
        DEPENDS Sphere)
