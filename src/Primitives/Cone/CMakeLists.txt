add_library(Cone SHARED
    Cone.cpp
    Cone.hpp
)

target_include_directories(Cone PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Cone PRIVATE math)
