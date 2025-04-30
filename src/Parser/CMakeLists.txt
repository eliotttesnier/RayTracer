set(PARSER_SRC
    Parser.cpp
)

set(PARSER_HPP
    Parser.hpp
)

add_library(parser STATIC ${PARSER_SRC} ${PARSER_HPP})

target_link_libraries(parser PRIVATE
    config++
)
