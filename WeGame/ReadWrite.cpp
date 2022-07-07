#include "pch.h"
#include "ReadWrite.h"
#include "Address.h"
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
BYTE* _ReadBytes(DWORD64 address, INT32 length) {
	BYTE* result = new BYTE[length];
	readBytes(address, result, length);
	return result;
}

// 写字节集型(制裁基址, new BYTE[]{ 0x48, 0xBE }, 2);
BOOL _WriteBytes(DWORD64 address, PBYTE val, INT32 length) {
	return writeBytes(address, val, length);
}

vector<BYTE> _ReadByteArr(DWORD64 address, INT32 length) {
	return apiRw.读字节数组(globleProcessId, address, length);
}

BOOL _WriteByteArr(DWORD64 address, vector<BYTE> val){
	return apiRw.写字节数组(globleProcessId, address, val);
}


VOID 汇编执行(BYTE* 汇编代码) {
	__int64 汇编中转, 空白地址, Hook汇编, Hook跳回, 判断地址;
	vector<byte> Hook原数据,Hook数据;
	static bool 异步执行;

	汇编中转 = 全局空白 + 300;
	空白地址 = 全局空白 + 500;
	判断地址 = 空白地址 - 100;
	if(异步执行) {
		return;
	}

	异步执行 = true;
	Hook汇编 = 汇编CALL;
	Hook汇编 = Hook汇编 + 144;
	Hook跳回 = Hook汇编 + 19;
	Hook数据 = _ReadByteArr(Hook汇编, 19);
	Hook原数据 = Hook数据;

	vector<byte> tmp1 = { 72, 184 };
	Hook数据.insert(Hook数据.end(), tmp1.begin(), tmp1.end());

	unsigned char* tmp2;
	_Int64ToBytes(判断地址,tmp2);


	Hook数据.insert(Hook数据.end(), tmp2.begin(), tmp2.end());

	vector<byte> tmp3 = { 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 };
	Hook数据.insert(Hook数据.end(), tmp3.begin(), tmp3.end());

	vector<byte> tmp4 = { 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 };
	Hook数据.insert(Hook数据.end(), tmp4.begin(), tmp4.end());

	vector<byte> tmp5 = { 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 };
	Hook数据.insert(Hook数据.end(), tmp5.begin(), tmp5.end());

	vector<byte> tmp6 = { 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 };
	Hook数据.insert(Hook数据.end(), tmp6.begin(), tmp6.end());

	/*Hook数据.assign()


	Hook数据 = 字节集累加(Hook数据, 创建字节集(72, 184), 到字节集(判断地址));
	Hook数据 = 字节集累加(Hook数据, 创建字节集(131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0));
	Hook数据 = 字节集累加(Hook数据, 创建字节集(72, 187), 到字节集(空白地址));
	Hook数据 = 字节集累加(Hook数据, 创建字节集(255, 211));
	Hook数据 = 字节集累加(Hook数据, 创建字节集(72, 184), 到字节集(判断地址));
	Hook数据 = 字节集累加(Hook数据, 创建字节集(199, 0, 3, 0, 0, 0));

	Hook数据 = 字节集累加(Hook数据, 创建字节集(72, 129, 196, 0, 3, 0, 0));
	Hook数据 = 字节集累加(Hook数据, 创建字节集(255, 37, 0, 0, 0, 0), 到字节集(Hook跳回));

	if(_ReadLong(汇编中转) == 0) {
		_WriteByteArr(汇编中转, Hook数据);
	}
	_WriteByteArr(空白地址, 字节集累加(汇编代码, 创建字节集(195)));

	_WriteByteArr( Hook汇编, 字节集累加(创建字节集(255, 37, 0, 0, 0, 0), 到字节集(汇编中转), 创建字节集(144, 144, 144, 144, 144)));
	_WriteLong( 判断地址, 1);

	while (_ReadLong(判断地址) == 1)
	{
		Sleep(10);
	}

	_WriteByteArr(Hook汇编, Hook原数据);
	_WriteByteArr(空白地址, 取空白字节集(取字节集长度(汇编代码) + 16));*/
	异步执行 = false;
}