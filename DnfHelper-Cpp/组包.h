#pragma once
#include "公用.h"

VOID 缓冲Call(_int64 缓冲参数);
VOID 加密Call(__int64 加密参数, int 加密长度);
VOID 发包Call();
VOID 组包跳过();
VOID 组包选择角色(int 位置);
VOID 组包整理();
VOID 组包分解(int 装备位置);
VOID 组包拾取(ULONG64 物品地址);
VOID 组包_卖物(int 装备位置);
VOID 组包返回角色();
VOID 组包选图();
VOID 组包_提炼(int 提取器位置, int 装备位置);
VOID 组包进图(int 编号, int 难度, int 深渊, int 练习);
VOID 完成任务(int id, int type);
VOID 放弃任务(int id);
VOID 接取任务(int id);
VOID 提交任务(int id);
VOID 组包翻牌(int 行, int 列);
VOID 组包出图();
VOID 组包过图(int X, int Y);
VOID 组包移动(int 大地图ID, int 小地图ID, int 城镇X坐标, int 城镇Y坐标);

