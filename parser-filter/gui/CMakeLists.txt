# TODO Sorry Unix guys, the supoprt is coming afte first windows release.

set (WINDOW_HEADERS
    win32/window.h)

set (WINDOW_SRC
    win32/window.cpp)

set (WINDOW_SOURCES ${WINDOW_SRC})

# Shared or static?

add_library (parser-window ${WINDOW_SOURCES})
