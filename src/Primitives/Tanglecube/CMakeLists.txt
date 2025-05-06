add_library(Tanglecube SHARED
    Tanglecube.cpp
    Tanglecube.hpp
    EntyPoint.cpp
    ../APrimitive.cpp
)

add_custom_command(TARGET Tanglecube POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Tanglecube>/libTanglecube.so"
        "${CMAKE_BINARY_DIR}/plugins/libTanglecube.so")


add_custom_target(copy_Tanglecube ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libTanglecube.so" "${CMAKE_BINARY_DIR}/../plugins/libTanglecube.so"
        DEPENDS Tanglecube)
