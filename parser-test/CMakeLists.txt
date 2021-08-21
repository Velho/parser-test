# Source configuration.

set(PARSER_TEST_HEADERS
    parser/lexer.h
    parser/parser.h
    parser/token.h
    parser/pdef.h
    parser/sem-anal.h)

set(PARSER_TEST_SRC 
    parser/main.cpp
    parser/lexer.cpp
    parser/parser.cpp
    parser/token.cpp
    parser/sem-anal.cpp)

if(MSVC)
    # TODO
    # set(PARSER_TEST_HEADERS ${PARSER_TEST_HEADERS} window/window.h)
    # set(PARSER_TEST_SRC ${PARSER_TEST_SRC} window/window.cpp)
    # WIN32

    set(PARSER_SRCS
        ${PARSER_TEST_HEADERS}
        ${PARSER_TEST_SRC})

    add_executable(parser-test  ${PARSER_SRCS})

    # Add the current folder to -I.
    target_include_directories (parser-test PRIVATE .)
    # Specify the warning level, treat all warnings as errors.
    target_compile_options(parser-test PRIVATE "/WX")
endif()

