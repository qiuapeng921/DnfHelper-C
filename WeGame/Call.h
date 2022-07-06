#pragma once

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