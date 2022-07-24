#include "pch.h"
#include "判断.h"

#include "读写.h"
#include "游戏Call.h"

int 解密(__int64 数据指针)
{
	__int64 temp = _ReadLong(数据指针);
	temp = temp ^ 0x1F2A025C;
	temp -= 4;
	return (int)temp;
}

VOID 加密(__int64 数据指针, int 修改数值)
{
	数据指针 += 4;
	数据指针 = 数据指针 ^ 0x1F2A025C;
	_WriteLong(数据指针, 数据指针);
}

// 0选角 1城镇 2选图 3图内 5选择频道
int 取游戏状态()
{
	return  _ReadInt(游戏状态);
}

bool 取是否城镇()
{
	if (_ReadLong(_ReadLong(取人物基质()) + 地图偏移) == 0)
	{
		return true;
	}
	return false;
}

bool 取是否开门()
{
	if (解密(_ReadLong(_ReadLong(_ReadLong(取人物基质()) + 地图偏移) + 16) + 是否开门) == 0)
	{
		return true;
	}
	return false;
}

bool 取是否BOSS房()
{
	坐标型 当前 = 取当前房间();
	坐标型 BOSS = 取BOSS房间();
	if (当前.x == BOSS.x && 当前.y == BOSS.y)
	{
		return true;
	}
	return false;
}

bool 取是否通关()
{
	__int64 房间数据 = _ReadLong(_ReadLong(_ReadLong(房间编号) + 时间基址) + 门型偏移);
	int 判断数值 = _ReadInt(房间数据 + 篝火判断);
	if(判断数值 == 2 || 判断数值 == 0) 
	{
		return true;
	}
	return false;
}
坐标型 取BOSS房间()
{
	坐标型 返回数据;
	__int64 房间数据 = _ReadLong(_ReadLong(_ReadLong(房间编号) + 时间基址) + 门型偏移);
	返回数据.x = 解密(房间数据 + BOSS房间X);
	返回数据.y = 解密(房间数据 + BOSS房间Y);
	return 返回数据;
}

坐标型 取当前房间() 
{
	坐标型 返回数据;
	__int64 房间数据 = _ReadLong(_ReadLong(_ReadLong(房间编号) + 时间基址) + 门型偏移);
	返回数据.x = _ReadInt(房间数据 + 当前房间X);
	返回数据.y = _ReadInt(房间数据 + 当前房间Y);
	return 返回数据;
}

int 取地图编号() 
{
	return _ReadInt(副本编号);
}

int 取疲劳值()
{
	return 解密(最大疲劳) - 解密(当前疲劳);
}

int 取角色等级(){
	return _ReadInt(角色等级);
}

CString 取地图名称()
{
	__int64 房间数据 = _ReadLong(_ReadLong(_ReadLong(房间编号) + 时间基址) + 门型偏移);
	return _UnicodeToAnsi(_ReadByteArr(_ReadLong(房间数据 + 地图名称), 52));
}