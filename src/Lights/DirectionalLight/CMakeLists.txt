add_library(DirectionalLight SHARED
        ../ALight.hpp
        ../ALight.cpp
        ../ILight.hpp
        DirectionalLight.cpp
        DirectionalLight.hpp
        EntyPoint.cpp
)

add_custom_command(TARGET DirectionalLight POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:DirectionalLight>/libDirectionalLight.so"
        "${CMAKE_BINARY_DIR}/plugins/libDirectionalLight.so")


add_custom_target(copy_DirectionalLight ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libDirectionalLight.so" "${CMAKE_BINARY_DIR}/../plugins/libDirectionalLight.so"
        DEPENDS DirectionalLight)

