add_subdirectory(AmbientLight)
add_subdirectory(DirectionalLight)

# Create a static library that includes the light classes for linking with the main executable
add_library(Lights STATIC
    ALight.cpp
    ALight.hpp
    ILight.hpp
    AmbientLight/AmbientLight.cpp
    AmbientLight/AmbientLight.hpp
    DirectionalLight/DirectionalLight.cpp
    DirectionalLight/DirectionalLight.hpp
)

target_include_directories(Lights PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)
