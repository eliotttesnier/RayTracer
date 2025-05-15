set(MATH_SRC
    Point3D.cpp
    Vector3D.cpp
    Ray.cpp
    Rectangle3D.cpp
)

set(MATH_INC
    Point3D.hpp
    Vector3D.hpp
    Ray.hpp
    HitData.hpp
    Rectangle3D.hpp
)

add_library(Math STATIC ${MATH_SRC} ${MATH_INC})
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
