set(LIGHT_FACTORY_SRC
    LightFactory.cpp
    AmbientFactory.cpp
    DirectionalFactory.cpp
)

set(LIGHT_FACTORY_INC
    LightFactory.hpp
    ILightFactory.hpp
    AmbientFactory.hpp
    DirectionalFactory.hpp
)

add_library(LightFactory SHARED ${LIGHT_FACTORY_SRC} ${LIGHT_FACTORY_INC})