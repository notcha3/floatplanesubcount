#include "subs.h"

HWND hWindowHandle;
HDC hWindowContext;

VOID WINAPI fnSubcountWindow(VOID) {
	HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0));

	MSG uMsg;

	WNDCLASSEX strWindowClass = { 0 };
	strWindowClass.cbSize = sizeof(strWindowClass);
	strWindowClass.style = 0;
	strWindowClass.cbClsExtra = 0;
	strWindowClass.cbWndExtra = 0;
	strWindowClass.lpszMenuName = NULL;
	strWindowClass.lpszClassName = TEXT("ltt floatplane subcount");
	strWindowClass.hbrBackground = hBrush;
	strWindowClass.hIconSm = NULL;
	strWindowClass.hInstance = NULL;
	strWindowClass.hIconSm = NULL;
	strWindowClass.lpfnWndProc = fnWndProcCb;
	strWindowClass.hCursor = LoadCursor(
		strWindowClass.hInstance,
		IDC_ARROW
	);


	RegisterClassEx(&strWindowClass);
	
	hWindowHandle = CreateWindowEx(
		WS_EX_LEFT,
		TEXT("ltt floatplane subcount"),
		TEXT("ltt floatplane subcount"),
		WS_VISIBLE | WS_OVERLAPPEDWINDOW - WS_THICKFRAME - WS_MINIMIZEBOX - WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 160,
		NULL,
		NULL,
		strWindowClass.hInstance,
		NULL
	);

	hWindowContext = GetDC(hWindowHandle);
	SetTextColor(hWindowContext, RGB(17, 25, 255));

	while (GetMessage((LPMSG)&uMsg, hWindowHandle, 0, 0))
	{
		TranslateMessage((LPMSG)&uMsg);
		DispatchMessage((LPMSG)&uMsg);
	}
}

LRESULT CALLBACK fnWndProcCb(
	_Inout_ HWND hWnd,
	_In_ UINT uMsg,
	_Inout_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	switch (uMsg)
	{
	case WM_DESTROY:
		ExitProcess(0);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

VOID WINAPI fnSubCount(VOID) {
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	LPSTR lpOutBuffer;
	WORD wOutBufferlen;
	BOOL  bResults = FALSE;
	HINTERNET  hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;

	Sleep(200);

	while (TRUE) {
		
		
		TextOutW(hWindowContext, 15, 15, TEXT("LTT FLOATPLANE SUBCOUNT\0"), strlen("LTT FLOATPLANE SUBCOUNT"));

		hSession = WinHttpOpen(TEXT("Chrome/{Chrome Rev} Mobile Safari/{WebKit Rev}"),
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME,
			WINHTTP_NO_PROXY_BYPASS, 0);


		if (hSession) {
			hConnect = WinHttpConnect(hSession, TEXT("floatplane.com"),
				INTERNET_DEFAULT_HTTPS_PORT, 0);
		}

		if (hConnect) {
			hRequest = WinHttpOpenRequest(hConnect, TEXT("GET"), TEXT("/api/v2/plan/info?creatorId=59f94c0bdd241b70349eb72b"),
				TEXT("3.0"), WINHTTP_NO_REFERER,
				WINHTTP_DEFAULT_ACCEPT_TYPES,
				WINHTTP_FLAG_SECURE);
		}

		if (hRequest) {

			bResults = WinHttpSendRequest(hRequest,
				WINHTTP_NO_ADDITIONAL_HEADERS, 0,
				WINHTTP_NO_REQUEST_DATA, 0,
				0, (DWORD_PTR)NULL);

		}

		if (bResults) {

			bResults = WinHttpReceiveResponse(hRequest, NULL);
		}

		if (bResults)
		{

			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
				TextOutA(hWindowContext, 50, 50, "ERROR", strlen("ERROR"));
			}

			pszOutBuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize + 1);

			if (!pszOutBuffer) {
				TextOutA(hWindowContext, 50, 50, "Out of memory", strlen("Out of memory"));

				dwSize = 0;
			}

			else {

				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
					dwSize, &dwDownloaded)) {

					TextOutA(hWindowContext, 50, 50, "ERROR", strlen("ERROR"));
				}

				else {

					pszOutBuffer[29] = '\0';

					lpOutBuffer = pszOutBuffer + 24;

					TextOutA(hWindowContext, 80, 50, lpOutBuffer, strlen(lpOutBuffer));
					Sleep(9000);
				}
				HeapFree(GetProcessHeap(), 0, pszOutBuffer);
			}
		}



		if (!bResults) 
			TextOutW(hWindowContext, 50, 50, TEXT("ERROR"), strlen("ERROR"));

		if (hRequest)
			WinHttpCloseHandle(hRequest);

		if (hConnect)
			WinHttpCloseHandle(hConnect);

		if (hSession)
			WinHttpCloseHandle(hSession);

		UpdateWindow(hWindowHandle);
	
	
	}
	
}
