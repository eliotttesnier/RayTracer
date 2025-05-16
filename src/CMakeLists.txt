add_subdirectory(Math)
add_subdirectory(Graphic)
add_subdirectory(Lights)
add_subdirectory(Materials)
add_subdirectory(Primitives)
add_subdirectory(Parser)
add_subdirectory(GraphicRenderer)
add_subdirectory(Core)
add_subdirectory(Factory)
add_subdirectory(LibLoader)

add_executable(raytracer
    main.cpp
)

target_link_libraries(raytracer PRIVATE
        LibLoader
        Graphic
        Core
        Math
        Parser
        GraphicRenderer
        sfml-graphics
        sfml-window
        sfml-system
)

target_link_libraries(Core PRIVATE
    Factory
    LibLoader
)

target_include_directories(raytracer PUBLIC
    ./
)

add_custom_command(TARGET raytracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:raytracer>"
        "${CMAKE_BINARY_DIR}/raytracer")

add_custom_command(TARGET raytracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:raytracer>"
        "${CMAKE_BINARY_DIR}/../raytracer")

target_include_directories(Core PUBLIC
        ./
)

target_include_directories(PrimitivesFactory PUBLIC
    ./
)

target_include_directories(LightFactory PUBLIC
    ./
)

