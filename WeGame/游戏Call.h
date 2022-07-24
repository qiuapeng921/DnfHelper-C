#pragma once
#include "Common.h"

VOID 技能Call(__int64 触发指针, int 技能代码, int 技能伤害, int x, int y, int z, int 大小);
VOID 透明Call(__int64 对象指针);
VOID 评分Call(int Value);

VOID 区域Call(int 地图编号);
VOID 坐标Call(int 对象横轴, int 对象纵轴, int 对象竖轴);
int 顺图Call(int 顺图方向);

__int64 取人物指针Call(__int64 globleRwAddr);
__int64 取人物基质();
