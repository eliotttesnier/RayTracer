add_library(Cylinder SHARED
    Cylinder.cpp
    Cylinder.hpp
)

target_include_directories(Cylinder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Cylinder PRIVATE math)
