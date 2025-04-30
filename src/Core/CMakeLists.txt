set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Core)

set(SRC
    ${SRCROOT}/Renderer.cpp
    ${SRCROOT}/Renderer.hpp
)

add_library(Core STATIC
    ${SRC}
)
