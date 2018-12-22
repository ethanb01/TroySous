#include <Windows.h>




LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	

	//if (GetAsyncKeyState(VK_RETURN)!=0)
	//{
	//	MessageBoxW(NULL, L"YOU RETURN", L"myDLL", MB_OKCANCEL);
	//}

	wParam = 'a';
	/*switch (uMsg)
	{
		
	default:
		
		
	}*/
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void fuckwindow() {
	HWND hparent = FindWindowExA(NULL,NULL, "Notepad", NULL );
	HWND hedit = FindWindowExA(hparent,NULL,"Edit",NULL);
	SetWindowLongPtrA(hedit, GWLP_WNDPROC,(LONG_PTR)WindowProc);
}


BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
) {
	if (fdwReason==DLL_PROCESS_ATTACH)
	{
		MessageBoxW(NULL, L"HELLO", L"myDLL", MB_OK);

		fuckwindow();
	}
	

	return TRUE;
	
}

