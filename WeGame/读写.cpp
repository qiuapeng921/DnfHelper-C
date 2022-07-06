#include "pch.h"
#include "读写.h"

#include "Api读写.h"

Api读写 apiRw;

DWORD static 全_进程ID;

HWND static 全_进程句柄;

VOID 设置进程ID(DWORD 进程ID, HWND 窗口句柄) {
	全_进程ID = 进程ID;
	全_进程句柄 = 窗口句柄;
}

LPVOID 申请_内存(DWORD 申请长度) {
	return apiRw.申请内存64(全_进程ID, 申请长度);
}

BOOL 读字节集(DWORD64 地址, PVOID 返回值, INT32 写入长度) {
	return apiRw.进程_读字节集(全_进程ID, 地址, 返回值, 写入长度);
}

BOOL 写字节集(DWORD64 地址, PVOID 写入值, INT32 写入长度) {
	return apiRw.进程_写字节集(全_进程ID, 地址, 写入值, 写入长度);
}

DWORD 读整数型(DWORD64 地址)
{
	DWORD result;
	读字节集(地址, &result, sizeof(result));
	return result;
}

DWORD64 读长整数型(DWORD64 地址)
{
	DWORD64 result;
	读字节集(地址, &result, sizeof(result));
	return result;
}

BOOL 写整数型(DWORD64 地址, DWORD 数据)
{
	return 写字节集(地址, &数据, sizeof(数据));
}

BOOL 写长整数型(DWORD64 地址, DWORD64 数据)
{
	return 写字节集(地址, &数据, sizeof(数据));
}

// BYTE* 原字节集 = 读字节集型(制裁基址, 2);
BYTE* 读字节集型(DWORD64 地址, INT32 长度) {
	BYTE* result = new BYTE[长度];
	读字节集(地址, result, 长度);
	return result;
}

// 写字节集型(制裁基址, new BYTE[]{ 0xC3, 0x90 }, 2);
BOOL 写字节集型(DWORD64 地址, PBYTE 写入值, INT32 长度) {
	return 写字节集(地址, 写入值, 长度);
}

vector<BYTE> API_读字节集(DWORD64 地址, INT32 长度) {
	return apiRw.API_读字节集(全_进程ID, 地址, 长度);
}

BOOL API_写字节集(DWORD64 地址, vector<BYTE> 值) {
	return apiRw.API_写字节集(全_进程ID, 地址, 值);
}


VOID 汇编执行(BYTE* 汇编代码) {

	DWORD64 static 空白地址, 汇编中转, Hook地址, Hook跳回, 判断地址 = 0;
	BYTE* Hook数据[] = { 0 };
	if (空白地址 == 0)
	{

		空白地址 = (DWORD64)申请_内存(1024);
		汇编中转 = (DWORD64)申请_内存(1024) + 100;
		判断地址 = 汇编中转 - 100;
	}
}