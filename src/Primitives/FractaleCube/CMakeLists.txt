add_library(FractaleCube SHARED
    FractaleCube.cpp
    FractaleCube.hpp
    EntryPoint.cpp
    ../APrimitive.cpp
)

add_custom_command(TARGET FractaleCube POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE_DIR:FractaleCube>/libFractaleCube.so"
    "${CMAKE_BINARY_DIR}/plugins/libFractaleCube.so")

add_custom_target(copy_FractaleCube ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_BINARY_DIR}/plugins/libFractaleCube.so"
    "${CMAKE_BINARY_DIR}/../plugins/libFractaleCube.so"
    DEPENDS FractaleCube)
