#include "pch.h"
#include "ReadWrite.h"
#include "ApiReadWrite.h"
#include "Common.h"

ApiReadWrite apiRw;

DWORD static globleProcessId;

HWND static globleProcessHandle;

VOID _SetProcessId(DWORD processId, HWND processHandle)
{
	globleProcessId = processId;
	globleProcessHandle = processHandle;
}

LPVOID _ApplyMemory(DWORD length) {
	return apiRw.申请内存64(globleProcessId, length);
}

BOOL readBytes(DWORD64 address, PVOID val, INT32 length)
{
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

vector<BYTE> _ReadByteArr(DWORD64 address, INT32 length)
{
	return apiRw.读字节数组(globleProcessId, address, length);
}

BOOL _WriteByteArr(DWORD64 address, ByteArr val)
{
	return apiRw.写字节数组(globleProcessId, address, val);
}


VOID 汇编执行(ByteArr 汇编代码)
{
	//static __int64 空白地址, 汇编中转, Hook地址, Hook跳回, 判断地址;
	//static ByteArr Hook数据;
	//if (空白地址 == 0)
	//{
	//	空白地址 = (__int64)_ApplyMemory(1024);
	//	汇编中转 = (__int64)_ApplyMemory(1024) + 100;
	//	判断地址 = 汇编中转 - 100;
	//	Hook地址 = 内存汇编;
	//	Hook地址 = Hook地址 + 144;
	//	Hook跳回 = Hook地址 + 19;
	//	Hook数据 = { 15, 16, 28, 36, 15, 16, 84, 36, 16, 15, 16, 76, 36, 32, 15, 16, 68, 36, 48 };// ' 读字节集 (Hook地址, 19)
	//	Hook数据 = _AppendToBytes(Hook数据, _AppendToBytes({ 72, 184 }, _IntToBytes(判断地址, 8)));
	//	Hook数据 = _AppendToBytes(Hook数据, { 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 });
	//	Hook数据 = _AppendToBytes(Hook数据, _AppendToBytes({ 72, 187 }, _IntToBytes(汇编中转, 8)));
	//	Hook数据 = _AppendToBytes(Hook数据, { 255, 211 });
	//	Hook数据 = _AppendToBytes(Hook数据, _AppendToBytes({ 72, 184 }, _IntToBytes(判断地址, 8)));
	//	Hook数据 = _AppendToBytes(Hook数据, { 199, 0, 3, 0, 0, 0 });
	//	Hook数据 = _AppendToBytes(Hook数据, { 72, 129, 196, 0, 3, 0, 0 });
	//	Hook数据 = _AppendToBytes(Hook数据, _AppendToBytes({ 255, 37, 0, 0, 0, 0 }, _IntToBytes(Hook跳回, 8)));
	//	_WriteByteArr(空白地址, Hook数据);
	//	_WriteByteArr(Hook地址, _AppendToBytes({ 255, 37, 0, 0, 0, 0 }, _IntToBytes(空白地址, 8)));
	//}
	//_WriteByteArr(汇编中转, _AppendToBytes(汇编代码, { 195 }));
	//_WriteInt(判断地址, 1);
	//while (_ReadInt(判断地址) == 1)
	//{
	//	Sleep(20);
	//}

	__int64 汇编中转, 空白地址, Hook汇编, Hook跳回, 判断地址;

	static bool 异步执行;
	static __int64 kb;
	if (kb == 0)
	{
		kb = (__int64)_ApplyMemory(1024);
	}
	汇编中转 = kb + 300;
	空白地址 = kb + 500;
	判断地址 = 空白地址 - 100;
	if (异步执行) {
		return;
	}

	异步执行 = true;

	Hook汇编 = 汇编CALL;
	Hook汇编 = Hook汇编 + 144;
	Hook跳回 = Hook汇编 + 19;
	ByteArr Hook数据 = _ReadByteArr(Hook汇编, 19);
	ByteArr Hook原数据 = Hook数据;

	Hook数据 = _AppendToBytes(Hook数据, { 72, 184 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(判断地址, 8));

	Hook数据 = _AppendToBytes(Hook数据, { 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 });

	Hook数据 = _AppendToBytes(Hook数据, { 72, 187 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(空白地址, 8));

	Hook数据 = _AppendToBytes(Hook数据, { 255, 211 });

	Hook数据 = _AppendToBytes(Hook数据, { 72, 184 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(判断地址, 8));

	Hook数据 = _AppendToBytes(Hook数据, { 199, 0, 3, 0, 0, 0 });
	Hook数据 = _AppendToBytes(Hook数据, { 72, 129, 196, 0, 3, 0, 0 });

	Hook数据 = _AppendToBytes(Hook数据, { 255, 37, 0, 0, 0, 0 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(Hook跳回, 8));

	if (_ReadInt(汇编中转) == 0) {
		_WriteByteArr(汇编中转, Hook数据);
	}

	Hook数据.clear();
	_WriteByteArr(空白地址, _AppendToBytes(汇编代码, { 195 }));
	ByteArr tmp = { 255, 37, 0, 0, 0, 0 };
	tmp = _AppendToBytes(tmp, _IntToBytes(汇编中转, 8));
	tmp = _AppendToBytes(tmp, { 144, 144, 144, 144, 144 });
	_WriteByteArr(Hook汇编, tmp);
	_WriteInt(判断地址, 1);
	while (_ReadInt(判断地址) == 1)
	{
		Sleep(10);
	}
	_WriteByteArr(Hook汇编, Hook原数据);
	_WriteByteArr(空白地址, 取空白ByteArr(sizeof(汇编代码) + 16));

	异步执行 = false;
}