#include <Windows.h>



LONG_PTR previous_func = NULL;

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {

	if (uMsg == WM_CHAR)
	{
		if (wParam % 2 ==0)
		{
			wParam -= 1;
		}
	}
		//MessageBoxW(NULL, L"YOU RETURN", L"myDLL", MB_OKCANCEL);
	

	return CallWindowProcA(previous_func , hwnd, uMsg, wParam, lParam);
}

void fuckwindow() {
	HWND hparent = FindWindowExA(NULL,NULL, "Notepad", NULL );
	HWND hedit = FindWindowExA(hparent,NULL,"Edit",NULL);
	previous_func = GetWindowLongPtrA(hedit, GWLP_WNDPROC);
	SetWindowLongPtrA(hedit, GWLP_WNDPROC,(LONG_PTR)WindowProc);
}


BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
) {
	if (fdwReason==DLL_PROCESS_ATTACH)
	{
		//MessageBoxW(NULL, L"HELLO", L"myDLL", MB_OK);

		fuckwindow();
	}
	

	return TRUE;
	
}
