set(CLASSCONFIG_SRC
    LightsConfig.cpp
    CameraConfig.cpp
    PrimitivesConfig.cpp
    AntialiasingConfig.cpp
    RenderingConfig.cpp
)

set(CLASSCONFIG_HPP
    LightsConfig.hpp
    CameraConfig.hpp
    PrimitivesConfig.hpp
    AntialiasingConfig.hpp
    RenderingConfig.hpp
)

add_library(classConfig STATIC ${CLASSCONFIG_SRC} ${CLASSCONFIG_HPP})
