set(PLANE_SRC
    Plane.cpp
)

set(PLANE_INC
    Plane.hpp
)

add_library(Plane SHARED ${PLANE_SRC} ${PLANE_INC})
target_include_directories(Plane PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Plane PRIVATE math)