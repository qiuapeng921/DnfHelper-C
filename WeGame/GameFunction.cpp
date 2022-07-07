#include "pch.h"
#include "framework.h"
#include "Address.h"
#include "Common.h"
#include "GameFunction.h"
#include "ReadWrite.h"

VOID 武器冰冻() {
	//MessageBoxW(NULL, L"武器冰冻", L"功能", MB_OK);

	BOOL static 冰冻开关 = FALSE;
	DWORD64 空白地址 = 全局空白;
	if (冰冻开关 == FALSE)
	{
		DWORD64 kb = _ReadLong(空白地址);

		_WriteLong(空白地址, 0);
		_WriteLong(空白地址 + 4, 2000);
		_WriteLong(空白地址 + 8, 2000);
		_WriteLong(空白地址 + 12, 0);
		_WriteLong(空白地址 + 16, 0);
		_WriteLong(空白地址 + 20, 0);
		_WriteLong(空白地址 + 24, 0);
		_WriteLong(空白地址 + 28, 0);
		DWORD64 武器 = _ReadLong(_ReadLong(人物基址) + 武器偏移);
		_WriteLong(武器 + 冰冻开始, 空白地址);
		_WriteLong(武器 + 冰冻结束, 空白地址 + 32);
		冰冻开关 = TRUE;
		_DebugStringW(L"冰冻开启 - 启动");
		return;
	}
	DWORD64 武器 = _ReadLong(_ReadLong(人物基址) + 武器偏移);
	_WriteLong(武器 + 冰冻开始, 0);
	_WriteLong(武器 + 冰冻结束, 0);
	for (int i = 0; i >= 7; i++)
	{
		_WriteLong(空白地址, 0);
		空白地址 = 空白地址 + 4;
	}
	冰冻开关 = FALSE;
	_DebugStringW(L"冰冻开启 - 关闭");
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
	BOOL static HOOK开关 = false;

	BYTE* 地址原数据;

	DWORD64 伤害地址 = 全局基址;
	HOOK开关 = !HOOK开关;

	if (HOOK开关)
	{
		地址原数据 = _ReadBytes(伤害地址,10);

		vector<byte> data = { 72,190,127,150,152,0 };
		_WriteByteArr(伤害地址, data);
	}
	else
	{
		//写字节集型(伤害地址,地址原数据,10);
	}
}


