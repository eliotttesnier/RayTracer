add_library(Mobius SHARED
    Mobius.cpp
    Mobius.hpp
    EntryPoint.cpp
    ../APrimitive.cpp
)

add_custom_command(TARGET Mobius POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Mobius>/libMobius.so"
        "${CMAKE_BINARY_DIR}/plugins/libMobius.so")


add_custom_target(copy_Mobius ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libMobius.so" "${CMAKE_BINARY_DIR}/../plugins/libMobius.so"
        DEPENDS Mobius)