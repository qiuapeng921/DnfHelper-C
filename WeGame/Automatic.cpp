#include "pch.h"
#include "Automatic.h"
#include "Common.h"
#include "ReadWrite.h"
#include "GameBulletin.h"
#include "GetGameData.h"
#include "GameCall.h"
#include "GamePackage.h"

// 自动开关
static bool automaticSwitch;
// 自动线程句柄
HANDLE threadHandle = NULL;

VOID 自动开关() {
	automaticSwitch = !automaticSwitch;
	区域Call(192);//  ' 移动到副本
	Sleep(200);
	进入选图();
	Sleep(100);
	组包进图(192, 0, 0, 0);
	return;
	if (automaticSwitch == true)
	{
		threadHandle = ::_CreateThread(&自动线程);
		Message("自动刷图 - 启动", 1);
		return;
	}

	if (automaticSwitch == false && threadHandle != NULL)
	{
		_DeleteThread(threadHandle);
		Message("自动刷图 - 关闭", 1);
	}
}

VOID 自动线程() {

	static bool 是否进图 = false;

	while (true)
	{
		Sleep(300);
		if (取游戏状态() == 0)
		{
			Sleep(200);
			进入城镇();
			_DebugStringW(L"进入城镇");
			continue;
		}
		if (取游戏状态() == 1 && 取是否城镇() == true)
		{
			_DebugStringW(L"城镇处理");

			城镇处理();
			continue;
		}

		if (取游戏状态() == 2)
		{
			_DebugStringW(L"进入副本");

			进入副本(192, 0);
			continue;
		}

		if (取游戏状态() == 3)
		{
			if (是否进图 == false && _ReadInt(是否进图) == 1)
			{
				_DebugStringW(L"首次进图");

				Message("当前副本编号", 1);
				透明Call(_ReadInt(人物基址));
				// 刷图功能();
				是否进图 = true;
			}

			if (取是否开门() == true && 取是否BOSS房() == false)
			{
				_DebugStringW(L"模拟顺图");
				// 物品入包();
				模拟顺图();
				continue;
			}
			if (取是否BOSS房() == true)
			{
				if (取是否通关() == true || 取是否通关() == true)
				{
					_DebugStringW(L"通关");

					// 刷图功能();
					退出副本();
					是否进图 = false;
					continue;
				}
			}
		}
	}
}

VOID 进入城镇() {

}

VOID 城镇处理() {
	区域Call(192);//  ' 移动到副本
	Sleep(200);
}

VOID 进入选图() {
	Sleep(200);
	组包选图();
}

VOID 返回角色() {
}

VOID 进入副本(int 副本编号, int 副本难度) {
	组包进图(副本编号, 副本难度, 0, 0);
}

VOID 模拟顺图() {
	Message("顺图", 1);
}

VOID 退出副本() {
	Sleep(200);
	//物品入包();
	Sleep(200);
	// 通关计次 ();
	组包翻牌(0, _Rand(0, 3));
	组包出图();
}