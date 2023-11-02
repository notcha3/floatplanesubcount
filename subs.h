#pragma once
#include "main.h"

extern HWND hWindowHandle;
extern HDC hWindowContext;


VOID WINAPI fnSubcountWindow(VOID);
LRESULT CALLBACK fnWndProcCb(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam
);

VOID WINAPI fnSubCount(VOID);