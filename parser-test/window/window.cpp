#include "window.h"

#include <stdio.h>
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
    WinHandler *handler = (WinHandler*)malloc(sizeof(WinHandler));

    if (handler == NULL)
    {
        return NULL;
    }

    handler->nCmdShow = nCmdShow;
    handler->hInst = inst;

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = handler->hInst;
    wc.lpszClassName = P_WINDOW_CLASS_NAME;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        P_WINDOW_CLASS_NAME,
        P_WINDOW_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL,
        inst, //! Instance handle
        NULL
    );

    if (hwnd == NULL)
    {
        return handler;
    }

    handler->hwnd = hwnd;

    return handler;
}

void WinRelease(WinHandler* handler)
{
    free(handler);
}

int WinRun(WinHandler* handler)
{
   
    ShowWindow(handler->hwnd, SW_SHOW);

    // Run the message loop.
    MSG msg = { 0 };
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


