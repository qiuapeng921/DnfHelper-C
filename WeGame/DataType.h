#pragma once
#include "Common.h"

struct 坐标型 {
	int x;
	int y;
	int z;
};

struct 地图数据
{
	char* 地图名称;
	int 地图编号;
	vector<int> 地图通道;
	坐标型 起始坐标;
	坐标型 终点坐标;
	int 宽;
	int 高;
	vector<坐标型> 地图走法;
	int 消耗疲劳;
	int 通道数量;
	__int64 临时变量;
};

struct 游戏地图
{
	坐标型 地图坐标;
	bool 地图左边;
	bool 地图右边;
	bool 地图上边;
	bool 地图下边;
	int 地图通道;
	int 背景颜色;
};

struct 地图节点
{
	int 地图F点;
	int 地图G点;
	int 地图H点;
	坐标型 当前坐标;
	坐标型 最终坐标;
};
