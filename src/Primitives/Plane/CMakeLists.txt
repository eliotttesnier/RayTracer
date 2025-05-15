set(PLANE_SRC
    Plane.cpp
    EntyPoint.cpp
    ../APrimitive.cpp
)

set(PLANE_INC
    Plane.hpp
)

add_library(Plane SHARED ${PLANE_SRC} ${PLANE_INC})
target_include_directories(Plane PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Plane PRIVATE Math)

add_custom_command(TARGET Plane POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Plane>/libPlane.so"
        "${CMAKE_BINARY_DIR}/plugins/libPlane.so")


add_custom_target(copy_Plane ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libPlane.so" "${CMAKE_BINARY_DIR}/../plugins/libPlane.so"
        DEPENDS Plane)
