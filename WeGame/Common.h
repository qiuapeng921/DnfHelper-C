#pragma once
#include <winsvc.h>
#include "tlhelp32.h"

#include <vector>
using namespace std;

// RegisterHotKey(NULL, 1, 0, VK_HOME);
// RegisterHotKey(NULL, 1, MOD_ALT, VK_LEFT);
// RegisterHotKey(NULL, 0xC005, MOD_CONTROL, VK_LEFT);

// MessageBoxA(NULL, "激活按钮事件", "激活", MB_OK);

// CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)函数名, NULL, 0, &线程id);

// HWND hWnd = FindWindow(TEXT("地下城与勇士"), TEXT("地下城与勇士"));
// SetTimer(hWnd, 1, 频率, (TIMERPROC)函数名);
// KillTimer(hWnd, 1);

#define ByteArr vector<byte>
#define debug OutputDebugString

DWORD _GetProcessId(LPCWSTR 进程);

CString _IntToCString(int value);

char* _AnsiToUnicode(char* str);

CString _UnicodeToAnsi(vector<byte> vby);

CString _GetDesktopPath();

VOID _WriteConfig(CString 节, CString 项, CString 值);

DWORD _ReadConfig(CString 节, CString 项);

VOID _InitConfig();

HANDLE _CreateThread(PVOID 线程子程序);

BOOL _DeleteThread(HANDLE 线程句柄);

BYTE _ConvertHexChar(BYTE ch);

INT _Rand(int min, int max);

CString _GetCurrentTime();

VOID _DebugStringA(const char* lpcszOutputString, ...);

VOID _DebugStringW(const wchar_t* lpcwszOutputString, ...);

ByteArr _IntToBytes(DWORD64 num, int lenght);

ByteArr _AppendToBytes(ByteArr oldBytes, ByteArr newBytes);

ByteArr 取空白ByteArr(int num);

ByteArr AnsiToUnicode(string str);