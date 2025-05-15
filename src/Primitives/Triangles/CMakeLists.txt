add_library(Triangles SHARED
    Triangles.cpp
    Triangles.hpp
    EntryPoint.cpp
    ../APrimitive.cpp
)

target_include_directories(Triangles PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Triangles PRIVATE Math)

add_custom_command(TARGET Triangles POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Triangles>/libTriangles.so"
        "${CMAKE_BINARY_DIR}/plugins/libTriangles.so")

add_custom_target(copy_Triangles ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libTriangles.so" "${CMAKE_BINARY_DIR}/../plugins/libTriangles.so"
        DEPENDS Triangles)
