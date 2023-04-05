#include "自动.h"
#include "判断.h"
#include "公用.h"
#include "读写.h"
#include "判断.h"
#include "Call.h"
#include "组包.h"
#include "寻路.h"
#include "公用.h"
#include "结构.h"

全局自动 全局_自动;

VOID 自动开关() {
	static bool automaticSwitch;
	automaticSwitch = !automaticSwitch;
	if (automaticSwitch == true)
	{
		SetTimer(0, 1000, 200, (TIMERPROC)自动线程);
		//游戏公告("自动刷图 - 启动", 2);
		return;
	}
	KillTimer(0, 1000);
	//游戏公告("自动刷图 - 关闭", 2);
}

VOID 自动线程() {
	static bool 首次进图 = false;
	if (取游戏状态() == 0)
	{
		Sleep(200);
		进入城镇();
		return;
	}
	if (取游戏状态() == 1 && 取是否城镇())
	{
		城镇处理();
		return;
	}

	if (取游戏状态() == 2)
	{
		进入副本(全局_自动.副本编号);
		return;
	}

	if (取游戏状态() == 3)
	{
		Sleep(2000);
		if (首次进图 == false)
		{
			透明Call(读整数型(取人物基质()));
			Sleep(100);
			首次进图 = true;
		}

		if (判断_是否对话())
		{
			Sleep(30);
		}

		if (取是否开门() && !取是否BOSS房())
		{
			Sleep(300);
			模拟顺图();
			return;
		}

		if (取是否BOSS房())
		{
			if (取是否通关() || 取是否通关())
			{
				if (判断_是否对话())
				{
					Sleep(30);

				}
				Sleep(300);
				退出副本();
				首次进图 = false;
			}
		}
	}
}

VOID 进入城镇() {
	static int 全_已刷角色;
	int 全角色;
	全角色 = 读配置(L"自动配置", L"角色数量");
	if (全_已刷角色 + 1 > 全角色) {
		//监控(L"指定角色完成所有角色");
		//DeleteThread(threadHandle);
		//游戏公告("自动线程 - 关闭", 1);
		return;
	}

	全_已刷角色++;
	组包选择角色(全_已刷角色);
	//监控(L"进入角色[" + _IntToCString(全_已刷角色) + L"]");
	//监控(L"开始第[" + _IntToCString(全_已刷角色) + L"] 个角色, 剩余疲劳[" + _IntToCString(取疲劳值()) + L"]");
	Sleep(200);
	do
	{
		if (取游戏状态() == 1) {
			break;
		}
		Sleep(500);
	} while (取游戏状态() == 0);
}

VOID 城镇处理()
{
	if (取疲劳值() < 8)
	{
		返回角色();
		return;
	}
	int 刷图方式 = 读配置(L"自动配置", L"刷图方式");

	if (刷图方式 == 1) {
		全局_自动.副本编号 = 读配置(L"自动配置", L"副本编号");
		Sleep(100);
		全局_自动.副本难度 = 读配置(L"自动配置", L"副本等级");
	}

	区域Call(全局_自动.副本编号);
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
			if (取游戏状态() == 2) {
				return;
			}
		}
	} while (取游戏状态() == 1);
}

VOID 返回角色()
{

	//监控(L"疲劳值不足 · 即将切换角色");
	Sleep(100);
	组包返回角色();
	Sleep(500);
	do
	{
		if (取游戏状态() == 0) {
			break;
		}
		Sleep(500);
	} while (取游戏状态() == 1);

}

VOID 进入副本(int 副本编号) {
	if (全局_自动.副本难度 == 5)
	{
		if (副本编号 < 10 || 副本编号 == 1000)
		{
			组包进图(副本编号, 全局_自动.副本难度, 0, 0);
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
	else {
		组包进图(副本编号, 全局_自动.副本难度, 0, 0);
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
	if (!取是否开门() || 取是否BOSS房())
	{
		return;
	}
	地图数据 局_地图数据 = 寻路_地图数据();
	if (sizeof(局_地图数据.地图走法) >= 2)
	{
		int 过图方向 = 寻路_计算方向(局_地图数据.地图走法[0], 局_地图数据.地图走法[1]);
		int 顺图方式 = 读配置(L"自动配置", L"顺图方式");
		if (顺图方式 == 1)
		{

		}
		if (顺图方式 == 2) {

		}
	}
}


VOID 退出副本()
{

	Sleep(300);
	do
	{
		// 设置随机数种子
		std::srand(static_cast<unsigned int>(std::time(0)));
		// 生成随机数，范围是0到3
		int random_num = std::rand() % 4;
		组包翻牌(0, random_num);
		Sleep(200);
		组包出图();
		Sleep(1000);
	} while (取游戏状态() == 3 || 取是否城镇() == false);
}
