# Source configuration.

set (PARSER_TEST_HEADERS
    parser/lexer.h
    parser/parser.h
    parser/token.h
    parser/pdef.h
    parser/sem-anal.h)

set (PARSER_TEST_SRC
    parser/main.cpp
    parser/lexer.cpp
    parser/parser.cpp
    parser/token.cpp
    parser/sem-anal.cpp)

if (MSVC)
    # TODO
    # set(PARSER_TEST_HEADERS ${PARSER_TEST_HEADERS} window/window.h)
    # set(PARSER_TEST_SRC ${PARSER_TEST_SRC} window/window.cpp)
    # WIN32

    # TODO
    # MSVC does not like the appending style of handling files.
    add_subdirectory (gui)

    # list (APPEND PARSER_TEST_SRC window/window.cpp)
    # list (APPEND PARSER_TEST_HEADERS window/window.h)

    set (PARSER_SOURCES
        ${PARSER_TEST_HEADERS}
        ${PARSER_TEST_SRC})

    add_executable (parser WIN32 ${PARSER_SOURCES})


    target_link_libraries(parser parser-window)
    # Add the current folder to -I.
    target_include_directories (parser PRIVATE .)
    # Specify the warning level, treat all warnings as errors.
    target_compile_options(parser PRIVATE "/WX")
endif()

