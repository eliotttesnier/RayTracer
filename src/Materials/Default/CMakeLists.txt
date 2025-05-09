add_library(DefaultMaterial SHARED
        DefaultMaterial.cpp
        EntryPoint.cpp
        ../AMaterial.cpp
)

add_custom_command(TARGET DefaultMaterial POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:DefaultMaterial>/libDefaultMaterial.so"
        "${CMAKE_BINARY_DIR}/plugins/libDefaultMaterial.so")


add_custom_target(copy_DefaultMaterial ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/../plugins"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/plugins/libDefaultMaterial.so" "${CMAKE_BINARY_DIR}/../plugins/libDefaultMaterial.so"
        DEPENDS DefaultMaterial)
