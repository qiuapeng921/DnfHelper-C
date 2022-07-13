#include "pch.h"
#include "Automatic.h"
#include "Common.h"
#include "ReadWrite.h"
#include "GameBulletin.h"
#include "GetGameData.h"
#include "GameCall.h"
#include "GamePackage.h"
#include "GameMap.h"

// 自动开关
static bool automaticSwitch;
// 自动线程句柄
HANDLE threadHandle = NULL;

VOID 自动开关() {
	automaticSwitch = !automaticSwitch;
	if (automaticSwitch == true)
	{
		threadHandle = ::_CreateThread(&自动线程);
		Message("自动刷图 - 启动", 2);
		return;
	}

	if (automaticSwitch == false && threadHandle != NULL)
	{
		_DeleteThread(threadHandle);
		Message("自动刷图 - 关闭", 2);
	}
}

VOID 自动线程() {
	static bool 首次进图 = false;

	while (true)
	{
		Sleep(500);
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
			进入副本(_ReadConfig(L"自动配置", L"副本编号"), 0);
			continue;
		}

		if (取游戏状态() == 3)
		{
			if (首次进图 == false)
			{
				透明Call(_ReadInt(GetPersonAddr()));
				首次进图 = true;
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
					退出副本();
					首次进图 = false;
					continue;
				}
			}
		}
	}
}

VOID 进入城镇() {
	static int 全_已刷角色 = 0;
	if (全_已刷角色 + 1 > 32) {
		监控(L"指定角色完成所有角色");
		_DeleteThread(threadHandle);
		Message("自动线程 - 关闭", 1);
		return;
	}

	全_已刷角色++;
	组包选择角色(全_已刷角色);
	监控(L"进入角色[" + _IntToCString(全_已刷角色) + L"]");
	监控(L"开始第[" + _IntToCString(全_已刷角色) + L"] 个角色, 剩余疲劳[" + _IntToCString(取疲劳值()) + L"]");
	Sleep(200);
	do
	{
		if (取游戏状态() == 1) break;
		Sleep(500);
	} while (取游戏状态() == 0);
}

VOID 城镇处理() {
	if (取疲劳值() < 8)
	{
		返回角色();
		return;
	}
	区域Call(_ReadConfig(L"自动配置", L"副本编号"));
	Sleep(200);
	进入选图();
}

VOID 进入选图()
{
	do
	{
		Sleep(200);
		组包选图();
		for (int i = 1; i <= 10; i++)
		{
			Sleep(500);
			if (取游戏状态() == 2) return;
		}
	} while (取游戏状态() == 1);
}

VOID 返回角色() {
	监控(L"疲劳值不足 · 即将切换角色");
	Sleep(100);
	组包返回角色();
	Sleep(500);
	do
	{
		if (取游戏状态() == 0) break;
		Sleep(500);
	} while (取游戏状态() == 1);
}

VOID 进入副本(int 副本编号, int 副本难度) {
	if (副本难度 == 5)
	{
		if (副本编号 < 10 || 副本编号 == 1000)
		{
			组包进图(副本编号, 副本难度, 0, 0);
		}
		else
		{
			组包进图(副本编号, 4, 0, 0);
			组包进图(副本编号, 3, 0, 0);
			组包进图(副本编号, 2, 0, 0);
			组包进图(副本编号, 1, 0, 0);
			组包进图(副本编号, 0, 0, 0);
		}
	}
	else
	{
		组包进图(副本编号, 副本难度, 0, 0);
	}
	do
	{
		Sleep(200);
		for (int i = 1; i <= 10; i++)
		{
			Sleep(500);
			if (取游戏状态() == 3) break;
		}
	} while (取游戏状态() == 2);
}

VOID 模拟顺图()
{
	if (取是否开门() == false || 取是否BOSS房() == true)
	{
		return;
	}
	地图数据 局_地图数据 = 寻路_地图数据();
	if (sizeof(局_地图数据.地图走法) >= 2)
	{
		int 过图方向 = 寻路_计算方向(局_地图数据.地图走法[0], 局_地图数据.地图走法[1]);
		坐标过图(过图方向);
	}
}

VOID 通关计次()
{
	int 通关计次 = _ReadConfig(L"计次", L"次数");
	通关计次++;
	_WriteConfig(L"计次", L"次数", _IntToCString(通关计次));

	监控(L"当前副本 [ " + 取地图名称() + L" ]");
	监控(L"自动刷图 [" + _IntToCString(通关计次) + L" ]" + L"剩余疲劳 [" + _IntToCString(取疲劳值()) + L" ]");
}

VOID 退出副本()
{
	通关计次();
	Sleep(200);
	//物品入包();
	do
	{
		组包翻牌(0, _Rand(0, 3));
		Sleep(200);
		组包出图();
		Sleep(200);
	} while (取游戏状态() == 3 || 取是否城镇() == false);
}