set(PARSER_SRC
    Parser.cpp
    PrimitivesParser.cpp
    LightsParser.cpp
)

set(PARSER_HPP
    Parser.hpp
    PrimitivesParser.hpp
    LightsParser.hpp
)

add_subdirectory(ParserConfig)

add_library(Parser STATIC ${PARSER_SRC} ${PARSER_HPP})

find_library(LIBCONFIGPP_LIBRARY NAMES config++)
if (NOT LIBCONFIGPP_LIBRARY)
    message(FATAL_ERROR "libconfig++ non trouvée")
endif()

target_link_libraries(Parser PRIVATE ${LIBCONFIGPP_LIBRARY} classConfig)
target_include_directories(Parser PRIVATE ./)
