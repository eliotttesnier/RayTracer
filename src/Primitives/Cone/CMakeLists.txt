add_library(Cone SHARED
    Cone.cpp
    Cone.hpp
    EntyPoint.cpp
    ../APrimitive.cpp
)

target_include_directories(Cone PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Cone PRIVATE Math)

add_custom_command(TARGET Cone POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Cone>/libCone.so"
        "${CMAKE_BINARY_DIR}/plugins/libCone.so")


add_custom_target(copy_Cone ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libCone.so" "${CMAKE_BINARY_DIR}/../plugins/libCone.so"
        DEPENDS Cone)
