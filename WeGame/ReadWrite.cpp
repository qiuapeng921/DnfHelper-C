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
	__int64 汇编中转, 空白地址, Hook汇编, Hook跳回, 判断地址;

	static bool 异步执行;
	static __int64 kb;
	if (kb == 0)
	{
		kb = (__int64)_ApplyMemory(1000);
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

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 184 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(判断地址, 8));

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 });

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 187 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(空白地址, 8));

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 255, 211 });

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 184 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(判断地址, 8));

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 199, 0, 3, 0, 0, 0 });
	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 129, 196, 0, 3, 0, 0 });

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 255, 37, 0, 0, 0, 0 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(Hook跳回, 8));

	if (_ReadLong(汇编中转) == 0) {
		_WriteByteArr(汇编中转, Hook数据);
	}

	Hook数据.clear();
	_WriteByteArr(空白地址, _AppendToBytes(汇编代码, ByteArr{ 195 }));
	ByteArr tmp = { 255, 37, 0, 0, 0, 0 };
	tmp = _AppendToBytes(tmp, _IntToBytes(汇编中转, 8));
	tmp = _AppendToBytes(tmp, ByteArr{ 144, 144, 144, 144, 144 });
	_WriteByteArr(Hook汇编, tmp);
	_WriteLong(判断地址, 1);
	while (_ReadLong(判断地址) == 1)
	{
		Sleep(10);
	}
	_WriteByteArr(Hook汇编, Hook原数据);
	_WriteByteArr(空白地址, 取空白ByteArr(sizeof(汇编代码) + 16));

	异步执行 = false;
}