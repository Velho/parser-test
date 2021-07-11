

set(PARSER_TEST_HEADERS
    lexer.h
    node.h
    parser.h
    token.h
    pdef.h
    sem.h)

set(PARSER_TEST_SRC 
    ${PARSER_TEST_HEADERS}
    main.c
    lexer.c
    node.c
    parser.c
    token.c
    sem.c)


add_executable(parser-test ${PARSER_TEST_SRC})
