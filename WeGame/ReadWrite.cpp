#include "pch.h"
#include "ReadWrite.h"
#include "ApiReadWrite.h"
#include "Common.h"

ApiReadWrite apiRw;

DWORD static globleProcessId;

HWND static globleProcessHandle;

VOID _SetProcessId(DWORD processId, HWND processHandle) {
	globleProcessId = processId;
	globleProcessHandle = processHandle;
}

LPVOID _ApplyMemory(DWORD length) {
	return apiRw.申请内存64(globleProcessId, length);
}

BOOL readBytes(DWORD64 address, PVOID val, INT32 length) {
	return apiRw.进程_读字节集(globleProcessId, address, val, length);
}

BOOL writeBytes(DWORD64 address, PVOID val, INT32 length) {
	return apiRw.进程_写字节集(globleProcessId, address, val, length);
}

DWORD _ReadInt(DWORD64 address)
{
	DWORD result;
	readBytes(address, &result, sizeof(result));
	return result;
}

DWORD64 _ReadLong(DWORD64 address)
{
	DWORD64 result;
	readBytes(address, &result, sizeof(result));
	return result;
}

BOOL _WriteInt(DWORD64 address, DWORD val)
{
	return writeBytes(address, &val, sizeof(val));
}

BOOL _WriteLong(DWORD64 address, DWORD64 val)
{
	return writeBytes(address, &val, sizeof(val));
}

// BYTE* 原字节集 = 读字节集型(制裁基址, 2);
//BYTE* _ReadBytes(DWORD64 address, INT32 length) {
//	BYTE* result = new BYTE[length];
//	readBytes(address, result, length);
//	return result;
//}

// 写字节集型(制裁基址, new BYTE[]{ 0x48, 0xBE }, 2);
//BOOL _WriteBytes(DWORD64 address, PBYTE val, INT32 length) {
//	return writeBytes(address, val, length);
//}

vector<BYTE> _ReadByteArr(DWORD64 address, INT32 length) {
	return apiRw.读字节数组(globleProcessId, address, length);
}

BOOL _WriteByteArr(DWORD64 address, ByteArr val){
	return apiRw.写字节数组(globleProcessId, address, val);
}