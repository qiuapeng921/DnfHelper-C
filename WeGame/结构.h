#pragma once
#include "公用.h"

struct 坐标型 {
	DWORD x;
	DWORD y;
	DWORD z;
};

struct 地图数据
{
	CHAR* 地图名称;
	DWORD 地图编号;
	vector<DWORD> 地图通道;
	坐标型 起始坐标;
	坐标型 终点坐标;
	DWORD 宽;
	DWORD 高;
	vector<坐标型> 地图走法;
	DWORD 消耗疲劳;
	DWORD 通道数量;
	ULONG64 临时变量;
};

struct 游戏地图
{
	坐标型 地图坐标;
	BOOL 地图左边;
	BOOL 地图右边;
	BOOL 地图上边;
	BOOL 地图下边;
	DWORD 地图通道;
	DWORD 背景颜色;
};

struct 地图节点
{
	DWORD 地图F点;
	DWORD 地图G点;
	DWORD 地图H点;
	坐标型 当前坐标;
	坐标型 最终坐标;
};
