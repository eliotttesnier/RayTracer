add_library(AmbientLight SHARED
        AmbientLight.cpp
        AmbientLight.hpp
)

add_custom_command(TARGET AmbientLight POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:AmbientLight>/libAmbientLight.so"
        "$<TARGET_FILE_DIR:AmbientLight>/../../../plugins/libAmbientLight.so")


add_custom_target(copy_AmbientLight ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:AmbientLight>/../../.."
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:AmbientLight>" "$<TARGET_FILE_DIR:AmbientLight>/../../../../plugins/libAmbientLight.so"
        DEPENDS AmbientLight)
