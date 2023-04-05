#pragma once
#include "公用.h"

using namespace std;

typedef struct 坐标
{
	INT x;
	INT y;
	INT z;
}坐标;

struct 地图数据
{
	CHAR* 地图名称;
	DWORD 地图编号;
	vector<DWORD> 地图通道;
	坐标 起始坐标;
	坐标 终点坐标;
	DWORD 宽;
	DWORD 高;
	vector<坐标> 地图走法;
	DWORD 消耗疲劳;
	DWORD 通道数量;
	ULONG64 临时变量;
};

struct 游戏地图
{
	坐标 地图坐标;
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
	坐标 当前坐标;
	坐标 最终坐标;
};

struct 全局自动
{
	DWORD 全局任务;
	DWORD 全_回走;
	DWORD 副本编号;
	DWORD 副本难度;
	bool 参_已经进图;
	bool 参_可以顺图;
	bool 参_切换角色;
	DWORD 参_刷图角色;
	DWORD 参_公告角色;
	DWORD 参_顺图方向;
	DWORD 参_顺图计次;
	DWORD 参_皇宫根特;
	DWORD 参_无底坑道;
	DWORD 参_记忆之地;
	DWORD 参_痛苦地下室;
	DWORD 参_暗黑神殿;
};
extern 全局自动 全局_自动;

struct 遍历数据
{
	ULONG64 人物指针;
	ULONG64 地图指针;
	ULONG64 遍历指针;
	ULONG64 遍历血量;

	ULONG64 首地址;
	ULONG64 尾地址;

	int 遍历数量;
	int 遍历类型;
	int 遍历阵营;

	ULONG64 物品指针;

	size_t 遍历次数;
	int 遍历代码;
	int 怪物阵营;
	int 技能个数;
	int 怪物血量;
	wstring 遍历名称;

	wstring 物品名称;

	int 物品数量;
	int 物品代码;
};
