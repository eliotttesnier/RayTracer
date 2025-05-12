set(MATERIAL_FACTORY_SRC
    MaterialFactory.cpp
)

set(MATERIAL_FACTORY_INC
    MaterialFactory.hpp
)

add_library(MaterialFactory STATIC ${MATERIAL_FACTORY_SRC} ${MATERIAL_FACTORY_INC})
