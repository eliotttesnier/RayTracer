add_library(DirectionalLight SHARED
    DirectionalLight.cpp
    DirectionalLight.hpp
)

add_custom_command(TARGET DirectionalLight POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:DirectionalLight>/libDirectionalLight.so"
        "$<TARGET_FILE_DIR:DirectionalLight>/../../../plugins/libDirectionalLight.so")


add_custom_target(copy_DirectionalLight ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:DirectionalLight>/../../.."
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:DirectionalLight>" "$<TARGET_FILE_DIR:DirectionalLight>/../../../../plugins/libDirectionalLight.so"
        DEPENDS DirectionalLight)
