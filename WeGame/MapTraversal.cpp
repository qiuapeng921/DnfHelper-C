#include "pch.h"
#include "MapTraversal.h"
#include "Common.h"
#include "ReadWrite.h"
#include "GetGameData.h"
#include "GameBulletin.h"
#include "GameCall.h"

vector<__int64> 遍历怪物()
{
	vector<__int64> 全_怪物;

	if (取游戏状态() != 3)
	{
		return 全_怪物;
	}
	__int64 首地址_ = _ReadLong(_ReadLong(_ReadLong(_ReadLong(GetPersonAddr()) + 地图偏移) + 16) + 地图开始2);
	__int64 尾地址_ = _ReadLong(_ReadLong(_ReadLong(_ReadLong(GetPersonAddr()) + 地图偏移) + 16) + 地图结束2);
	int 怪物数量 = (int)(尾地址_ - 首地址_) / 16;
	for (int i = 1; i <= 怪物数量; i++)
	{
		__int64 怪物地址 = _ReadLong(_ReadLong(首地址_ + i * 16) + 16) - 32;
		int 怪物类型 = _ReadInt(怪物地址 + 类型偏移);
		int 怪物阵营 = _ReadInt(怪物地址 + 阵营偏移);
		int 怪物代码 = _ReadInt(怪物地址 + 代码偏移);
		int 怪物血量_ = _ReadInt(怪物地址 + 怪物血量);
		if (怪物类型 == 529 || 怪物类型 == 273)
		{
			if (怪物地址 == _ReadLong(GetPersonAddr()))
			{
				continue;
			}
			if (怪物阵营 != 0 && 怪物代码 != 0 && 怪物血量_ != 0)
			{
				全_怪物.push_back(怪物地址);
			}
		}
	}
	return 全_怪物;
}

VOID 全屏技能() {
	while (true)
	{
		// 遍历全屏();
		Sleep(_ReadConfig(L"全屏配置",L"技能频率"));
		技能Call(0, 39002, 0, 0, 0, 0, 0);
	}
}

坐标型 读坐标(__int64 读取指针)
{
	坐标型 坐标;
	__int64 指针;

	int 类型 = _ReadInt(读取指针 + 类型偏移);
	if (类型 == 273)
	{
		指针 = _ReadLong(读取指针 + 读取坐标);
		坐标.x = _ReadInt(指针 + 0);
		坐标.y = _ReadInt(读取指针 + 读取坐标);
		坐标.z = _ReadInt(读取指针 + 读取坐标);
		return 坐标;
	}
	指针 = _ReadLong(读取指针 + 对象坐标);
	坐标.x = _ReadInt(指针 + 32);
	坐标.y = _ReadInt(指针 + 36);
	坐标.z = _ReadInt(指针 + 40);
	return 坐标;
}

VOID 遍历全屏()
{
	//坐标型 怪物坐标;

	vector<__int64> 怪物数量 = 遍历怪物();
	for (int i = 1; i <= 怪物数量.size(); i++)
	{
		怪物数量.pop_back();
		//怪物坐标 = 读坐标();
	}
}