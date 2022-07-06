#pragma once

#include <vector>
using namespace std;

VOID 设置进程ID(DWORD 进程ID, HWND 窗口句柄);

LPVOID 申请_内存(DWORD 申请长度);

BOOL 读字节集(DWORD64 地址, PVOID 返回值, INT32 写入长度);

BOOL 写字节集(DWORD64 地址, PVOID 写入值, INT32 写入长度);

DWORD 读整数型(DWORD64 地址);

DWORD64 读长整数型(DWORD64 地址);

BOOL 写整数型(DWORD64 地址, DWORD 数据);

BOOL 写长整数型(DWORD64 地址, DWORD64 数据);

BYTE* 读字节集型(DWORD64 地址, INT32 长度);

BOOL 写字节集型(DWORD64 地址, PBYTE 写入值, INT32 长度);

vector<BYTE> API_读字节集(DWORD64 地址, INT32 长度);

BOOL API_写字节集(DWORD64 地址, vector<byte> 值);

VOID 汇编执行(BYTE *bytes);