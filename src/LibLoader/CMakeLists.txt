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

target_include_directories(PointLight PRIVATE
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
target_include_directories(Triangles PRIVATE
        ./
)
target_include_directories(Tanglecube PRIVATE
        ./
)

target_include_directories(DefaultMaterial PRIVATE
        ./
)

target_include_directories(TransparencyMaterial PRIVATE
        ./
)

target_include_directories(ReflectionMaterial PRIVATE
        ./
)

target_include_directories(ChessPatternMaterial PRIVATE
        ./
)

target_include_directories(FileTextureMaterial PRIVATE
        ./
)

target_include_directories(NormalMappingMaterial PRIVATE
        ./
)

target_include_directories(OBJ PRIVATE
        ./
)

target_include_directories(RefractionMaterial PRIVATE
        ./
)

target_include_directories(PerlinNoiseMaterial PRIVATE
        ./
)

target_include_directories(Rectangle PRIVATE
        ./
)
