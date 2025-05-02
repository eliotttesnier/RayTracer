set(LIGHT_FACTORY_SRC
    LightFactory.cpp
)

set(LIGHT_FACTORY_INC
    LightFactory.hpp
    ILightFactory.hpp
)

add_library(LightFactory SHARED ${LIGHT_FACTORY_SRC} ${LIGHT_FACTORY_INC})