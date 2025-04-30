set(PRIMITIVE_FACTORY_SRC
    PrimitiveFactory.cpp
    SphereFactory.cpp
    PlaneFactory.cpp
)

set(PRIMITIVE_FACTORY_INC
    PrimitiveFactory.hpp
    IPrimitiveFactory.hpp
    SphereFactory.hpp
    PlaneFactory.hpp
)

add_library(PrimitivesFactory SHARED ${PRIMITIVE_FACTORY_SRC} ${PRIMITIVE_FACTORY_INC})
