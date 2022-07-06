#pragma once

#include <vector>
using namespace std;

class ApiReadWrite
{
public:
	
	LPVOID 申请内存64(DWORD 进程ID, DWORD 申请长度);

	BOOL 进程_写字节集(DWORD 进程ID, DWORD64 地址, PVOID 返回值, INT32 写入长度);
	BOOL 进程_读字节集(DWORD 进程ID, DWORD64 地址, PVOID 写入值, INT32 写入长度);

	DWORD 读整数型(DWORD 进程ID, DWORD64 地址);
	BOOL 写整数型(DWORD 进程ID, DWORD64 地址, DWORD 数据);

	DWORD64 读长整数型(DWORD 进程ID, DWORD64 地址);
	BOOL 写长整数型(DWORD 进程ID, DWORD64 地址, DWORD64 数据);

	vector<byte> API_读字节集(DWORD 进程ID, DWORD64 地址, INT32 长度);
	BOOL API_写字节集(DWORD 进程ID, DWORD64 地址, vector<byte> 值);
};

extern ApiReadWrite apiRw;