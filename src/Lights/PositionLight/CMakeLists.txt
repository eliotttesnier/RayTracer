add_library(PositionLight SHARED
        ../ALight.hpp
        ../ALight.cpp
        ../ILight.hpp
        PositionLight.cpp
        PositionLight.hpp
        EntyPoint.cpp
)

add_custom_command(TARGET PositionLight POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:PositionLight>/libPositionLight.so"
        "${CMAKE_BINARY_DIR}/plugins/libPositionLight.so")


add_custom_target(copy_PositionLight ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libPositionLight.so" "${CMAKE_BINARY_DIR}/../plugins/libPositionLight.so"
        DEPENDS PositionLight)

