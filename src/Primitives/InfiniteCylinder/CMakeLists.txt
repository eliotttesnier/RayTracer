add_library(InfiniteCylinder SHARED
    InfiniteCylinder.cpp
    InfiniteCylinder.hpp
    EntryPoint.cpp
    ../APrimitive.cpp
)

target_include_directories(InfiniteCylinder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(InfiniteCylinder PRIVATE Math)

add_custom_command(TARGET InfiniteCylinder POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:InfiniteCylinder>/libInfiniteCylinder.so"
        "${CMAKE_BINARY_DIR}/plugins/libInfiniteCylinder.so")

add_custom_target(copy_InfiniteCylinder ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libInfiniteCylinder.so" "${CMAKE_BINARY_DIR}/../plugins/libInfiniteCylinder.so"
        DEPENDS InfiniteCylinder)
