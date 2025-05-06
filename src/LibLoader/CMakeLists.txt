add_library(LibLoader STATIC
        LibLoader.cpp
        LibLoader.hpp
        Exception.hpp
        LoaderType.hpp
)

target_include_directories(AmbientLight PRIVATE
        ./
)

target_include_directories(DirectionalLight PRIVATE
        ./
)


target_include_directories(Plane PRIVATE
        ./
)

target_include_directories(Cylinder PRIVATE
        ./
)

target_include_directories(Cone PRIVATE
        ./
)

target_include_directories(Sphere PRIVATE
        ./
)

target_include_directories(Torus PRIVATE
        ./
)

target_include_directories(Tanglecube PRIVATE
        ./
)
