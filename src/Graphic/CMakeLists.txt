set(GRAPHIC_SRC
    Color.cpp
    Camera.cpp
)

set(GRAPHIC_INC
    Color.hpp
    Camera.hpp
)

add_library(Graphic SHARED ${GRAPHIC_SRC} ${GRAPHIC_INC})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Graphic PRIVATE Math)
