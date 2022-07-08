#pragma once
#include "Common.h"

#include <vector>
using namespace std;

VOID _SetProcessId(DWORD processId, HWND processHandle);

LPVOID _ApplyMemory(DWORD length);

BOOL readBytes(DWORD64 address, PVOID val, INT32 length);

BOOL writeBytes(DWORD64 address, PVOID val, INT32 length);

DWORD _ReadInt(DWORD64 address);

DWORD64 _ReadLong(DWORD64 address);

BOOL _WriteInt(DWORD64 address, DWORD val);

BOOL _WriteLong(DWORD64 address, DWORD64 val);

//BYTE* _ReadBytes(DWORD64 address, INT32 length);
//
//BOOL _WriteBytes(DWORD64 address, PBYTE val, INT32 length);

ByteArr _ReadByteArr(DWORD64 address, INT32 length);

BOOL _WriteByteArr(DWORD64 address, ByteArr val);