# Source configuration.

set(PARSER_TEST_HEADERS
    lexer.h
    parser.h
    token.h
    pdef.h
    sem-anal.h)

set(PARSER_TEST_SRC 
    main.cpp
    lexer.cpp
    parser.cpp
    token.cpp
    sem-anal.cpp)

if(MSVC)
    set(PARSER_TEST_HEADERS ${PARSER_TEST_HEADERS} window/window.h)
    set(PARSER_TEST_SRC ${PARSER_TEST_SRC} window/window.cpp)

    set(PARSER_SRCS
        ${PARSER_TEST_HEADERS}
        ${PARSER_TEST_SRC})

    add_executable(parser-test WIN32 ${PARSER_SRCS})
    # Specify the warning level, treat all warnings as errors.
    target_compile_options(parser-test PRIVATE "/W4")
endif()

