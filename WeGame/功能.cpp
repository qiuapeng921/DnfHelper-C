﻿#include "pch.h"
#include "公告.h"

#include "公用.h"
#include "读写.h"
#include "游戏Call.h"
#include "公告.h"
#include "遍历.h"

HANDLE 技能开关句柄;

VOID 技能开关() {
	static bool _switch;
	_switch = !_switch;

	if (_switch == true)
	{
		技能开关句柄 = _CreateThread(&全屏技能);
		游戏公告("技能全屏 - 开启", 2);
	}
	else
	{
		_DeleteThread(技能开关句柄);
		游戏公告("技能全屏 - 关闭", 2);
	}
}

VOID 无形秒杀()
{
	技能Call(0, 39002, 0, 0, 0, 0, 0);
	游戏公告("无形秒杀 - 完毕", 2);
}

VOID 武器冰冻() {
	static bool _switch;
	__int64 static 局_空白地址;
	if (局_空白地址 == 0)
	{
		局_空白地址 = (__int64)_ApplyMemory(1024);
	}
	__int64 空白地址 = 局_空白地址;
	int 冰冻伤害 = 99999;
	_switch = !_switch;
	if (_switch == true)
	{
		_WriteInt(空白地址, 0);
		_WriteInt(空白地址 + 4, 2000);
		_WriteInt(空白地址 + 8, 2000);
		_WriteInt(空白地址 + 12, 50);
		_WriteInt(空白地址 + 16, 100);
		_WriteInt(空白地址 + 20, 99);
		_WriteInt(空白地址 + 24, 130);
		_WriteInt(空白地址 + 28, 冰冻伤害 * 100000);
		__int64 武器 = _ReadLong(_ReadLong(取人物基质()) + 武器偏移);
		_WriteLong(武器 + 冰冻开始, 空白地址);
		_WriteLong(武器 + 冰冻结束, 空白地址 + 32);
		游戏公告("武器冰冻 - 启动", 2);
	}
	else
	{
		__int64 武器 = _ReadLong(_ReadLong(取人物基质()) + 武器偏移);
		_WriteLong(武器 + 冰冻开始, 0);
		_WriteLong(武器 + 冰冻结束, 0);

		for (int i = 0; i <= 7; i++)
		{
			_WriteLong(空白地址, 0);
			空白地址 = 空白地址 + 4;
		}
		游戏公告("武器冰冻 - 关闭", 2);
	}
}

VOID HOOK伤害() {
	static bool _switch;
	__int64 倍攻伤害 = 9999999;
	static ByteArr 地址原数据;
	_switch = !_switch;
	if (_switch == true)
	{
		地址原数据 = _ReadByteArr(全局基址, 10);
		ByteArr data = _AppendToBytes(ByteArr{ 72, 190 }, _IntToBytes(倍攻伤害, 8));
		_WriteByteArr(全局基址, data);
		游戏公告("HOOK伤害 - 启动", 2);
	}
	else
	{
		_WriteByteArr(全局基址, 地址原数据);
		游戏公告("HOOK伤害 - 关闭", 2);
	}
}