add_library(AmbientLight SHARED
        ../ALight.hpp
        ../ALight.cpp
        ../ILight.hpp
        AmbientLight.cpp
        AmbientLight.hpp
        EntyPoint.cpp
)

add_custom_command(TARGET AmbientLight POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:AmbientLight>/libAmbientLight.so"
        "${CMAKE_BINARY_DIR}/plugins/libAmbientLight.so")


add_custom_target(copy_AmbientLight ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libAmbientLight.so" "${CMAKE_BINARY_DIR}/../plugins/libAmbientLight.so"
        DEPENDS AmbientLight)
