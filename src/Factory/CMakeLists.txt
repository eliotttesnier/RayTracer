add_subdirectory(PrimitivesFactory)

set(FACTORY_SRC
    Factory.cpp
)

set(FACTORY_INC
    Factory.hpp
)

add_library(Factory STATIC ${FACTORY_SRC} ${FACTORY_INC})

target_link_libraries(Factory
    PUBLIC
        PrimitivesFactory
)
