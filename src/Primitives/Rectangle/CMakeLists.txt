add_library(Rectangle SHARED
    Rectangle.cpp
    Rectangle.hpp
    EntryPoint.cpp
    ../APrimitive.cpp
)

add_custom_command(TARGET Rectangle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Rectangle>/libRectangle.so"
        "${CMAKE_BINARY_DIR}/plugins/libRectangle.so")


add_custom_target(copy_Rectangle ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libRectangle.so" "${CMAKE_BINARY_DIR}/../plugins/libRectangle.so"
        DEPENDS Rectangle)