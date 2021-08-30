#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

//
// Simple console renderer for the application,
// executes the given command.
//

typedef struct _WinHandler WinHandler;

/**
 * @brief Creates the Window context.
 * 
 * @param inst
 * @param nCmdShow
 */
WinHandler* WinCreate(HINSTANCE inst, int nCmdShow);

/**
 * @brief Release the handler allocation.
 */
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


