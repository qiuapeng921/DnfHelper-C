#pragma once
#include "Common.h"

VOID 技能Call(__int64 触发指针, int 技能代码, int 技能伤害, int x, int y, int z, int 大小);
VOID 透明Call(__int64 对象指针);
VOID 评分Call(int Value);
VOID 过图Call(int 方向);

VOID 区域Call(int 地图编号);

VOID SetPerson(__int64 pAddr, __int64 pPointer);
__int64 GetPersonAddr();
__int64 GetPersonPointer();
__int64 取人物指针Call(__int64 globleRwAddr);
VOID 取人物指针线程();

