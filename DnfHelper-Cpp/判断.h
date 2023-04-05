#pragma once
#include "结构.h"

BOOL 判断_是否对话();
INT 解密(INT64 数据指针);
VOID 加密(INT64 数据指针, INT 修改数值);
INT 取游戏状态();
BOOL 取是否城镇();
BOOL 取是否开门();
BOOL 取是否BOSS房();
BOOL 取是否通关();
坐标 取BOSS房间();
坐标 取当前房间();
INT 取地图编号();
INT 取角色等级();
string 取地图名称();
INT 取疲劳值();
INT 等级地图();