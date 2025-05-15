add_library(InfiniteCone SHARED
    InfiniteCone.cpp
    InfiniteCone.hpp
    EntryPoint.cpp
    ../APrimitive.cpp
)

target_include_directories(InfiniteCone PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(InfiniteCone PRIVATE Math)

add_custom_command(TARGET InfiniteCone POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:InfiniteCone>/libInfiniteCone.so"
        "${CMAKE_BINARY_DIR}/plugins/libInfiniteCone.so")

add_custom_target(copy_InfiniteCone ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libInfiniteCone.so" "${CMAKE_BINARY_DIR}/../plugins/libInfiniteCone.so"
        DEPENDS InfiniteCone)
