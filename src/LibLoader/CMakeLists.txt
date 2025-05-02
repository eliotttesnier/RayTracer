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
