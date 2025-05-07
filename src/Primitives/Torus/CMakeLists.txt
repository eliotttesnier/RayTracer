add_library(Torus SHARED
    Torus.cpp
    Torus.hpp
    EntyPoint.cpp
    ../APrimitive.cpp
)

add_custom_command(TARGET Torus POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Torus>/libTorus.so"
        "${CMAKE_BINARY_DIR}/plugins/libTorus.so")


add_custom_target(copy_Torus ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libTorus.so" "${CMAKE_BINARY_DIR}/../plugins/libTorus.so"
        DEPENDS Torus)
