#include "pch.h"
#include <winsvc.h>
#include "tlhelp32.h"
#include "Api读写.h"

LPVOID ApiReadWrite::申请内存64(DWORD 进程ID, DWORD 申请长度) {
	HANDLE 进程句柄 = ::OpenProcess(PROCESS_ALL_ACCESS, 0, 进程ID);
	LPVOID 内存地址 = VirtualAllocEx(进程句柄, 0, 申请长度, 4096, 64);
	CloseHandle(进程句柄);
	return 内存地址;
}

BOOL ApiReadWrite::进程_读字节集(DWORD 进程ID, DWORD64 地址, PVOID 返回值, INT32 写入长度) {
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, NULL, 进程ID);
	if (hProcess == NULL) {
		return FALSE;
	}

	BOOL result = ::ReadProcessMemory(hProcess, (LPVOID)地址, 返回值, 写入长度, NULL);
	if (result == false)
	{
		return 0;
	}
	::CloseHandle(hProcess);
	return result;
}
BOOL ApiReadWrite::进程_写字节集(DWORD 进程ID, DWORD64 地址, PVOID 写入值, INT32 写入长度) {

	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, NULL, 进程ID);
	if (hProcess == NULL) {
		return FALSE;
	}

	BOOL result = ::WriteProcessMemory(hProcess, (LPVOID)地址, 写入值, 写入长度, NULL);
	if (result == false)
	{
		return 0;
	}
	::CloseHandle(hProcess);
	return result;
}

DWORD ApiReadWrite::读整数型(DWORD 进程ID, DWORD64 地址)
{
	DWORD result;
	进程_读字节集(进程ID, 地址, &result, sizeof(result));
	return result;
}
BOOL ApiReadWrite::写整数型(DWORD 进程ID, DWORD64 地址, DWORD 数据)
{
	return 进程_写字节集(进程ID, 地址, &数据, sizeof(数据));
}

DWORD64 ApiReadWrite::读长整数型(DWORD 进程ID, DWORD64 地址)
{
	DWORD64 result;
	进程_读字节集(进程ID, 地址, &result, sizeof(result));
	return result;
}
BOOL ApiReadWrite::写长整数型(DWORD 进程ID, DWORD64 地址, DWORD64 数据)
{
	return 进程_写字节集(进程ID, 地址, &数据, sizeof(数据));
}

vector<BYTE> ApiReadWrite::读字节数组(DWORD 进程ID, DWORD64 地址, INT32 长度)
{
	vector<BYTE> result;

	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, NULL, 进程ID);
	if (hProcess == NULL) {
		return result;
	}

	BYTE* tempResult = new BYTE[(__int64)长度 + 1];

	memset(tempResult, 0, 长度);
	ReadProcessMemory(hProcess, (LPVOID)地址, tempResult, 长度, NULL);
	CloseHandle(hProcess);

	result.resize(长度);
	for (int i = 0; i < 长度; i++)
	{
		result[i] = tempResult[i];
	}
	return result;
}
// API_写字节集(任务地址, { 0x90, 0x90, 0x90, 0x90, 0x90 });
BOOL ApiReadWrite::写字节数组(DWORD 进程ID, DWORD64 地址, vector<byte> 值)
{
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, NULL, 进程ID);
	if (hProcess == NULL) {
		return FALSE;
	}

	int length;
	length = (int)值.size();
	byte* val = new byte[length]();
	for (int i = 0; i < length; i++)
	{
		val[i] = 值[i];
	}
	WriteProcessMemory(hProcess, (LPVOID)地址, (LPCVOID)val, length, 0);
	CloseHandle(hProcess);
	return TRUE;
}