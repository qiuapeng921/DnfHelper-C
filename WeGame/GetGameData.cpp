#include "pch.h"
#include "GetGameData.h"
#include "ReadWrite.h"

int GetGameData::解密(__int64 数据指针)
{
	// 结果数据 = 位异或(_ReadLong(数据指针), 0x1F2A025C);
	// 结果数据 = 结果数据 - 4;
	// 返回((整数)结果数据);
	return 0;
}

VOID GetGameData::加密(__int64 数据指针, int 修改数值)
{
	// 运算数据 = 修改数值 + 4
	// 运算数据 = 位异或 (0x1F2A025C, 运算数据)
	// _WriteLong(数据指针, 运算数据)
}

int GetGameData::取游戏状态()
{
	return  _ReadInt(游戏状态);
}

bool GetGameData::取是否开门()
{
	if (解密(_ReadLong(_ReadLong(_ReadLong(人物基址) + 地图偏移) + 16) + 是否开门) == 0) {
		return true;
	}
	return false;
}

bool GetGameData::取是否通关()
{
	__int64 房间数据 = _ReadLong(_ReadLong(_ReadLong(房间编号) + 时间基址) + 门型偏移);
	int 判断数值 = _ReadInt(房间数据 + 篝火判断);
	if(判断数值 == 2 || 判断数值 == 0) {
		return true;
	}
	return false;
}
坐标型 GetGameData::取BOSS房间()
{
	坐标型 返回数据;
	__int64 房间数据 = _ReadLong(_ReadLong(_ReadLong(房间编号) + 时间基址) + 门型偏移);
	返回数据.x = 解密(房间数据 + BOSS房间X);
	返回数据.y = 解密(房间数据 + BOSS房间Y);
	return 返回数据;
}

坐标型 GetGameData::取当前房间() 
{
	坐标型 返回数据;
	__int64 房间数据 = _ReadLong(_ReadLong(_ReadLong(房间编号) + 时间基址) + 门型偏移);
	返回数据.x = _ReadInt(房间数据 + 当前房间X);
	返回数据.y = _ReadInt(房间数据 + 当前房间Y);
	return 返回数据;
}

int GetGameData::取地图编号() 
{
	return _ReadInt(副本编号);
}

int GetGameData::取角色疲劳() 
{
	return 解密(最大疲劳) - 解密(当前疲劳);
}

int GetGameData::取角色等级(){
	return _ReadInt(角色等级);
}