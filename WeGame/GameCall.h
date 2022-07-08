#pragma once
#include "Common.h"

class Call
{
public:
	VOID 技能CALL(INT64 触发指针, INT 技能代码, INT 技能伤害, INT x, INT y, INT z);

	VOID 释放Call(INT64 触发指针, INT 技能代码, INT 技能伤害, INT x, INT y, INT z);

	VOID 物品Call(INT64 物品代码);

	VOID 特效Call(INT type);

	VOID 透明Call(INT64 对象指针);

	VOID 奔跑Call(INT x, INT y, INT Speed);

	VOID 评分Call(INT Value);

	VOID 过图Call(INT 方向);
};

VOID 汇编执行(ByteArr 汇编代码);

__int64 取人物指针Call(__int64 globleRwAddr);

VOID SetPerson(__int64 pAddr, __int64 pPointer);

__int64 GetPersonAddr();

__int64 GetPersonPointer();

VOID 取人物指针线程();