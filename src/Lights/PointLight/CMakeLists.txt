add_library(PointLight SHARED
        ../ALight.hpp
        ../ALight.cpp
        ../ILight.hpp
        PointLight.cpp
        PointLight.hpp
        EntyPoint.cpp
)

add_custom_command(TARGET PointLight POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:PointLight>/libPointLight.so"
        "${CMAKE_BINARY_DIR}/plugins/libPointLight.so")


add_custom_target(copy_PointLight ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libPointLight.so" "${CMAKE_BINARY_DIR}/../plugins/libPointLight.so"
        DEPENDS PointLight)

