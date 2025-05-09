add_subdirectory(PrimitivesFactory)
add_subdirectory(CameraFactory)
add_subdirectory(LigthsFactory)
add_subdirectory(MaterialFactory)

set(FACTORY_SRC
    Factory.cpp
)

set(FACTORY_INC
    Factory.hpp
)

add_library(Factory STATIC ${FACTORY_SRC} ${FACTORY_INC})

target_link_libraries(Factory PRIVATE
    PrimitivesFactory
    CameraFactory
    LightFactory
    MaterialFactory
)
