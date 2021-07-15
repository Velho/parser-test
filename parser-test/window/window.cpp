#include "window.h"

#include <stdlib.h>


/** Win32 **/
typedef struct _WinHandler {
    int nCmdShow;
    HINSTANCE hInst;
    WNDCLASS wc;
    HWND hwnd;
} WinHandler;


WinHandler* WinCreate(HINSTANCE inst, int nCmdShow)
{
    WinHandler *state = (WinHandler*)malloc(sizeof(WinHandler));
    
    state->nCmdShow = nCmdShow;
    // Initialize the window class to zero.
    memset(&state->wc, 0, sizeof(WNDCLASS));

    WNDCLASS wc;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = inst;
    wc.lpszClassName = P_WINDOW_CLASS_NAME;

    memcpy(&state->wc, &wc, sizeof(WNDCLASS));
    return state;
}

void WinRelease(WinHandler* handler)
{
    free(handler);
}

int WinRun(WinHandler* handler)
{
    // Register before create?
    RegisterClass(&handler->wc);
    HWND hwnd = CreateWindowEx(
        0,
        P_WINDOW_CLASS_NAME,
        P_WINDOW_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL,
        handler->hInst, //! Instance handle
        NULL
    );

    memcpy(&handler->hwnd, &hwnd, sizeof(HWND));
    ShowWindow(handler->hwnd, SW_SHOW);

    // Run the message loop.
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);



            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


