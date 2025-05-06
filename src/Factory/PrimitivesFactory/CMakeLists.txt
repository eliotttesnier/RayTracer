set(PRIMITIVE_FACTORY_SRC
    PrimitiveFactory.cpp
    SphereFactory.cpp
    PlaneFactory.cpp
    CylinderFactory.cpp
    ConeFactory.cpp
    TorusFactory.cpp
    TanglecubeFactory.cpp
    TrianglesFactory.cpp
)

set(PRIMITIVE_FACTORY_INC
    PrimitiveFactory.hpp
    IPrimitiveFactory.hpp
    SphereFactory.hpp
    PlaneFactory.hpp
    CylinderFactory.hpp
    ConeFactory.hpp
    TorusFactory.hpp
    TanglecubeFactory.hpp
    TrianglesFactory.hpp
)

add_library(PrimitivesFactory STATIC ${PRIMITIVE_FACTORY_SRC} ${PRIMITIVE_FACTORY_INC})

target_link_libraries(PrimitivesFactory PRIVATE
        math
)
