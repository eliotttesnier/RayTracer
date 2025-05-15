add_library(Cylinder SHARED
    Cylinder.cpp
    Cylinder.hpp
    EntyPoint.cpp
    ../APrimitive.cpp
)

target_include_directories(Cylinder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Cylinder PRIVATE Math)

add_custom_command(TARGET Cylinder POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Cylinder>/libCylinder.so"
        "${CMAKE_BINARY_DIR}/plugins/libCylinder.so")


add_custom_target(copy_Cylinder ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libCylinder.so" "${CMAKE_BINARY_DIR}/../plugins/libCylinder.so"
        DEPENDS Cylinder)
