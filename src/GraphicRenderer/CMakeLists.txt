set(INCROOT ${PROJECT_SOURCE_DIR}/src/GraphicRenderer)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/GraphicRenderer)

set(SRC
    ${SRCROOT}/GraphicRenderer.cpp
)

set(HEADER_DIRECTORIES ${INCROOT})
include_directories(${HEADER_DIRECTORIES})

if(NOT SFML_FOUND)
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
endif()

add_library(graphic_renderer STATIC ${SRC})
target_link_libraries(graphic_renderer
    sfml-graphics
    sfml-window
    sfml-system
)
