#include "pch.h"
#include "Automatic.h"
#include "Common.h"
#include "ReadWrite.h"
#include "GameBulletin.h"
#include "GetGameData.h"
#include "GameCall.h"

// 自动开关
static bool automaticSwitch;
// 自动线程句柄
HANDLE threadHandle = NULL;

VOID 自动开关() {
	automaticSwitch = !automaticSwitch;

	if (automaticSwitch == true)
	{
		threadHandle = ::_CreateThread(&自动线程);
		Message("自动刷图 - 启动", 1);
		return;
	}

	if (automaticSwitch == false &&  threadHandle != NULL)
	{
		_DeleteThread(threadHandle);
		Message("自动刷图 - 关闭", 1);
	}
}

VOID 自动线程() {

	static bool 是否进图 = false;

	while (true)
	{
		Message("自动线程循环", 1);
		Sleep(300);
		if (取游戏状态() == 0)
		{
			Sleep(200);
			进入城镇();
			continue;
		}
		if (取游戏状态() == 1 && 取是否城镇() == true)
		{
			城镇处理();
			continue;
		}

		if (取游戏状态() == 2)
		{
			// 进入副本(副本数据.编号, 副本数据.难度);
			continue;
		}

		if (取游戏状态() == 3)
		{
			if (是否进图 == false && _ReadInt(是否进图) == 1)
			{
				Message("当前副本编号", 1);
				透明Call(_ReadInt(人物基址));
				// 刷图功能();
				是否进图 = true;
			}

			if (取是否开门() == true && 取是否BOSS房() == false)
			{
				// 物品入包();
				模拟顺图();
				continue;
			}
			if (取是否BOSS房() == true)
			{
				if (取是否通关() == true || 取是否通关() == true)
				{
					// 刷图功能();
					退出副本();
					continue;
				}
			}
		}
	}
}

VOID 进入城镇() {

}

VOID 城镇处理() {
}

VOID 进入选图() {
}

VOID 返回角色() {
}

VOID 进入副本() {
}

VOID 模拟顺图() {
}

VOID 退出副本() {

}