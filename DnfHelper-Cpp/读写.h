#pragma once
#include "公用.h"
#include <vector>

VOID SetProcessId(DWORD id);

LPVOID 申请内存64(DWORD 申请长度);

BOOL 读字节集(DWORD64 地址, PVOID 返回值, INT32 写入长度);
BOOL 写字节集(DWORD64 地址, PVOID 写入值, INT32 写入长度);

DWORD 读整数型(DWORD64 地址);
BOOL 写整数型(DWORD64 地址, DWORD 数据);

DWORD64 读长整数型(DWORD64 地址);
BOOL 写长整数型(DWORD64 地址, DWORD64 数据);

vector<BYTE> 读字节数组(DWORD64 地址, INT32 长度);

BOOL 写字节数组(DWORD64 地址, vector<byte> 值);