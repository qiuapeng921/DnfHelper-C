#include "pch.h"
#include "GameMap.h"
#include "Address.h"
#include "ReadWrite.h"
#include "GetGameData.h"
#include "GameCall.h"
#include "GamePackage.h"

地图数据 寻路_地图数据()
{
	地图数据 局_地图数据;
	ULONG64 局_房间数据 = _ReadLong(_ReadLong(_ReadLong(房间编号) + 时间基址) + 门型偏移);
	ULONG64 局_房间索引 = 解密(局_房间数据 + 索引偏移);

	局_地图数据.宽 = _ReadInt(_ReadLong(局_房间数据 + 宽高偏移) + 局_房间索引 * 8 + 0);
	局_地图数据.高 = _ReadInt(_ReadLong(局_房间数据 + 宽高偏移) + 局_房间索引 * 8 + 4);
	局_地图数据.临时变量 = _ReadLong(_ReadLong(局_房间数据 + 数组偏移) + 32 * 局_房间索引 + 8);
	局_地图数据.通道数量 = 局_地图数据.宽 * 局_地图数据.高;
	for (size_t i = 0; i < 局_地图数据.通道数量; i++)
	{
		局_地图数据.地图通道.insert(局_地图数据.地图通道.begin() + i, _ReadInt(局_地图数据.临时变量 + i * 4));
	}
	局_地图数据.起始坐标.x = 取当前房间().x + 1;
	局_地图数据.起始坐标.y = 取当前房间().y + 1;
	局_地图数据.终点坐标.x = 取BOSS房间().x + 1;
	局_地图数据.终点坐标.y = 取BOSS房间().y + 1;
	if (局_地图数据.起始坐标.x == 局_地图数据.终点坐标.x && 局_地图数据.起始坐标.y == 局_地图数据.终点坐标.y)
	{
		return 局_地图数据;
	}
	局_地图数据.消耗疲劳 = 寻路_获取走法(局_地图数据.地图通道, 局_地图数据.宽, 局_地图数据.高, 局_地图数据.起始坐标, 局_地图数据.终点坐标, 局_地图数据.地图走法);
	return 局_地图数据;
}
DWORD 寻路_获取走法(vector<DWORD> 参_地图通道, DWORD 参_宽度, DWORD 参_高度, 坐标型 参_地图起点, 坐标型 参_地图终点, vector<坐标型>& 参_真实走法)
{
	坐标型 start_coordinate;
	坐标型 end_coordinate;
	vector<vector<游戏地图>> map_flag;
	vector<vector<游戏地图>> map_array;
	vector<坐标型> cross_way;

	if (参_地图起点.x == 参_地图终点.x && 参_地图起点.y == 参_地图终点.y)
	{
		参_真实走法.clear();
		参_真实走法.resize(0);
		return 0;
	}
	寻路_生成地图(参_宽度, 参_高度, 参_地图通道, map_array);
	寻路_显示地图(map_array, 参_宽度, 参_高度, map_flag);
	start_coordinate.x = 参_地图起点.x * 3 - 2;
	start_coordinate.y = 参_地图起点.y * 3 - 2;
	end_coordinate.x = 参_地图终点.x * 3 - 2;
	end_coordinate.y = 参_地图终点.y * 3 - 2;
	寻路_路径算法(map_flag, start_coordinate, end_coordinate, 参_宽度 * 3, 参_高度 * 3, cross_way);
	return 寻路_整理坐标(cross_way, 参_真实走法);

}
VOID 寻路_生成地图(DWORD 参_宽度, DWORD 参_高度, vector<DWORD> 参_地图通道, vector<vector<游戏地图>>& 参_游戏地图)
{
	参_游戏地图.clear();
	参_游戏地图.resize(参_宽度);
	for (DWORD x = 0; x < 参_宽度; x++)
	{
		参_游戏地图[x].resize(参_高度);
	}
	int i = 0;
	for (DWORD y = 0; y < 参_高度; y++)
	{
		for (DWORD x = 0; x < 参_宽度; x++)
		{
			参_游戏地图[x][y].地图坐标.x = x;
			参_游戏地图[x][y].地图坐标.y = y;
			参_游戏地图[x][y].地图通道 = 参_地图通道[i];
			参_游戏地图[x][y].地图左边 = 寻路_判断方向(参_地图通道[i], 0);
			参_游戏地图[x][y].地图右边 = 寻路_判断方向(参_地图通道[i], 1);
			参_游戏地图[x][y].地图上边 = 寻路_判断方向(参_地图通道[i], 2);
			参_游戏地图[x][y].地图下边 = 寻路_判断方向(参_地图通道[i], 3);
			参_游戏地图[x][y].背景颜色 = 0xFFFFFF;
			i++;
			if (参_游戏地图[x][y].地图通道 == 0)
				参_游戏地图[x][y].背景颜色 = 0x000000;
		}
	}
}
VOID 寻路_显示地图(vector<vector<游戏地图>> 参_地图数组, DWORD 参_宽度, DWORD 参_高度, vector<vector<游戏地图>>& 参_地图标签)
{
	参_地图标签.clear();
	参_地图标签.resize(参_宽度 * (DWORD64)3);
	for (DWORD x = 0; x < 参_宽度 * 3; x++)
	{
		参_地图标签[x].resize(参_高度 * 3);
	}
	for (DWORD y = 0; y < 参_高度; y++)
	{
		for (DWORD x = 0; x < 参_宽度; x++)
		{
			参_地图标签[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)2][(y + (DWORD64)1) * (DWORD64)3 - (DWORD64)2].背景颜色 = 0xFFFFFF;
			if (参_地图数组[x][y].地图左边)
				参_地图标签[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)3][(y + (DWORD64)1) * (DWORD64)3 - (DWORD64)2].背景颜色 = 0xFFFFFF;
			if (参_地图数组[x][y].地图右边)
				参_地图标签[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)1][(y + (DWORD64)1) * (DWORD64)3 - (DWORD64)2].背景颜色 = 0xFFFFFF;
			if (参_地图数组[x][y].地图上边)
				参_地图标签[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)2][(y + (DWORD64)1) * (DWORD64)3 - (DWORD64)3].背景颜色 = 0xFFFFFF;
			if (参_地图数组[x][y].地图下边)
				参_地图标签[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)2][(y + (DWORD64)1) * (DWORD64)3 - (DWORD64)1].背景颜色 = 0xFFFFFF;
		}
	}
}
VOID 寻路_路径算法(vector<vector<游戏地图>> 参_地图标签, 坐标型 参_地图起点, 坐标型 参_地图终点, DWORD 参_宽度, DWORD 参_高度, vector<坐标型>& 参_走法数组)
{
	BOOL 已存在开放列表, 已存在关闭列表;
	坐标型 待检测坐标;
	地图节点 待检测节点, 临时节点;
	vector<地图节点> 开放列表, 关闭列表;
	DWORD 最短编号 = 0;
	DWORD 最小F值, 预测G值;
	DWORD x, y;
	临时节点.当前坐标.x = 参_地图起点.x;
	临时节点.当前坐标.y = 参_地图起点.y;
	参_地图标签[参_地图起点.x][参_地图起点.y].背景颜色 = 0x00FF00;
	参_地图标签[参_地图终点.x][参_地图终点.y].背景颜色 = 0x0000FF;
	开放列表.insert(开放列表.begin(), 临时节点);
	do
	{
		最小F值 = 0;
		for (y = 0; y < 开放列表.size(); y++)
		{
			if (最小F值 == 0)
			{
				最小F值 = 开放列表[0].地图F点;
				最短编号 = y;
			}
			if (开放列表[y].地图F点 < 最小F值)
			{
				最小F值 = 开放列表[y].地图F点;
				最短编号 = y;
			}
		}
		临时节点 = 开放列表[最短编号];
		开放列表.erase(开放列表.begin() + 最短编号);
		关闭列表.insert(关闭列表.begin(), 临时节点);
		if (临时节点.当前坐标.x != 参_地图起点.x || 临时节点.当前坐标.y != 参_地图起点.y)
		{
			if (临时节点.当前坐标.x != 参_地图终点.x || 临时节点.当前坐标.y != 参_地图终点.y)
			{
				参_地图标签[临时节点.当前坐标.x][临时节点.当前坐标.y].背景颜色 = 0x0080FF;
			}
		}
		for (y = 0; y < 关闭列表.size(); y++)
		{
			if (关闭列表[y].当前坐标.x == 参_地图终点.x && 关闭列表[y].当前坐标.y == 参_地图终点.y)
			{
				待检测节点 = 关闭列表[y];
				do
				{
					for (unsigned int x = 0; x < 关闭列表.size(); x++)
					{
						if (关闭列表[x].当前坐标.x == 待检测节点.最终坐标.x && 关闭列表[x].当前坐标.y == 待检测节点.最终坐标.y)
						{
							待检测节点 = 关闭列表[x];
							break;
						}
					}
					if (待检测节点.当前坐标.x != 参_地图起点.x || 待检测节点.当前坐标.y != 参_地图起点.y)
					{
						参_地图标签[待检测节点.当前坐标.x][待检测节点.当前坐标.y].背景颜色 = 0x00D8D8;
						参_走法数组.insert(参_走法数组.begin(), 待检测节点.当前坐标);
					}
				} while (待检测节点.当前坐标.x != 参_地图起点.x || 待检测节点.当前坐标.y != 参_地图起点.y);
				参_走法数组.insert(参_走法数组.begin(), 参_地图起点);
				参_走法数组.insert(参_走法数组.end(), 参_地图终点);
				return;
			}
		}
		for (y = 0; y < 4; y++)
		{
			if (y == 0)
			{
				待检测坐标.x = 临时节点.当前坐标.x;
				待检测坐标.y = 临时节点.当前坐标.y - 1;
			}
			else if (y == 1)
			{
				待检测坐标.x = 临时节点.当前坐标.x - 1;
				待检测坐标.y = 临时节点.当前坐标.y;
			}
			else if (y == 2)
			{
				待检测坐标.x = 临时节点.当前坐标.x + 1;
				待检测坐标.y = 临时节点.当前坐标.y;
			}
			else
			{
				待检测坐标.x = 临时节点.当前坐标.x;
				待检测坐标.y = 临时节点.当前坐标.y + 1;
			}
			if (待检测坐标.x < 0 || 待检测坐标.x >(参_宽度 - 1) || 待检测坐标.y < 0 || 待检测坐标.y >(参_高度 - 1))
				continue;
			if (参_地图标签[待检测坐标.x][待检测坐标.y].背景颜色 == 0x000000)
				continue;
			已存在关闭列表 = false;
			for (x = 0; x < 关闭列表.size(); x++)
			{
				if (关闭列表[x].当前坐标.x == 待检测坐标.x && 关闭列表[x].当前坐标.y == 待检测坐标.y)
				{
					已存在关闭列表 = true;
					break;
				}
			}
			if (已存在关闭列表)
				continue;
			已存在开放列表 = false;
			for (x = 0; x < 开放列表.size(); x++)
			{
				if (开放列表[x].当前坐标.x == 待检测坐标.x && 开放列表[x].当前坐标.y == 待检测坐标.y)
				{
					if (待检测坐标.x != 临时节点.当前坐标.x || 待检测坐标.y != 临时节点.当前坐标.y)
						预测G值 = 14;
					else
						预测G值 = 10;
					if (临时节点.地图G点 + 预测G值 < 开放列表[x].地图G点)
						开放列表[x].最终坐标 = 临时节点.当前坐标;
					已存在开放列表 = true;
					break;
				}
			}
			if (已存在开放列表 == false)
			{
				if (待检测坐标.x == 临时节点.当前坐标.x || 待检测坐标.y == 临时节点.当前坐标.y)
					预测G值 = 10;
				else
					预测G值 = 14;
				待检测节点.地图G点 = 临时节点.地图G点 + 预测G值;
				待检测节点.地图H点 = 参_地图终点.x - 待检测坐标.x * 10 + 参_地图终点.y - 待检测坐标.y * 10;
				待检测节点.地图F点 = 待检测节点.地图G点 + 待检测节点.地图H点;
				待检测节点.当前坐标 = 待检测坐标;
				待检测节点.最终坐标 = 临时节点.当前坐标;
				开放列表.insert(开放列表.begin(), 待检测节点);
			}
		}
	} while (开放列表.size() != 0);
}
DWORD 寻路_整理坐标(vector<坐标型> 参_模拟走法, vector<坐标型>& 参_真实走法)
{
	DWORD x, y;
	DWORD k = 0;
	坐标型 局_临时坐标;
	for (DWORD i = 0; i < 参_模拟走法.size(); i++)
	{
		x = (参_模拟走法[i].x + 2) % 3;
		y = (参_模拟走法[i].y + 2) % 3;
		if (x == 0 && y == 0)
		{
			局_临时坐标.x = (参_模拟走法[i].x + 2) / 3 - 1;
			局_临时坐标.y = (参_模拟走法[i].y + 2) / 3 - 1;
			参_真实走法.insert(参_真实走法.begin() + k, 局_临时坐标);
			k++;
		}
	}
	return(k);
}
BOOL  寻路_判断方向(DWORD 参_通向, DWORD 参_方向)
{
	unsigned char 局_方向数组[4];
	unsigned char 局_方向集合[16][4] = { { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 1, 1, 0 }, { 1, 0, 0, 0 }, { 1, 1, 0, 0 }, { 1, 0, 1, 0 }, { 1, 1, 1, 0 },
	{ 0, 0, 0, 1 }, { 0, 1, 0, 1 }, { 0, 0, 1, 1 }, { 0, 1, 1, 1 }, { 1, 0, 0, 1 }, { 1, 1, 0, 1 }, { 1, 0, 1, 1 }, { 1, 1, 1, 1 } };
	if (参_通向 >= 0 && 参_通向 <= 15)
		for (int i = 0; i < 4; i++)
			局_方向数组[i] = 局_方向集合[参_通向][i];
	else
		for (int i = 0; i < 4; i++)
			局_方向数组[i] = 0;
	if (局_方向数组[参_方向] == 1)
		return TRUE;
	else
		return FALSE;
}

DWORD 寻路_计算方向(坐标型 参_当前房间, 坐标型 参_下个房间)
{
	DWORD 局_方向 = 0;
	DWORD 局_X, 局_Y;
	局_X = 参_当前房间.x - 参_下个房间.x;
	局_Y = 参_当前房间.y - 参_下个房间.y;
	if (局_X == 0 && 局_Y == 0)
	{
		return 4;
	}

	if (局_X == 0)
	{
		if (局_Y == 1)
		{
			局_方向 = 2;
		}
		else
		{
			局_方向 = 3;
		}
	}
	else if (局_Y == 0)
	{
		if (局_X == 1)
		{
			局_方向 = 0;
		}
		else
		{
			局_方向 = 1;
		}
	}
	return 局_方向;
}

VOID 坐标_顺图(int 方向ID)
{
	__int64 顺图数据 = 顺图Call(方向ID);
	__int64 坐标结构 = 顺图数据;

	int 起始X = _ReadInt(坐标结构 + 0);
	int 起始Y = _ReadInt(坐标结构 + 4);
	int 结束X = _ReadInt(坐标结构 + 8);
	int 结束Y = _ReadInt(坐标结构 + 12);

	// 0左
	int X = 0;
	int Y = 0;
	if (方向ID == 0)
	{
		X = 起始X + 结束X + 20;
		Y = 起始Y + 结束Y / 2;
	}
	// 1右
	if (方向ID == 1)
	{
		X = 起始X - 20;
		Y = 起始Y + 结束Y / 2;
	}
	// 2上
	if (方向ID == 2)
	{

		X = 起始X + 结束X / 2;
		Y = 起始Y + 结束Y + 20;
	}
	// 3下
	if (方向ID == 3)
	{
		X = 起始X + 结束X / 2;
		Y = 起始Y - 20;
	}
	坐标Call(X, Y, 0);
	Sleep(100);
	坐标Call(起始X + 结束X / 2, 起始Y, 0);
}


VOID 组包_顺图(int 方向ID)
{

	if (取是否城镇() == true) {
		return;
	}

	if (取是否开门() == false){
		return;
	}

	坐标型	当前房间 = 取当前房间();
	if (方向ID == 0)
	{
		组包过图(当前房间.x - 1, 当前房间.y);
	}
	if (方向ID == 1)
	{
		组包过图(当前房间.x + 1, 当前房间.y);
	}

	if (方向ID == 2)
	{
		组包过图(当前房间.x, 当前房间.y - 1);
	}
	if (方向ID == 3)
	{
		组包过图(当前房间.x, 当前房间.y + 1);
	}
}

VOID 组包_下() 
{
	坐标型 当前房间 = 取当前房间();
	组包过图(当前房间.x, 当前房间.y + 1);
}

VOID 组包_左() 
{
	坐标型 当前房间 = 取当前房间();
	组包过图(当前房间.x - 1, 当前房间.y);
}

VOID 组包_右() 
{
	坐标型 当前房间 = 取当前房间();
	组包过图(当前房间.x + 1, 当前房间.y);
}