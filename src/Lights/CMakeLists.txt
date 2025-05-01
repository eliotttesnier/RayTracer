add_subdirectory(AmbientLight)
add_subdirectory(DirectionalLight)

set(LIGHTS_SRC
    ALight.cpp
)

add_library(Lights STATIC ${LIGHTS_SRC})
target_include_directories(Lights PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Lights AmbientLight DirectionalLight)
