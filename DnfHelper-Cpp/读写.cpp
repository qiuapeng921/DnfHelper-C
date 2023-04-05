#include "读写.h"

using namespace std;

DWORD static processId;

VOID SetProcessId(DWORD id) {
	processId = id;
}

LPVOID 申请内存64(DWORD 申请长度) {
	HANDLE 进程句柄 = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);
	LPVOID 内存地址 = VirtualAllocEx(进程句柄, 0, 申请长度, 4096, 64);
	CloseHandle(进程句柄);
	return 内存地址;
}

BOOL 读字节集(DWORD64 地址, PVOID 返回值, INT32 长度) {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
	if (hProcess == NULL) {
		return FALSE;
	}

	BOOL result = ReadProcessMemory(hProcess, (LPVOID)地址, 返回值, 长度, NULL);
	if (result == false)
	{
		CloseHandle(hProcess);
		return 0;
	}
	CloseHandle(hProcess);
	return TRUE;
}
BOOL 写字节集(DWORD64 地址, PVOID 写入值, INT32 写入长度) {

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
	if (hProcess == NULL) {
		return FALSE;
	}

	BOOL result = WriteProcessMemory(hProcess, (LPVOID)地址, 写入值, 写入长度, NULL);
	if (result == false)
	{
		CloseHandle(hProcess);
		return FALSE;
	}
	CloseHandle(hProcess);
	return TRUE;
}

DWORD 读整数型(DWORD64 地址)
{
	DWORD result;
	读字节集(地址, &result, sizeof(result));
	return result;
}
BOOL 写整数型(DWORD64 地址, DWORD 数据)
{
	return 写字节集(地址, &数据, sizeof(数据));
}

DWORD64 读长整数型(DWORD64 地址)
{
	DWORD64 result;
	读字节集(地址, &result, sizeof(result));
	return result;
}
BOOL 写长整数型(DWORD64 地址, DWORD64 数据)
{
	return 写字节集(地址, &数据, sizeof(数据));
}


vector<BYTE> 读字节数组(DWORD64 地址, INT32 长度) {
	vector<BYTE> result;

	BYTE* tempResult = new BYTE[(INT64)长度 + 1];
	memset(tempResult, 0, 长度);

	if (!读字节集(地址, tempResult, 长度)) return result;

	result.resize(长度);
	for (int i = 0; i < 长度; i++)
	{
		result[i] = tempResult[i];
	}
	return result;
}

BOOL 写字节数组(DWORD64 地址, vector<byte> 值) {
	int length;
	length = (int)值.size();
	byte* val = new byte[length]();
	for (int i = 0; i < length; i++)
	{
		val[i] = 值[i];
	}

	return 写字节集(地址, val, sizeof(值));
}