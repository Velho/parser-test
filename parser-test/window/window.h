#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

#define P_WINDOW_NAME               L"Parser"
#define P_WINDOW_CLASS_NAME         L"Sample Window Class"


//
// Simple console renderer for the application,
// executes the given command.
//


typedef struct _WinHandler WinHandler;


WinHandler* WinCreate(HINSTANCE inst, int nCmdShow);
void WinRelease(WinHandler* handler);

/**
 * @brief Event handler for the dispatched messages.
 */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
 * @brief 
 * 
 * @param state Pointer to the window context.
 * @return int 
 */
int WinRun(WinHandler* state);


