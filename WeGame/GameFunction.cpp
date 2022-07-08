#include "pch.h"
#include "framework.h"
#include "Common.h"
#include "GameFunction.h"
#include "ReadWrite.h"
#include "Address.h"
#include "GameCall.h"
#include "GameBulletin.h"

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
		__int64 武器 = _ReadLong(_ReadLong(GetPersonAddr()) + 武器偏移);
		_WriteLong(武器 + 冰冻开始, 空白地址);
		_WriteLong(武器 + 冰冻结束, 空白地址 + 32);
		Message("武器冰冻 - 启动", 1);
	}
	else
	{
		__int64 武器 = _ReadLong(_ReadLong(GetPersonAddr()) + 武器偏移);
		_WriteLong(武器 + 冰冻开始, 0);
		_WriteLong(武器 + 冰冻结束, 0);

		for (int i = 0; i <= 7; i++)
		{
			_WriteLong(空白地址, 0);
			空白地址 = 空白地址 + 4;
		}
		Message("武器冰冻 - 关闭", 1);
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
	__int64 倍攻伤害 = 9999999;
	ByteArr 地址原数据;
	static bool _switch = false;
	if (!_switch)
	{
		地址原数据 = _ReadByteArr(全局基址, 10);
		ByteArr data = _AppendToBytes(ByteArr{ 72, 190 }, _IntToBytes(倍攻伤害, 8));
		_WriteByteArr(全局基址, data);
		Message("HOOK伤害 - 启动", 1);
	}
	else
	{
		_WriteByteArr(全局基址, 地址原数据);
		Message("HOOK伤害 - 关闭", 1);
	}
	_switch = !_switch;
}