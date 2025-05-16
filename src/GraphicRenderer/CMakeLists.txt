set(INCROOT ${PROJECT_SOURCE_DIR}/src/GraphicRenderer)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/GraphicRenderer)

set(SRC
    ${SRCROOT}/GraphicRenderer.cpp
    ${SRCROOT}/Inotify.cpp
)

set(HEADER_DIRECTORIES ${INCROOT})
include_directories(${HEADER_DIRECTORIES})

if(NOT SFML_FOUND)
    find_package(SFML COMPONENTS graphics window system REQUIRED)
endif()

add_library(GraphicRenderer STATIC ${SRC})
target_link_libraries(GraphicRenderer
    sfml-graphics
    sfml-window
    sfml-system
    Core
    Factory
)
