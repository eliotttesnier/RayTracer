add_library(OBJ SHARED
    OBJ.cpp
    OBJ.hpp
    EntryPoint.cpp
    ../APrimitive.cpp
    ../Triangles/Triangles.cpp
    ../Triangles/Triangles.hpp
)

target_include_directories(OBJ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(OBJ PRIVATE Math)

add_custom_command(TARGET OBJ POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:OBJ>/libOBJ.so"
        "${CMAKE_BINARY_DIR}/plugins/libOBJ.so")

add_custom_target(copy_OBJ ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libOBJ.so" "${CMAKE_BINARY_DIR}/../plugins/libOBJ.so"
        DEPENDS OBJ)
