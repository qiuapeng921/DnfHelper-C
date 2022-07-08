#include "pch.h"
#include "framework.h"
#include "Common.h"
#include "GameFunction.h"
#include "ReadWrite.h"
#include "Address.h"

VOID 武器冰冻() {
	static bool _switch = false;

	__int64 空白地址 = (__int64)_ApplyMemory(100);
	__int64 冰冻伤害 = 99999;
	__int64 kb = _ReadLong(空白地址);

	if (!_switch)
	{
		_WriteLong(空白地址, 0);
		_WriteLong(空白地址 + 4, 2000);
		_WriteLong(空白地址 + 8, 2000);
		_WriteLong(空白地址 + 12, 50);
		_WriteLong(空白地址 + 16, 100);
		_WriteLong(空白地址 + 20, 99);
		_WriteLong(空白地址 + 24, 130);
		_WriteLong(空白地址 + 28, 冰冻伤害 * 100000);
		__int64 武器 = _ReadLong(_ReadLong(人物基址) + 武器偏移);
		_WriteLong(武器 + 冰冻开始, 空白地址);
		_WriteLong(武器 + 冰冻结束, 空白地址 + 32);
		_DebugStringW(L"武器冰冻 - 启动");
	}
	else
	{
		__int64 武器 = _ReadLong(_ReadLong(人物基址) + 武器偏移);
		_WriteLong(武器 + 冰冻开始, 0);
		_WriteLong(武器 + 冰冻结束, 0);

		for (int i = 0; i <= 7; i++)
		{
			_WriteLong(空白地址, 0);
			空白地址 = 空白地址 + 4;
		}
		_DebugStringW(L"武器冰冻 - 关闭");
	}

	_switch = !_switch;

}

//void 技能开关() {
//
//	HWND hWnd = FindWindow(TEXT("地下城与勇士"), TEXT("地下城与勇士"));
//	static bool _switch = false;
//	if (_switch == false)
//	{
//		SetTimer(hWnd, 1, 频率, (TIMERPROC)遍历全屏技能);
//		公告("技能全屏 - 开启");
//	}
//	else
//	{
//		KillTimer(hWnd, 1);
//		公告("技能全屏 - 关闭");
//	}
//	_switch = !_switch;
//
//}



VOID HOOK伤害() {
	DWORD64 伤害地址 = 全局基址;

	_ReadConfig(L"倍攻", L"伤害");

	__int64 倍攻伤害 = 99999;
	const ByteArr 地址原数据 = _ReadByteArr(伤害地址, 10);

	static bool _switch = false;

	if (_switch)
	{
		vector<byte> data = _AppendToBytes(ByteArr{72, 190}, _IntToBytes(倍攻伤害 * 10000, 8));
		_WriteByteArr(伤害地址, data);
		_DebugStringW(L"HOOK伤害 - 启动");
	}
	else
	{
		_WriteByteArr(伤害地址, 地址原数据);
		_DebugStringW(L"HOOK伤害 - 关闭");
	}
	_switch = !_switch;
}

ByteArr 取空白ByteArr(int num) {
	ByteArr res;
	for (size_t i = 0; i < num; i++)
	{
		res.push_back(0);
	}
	return res;
}

VOID 汇编执行(vector<byte> 汇编代码) {
	__int64 汇编中转, 空白地址, Hook汇编, Hook跳回, 判断地址;

	static bool 异步执行;

	汇编中转 = 全局空白 + 300;
	空白地址 = 全局空白 + 500;
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


	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 184 }),
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(判断地址,8));

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 });
	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 187 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(空白地址,8));

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 255, 211 });
	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 184 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(判断地址,8));
	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 199, 0, 3, 0, 0, 0 });

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 129, 196, 0, 3, 0, 0 });
	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 255, 37, 0, 0, 0, 0 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(Hook跳回,8));

	if(_ReadLong(汇编中转) == 0) {
		_WriteByteArr(汇编中转, Hook数据);
	}

	_WriteByteArr(空白地址, _AppendToBytes(汇编代码, ByteArr{ 195 }));
	_WriteByteArr(Hook汇编, _AppendToBytes(_AppendToBytes(ByteArr{ 255, 37, 0, 0, 0, 0 }, _IntToBytes(汇编中转, 8)), ByteArr{ 144, 144, 144, 144, 144 }));
	_WriteLong( 判断地址, 1);
	while (_ReadLong(判断地址) == 1)
	{
		Sleep(10);
	}

	_WriteByteArr(Hook汇编, Hook原数据);
	_WriteByteArr(空白地址, 取空白ByteArr(sizeof(汇编代码) + 16));
	异步执行 = false;
}