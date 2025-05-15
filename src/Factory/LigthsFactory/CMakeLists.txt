set(LIGHT_FACTORY_SRC
        LightFactory.cpp
        AmbientFactory.cpp
        DirectionalFactory.cpp
        PointFactory.cpp
)

set(LIGHT_FACTORY_INC
        LightFactory.hpp
        ILightFactory.hpp
        AmbientFactory.hpp
        DirectionalFactory.hpp
        PointFactory.hpp
)

add_library(LightFactory STATIC ${LIGHT_FACTORY_SRC} ${LIGHT_FACTORY_INC})

target_link_libraries(LightFactory PRIVATE
        Math
)
