#pragma once
#include "DataType.h"

// 取游戏数据
int 解密(__int64 数据指针);
VOID 加密(__int64 数据指针, int 修改数值);

int 取游戏状态();
bool 取是否城镇();
bool 取是否开门();
bool 取是否BOSS房();
bool 取是否通关();
坐标型 取BOSS房间();
坐标型 取当前房间();
int 取地图编号();
__int64 取角色疲劳();
int 取角色等级();
