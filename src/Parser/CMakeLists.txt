set(PARSER_SRC
    Parser.cpp
)

set(PARSER_HPP
    Parser.hpp
)

add_subdirectory(ParserConfig)

add_library(parser STATIC ${PARSER_SRC} ${PARSER_HPP})

find_library(LIBCONFIGPP_LIBRARY NAMES config++)
if (NOT LIBCONFIGPP_LIBRARY)
    message(FATAL_ERROR "libconfig++ non trouvée")
endif()

target_link_libraries(parser PRIVATE ${LIBCONFIGPP_LIBRARY} classConfig)
target_include_directories(parser PRIVATE ./)
