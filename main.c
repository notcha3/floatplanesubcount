#include "main.h"


INT WINAPI WinMain(
_In_ HINSTANCE hInstance,
_In_opt_ HINSTANCE hPrevInstance,
_In_ LPSTR pCmdLine,
_In_ INT nCmdShow
) {
	UNREFERENCED_PARAMETER(hPrevInstance);

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&fnSubcountWindow, NULL, 0, NULL);
	CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) &fnSubCount, NULL, 0, NULL);

	while (TRUE) {
		Sleep(3000);
	}

}



