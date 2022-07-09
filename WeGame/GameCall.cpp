#include "pch.h"
#include "GameCall.h"
#include "ReadWrite.h"
#include "GameBulletin.h"
#include "Common.h"
#include "GetGameData.h"
#include "GamePackage.h"

VOID 技能Call(__int64 触发指针, int 技能代码, int 技能伤害, int x, int y, int z, int 大小) {
	__int64 空白地址 = 全局空白 + 1200;
	int 技能大小 = 1;
	_WriteLong(空白地址, 触发指针);
	_WriteInt(空白地址 + 16, 技能代码);
	_WriteLong(空白地址 + 20, 技能伤害);
	_WriteInt(空白地址 + 32, x);
	_WriteInt(空白地址 + 36, y);
	_WriteInt(空白地址 + 40, z);
	_WriteInt(空白地址 + 140, 技能大小);
	_WriteInt(空白地址 + 144, 65535);
	_WriteInt(空白地址 + 148, 65535);

	ByteArr shellCode = { 72, 129, 236, 0, 2, 0, 0 };
	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 185 });
	shellCode = _AppendToBytes(shellCode, _IntToBytes(空白地址, 8));

	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 184 });
	shellCode = _AppendToBytes(shellCode, _IntToBytes(技能CALL, 8));

	shellCode = _AppendToBytes(shellCode, ByteArr{ 255, 208, 72, 129, 196, 0, 2, 0, 0 });

	汇编执行(shellCode);
	shellCode.clear();
}

VOID  透明Call(__int64 对象指针)
{
	ByteArr shellCode = { 72, 129, 236, 0, 2, 0, 0 };
	shellCode = _AppendToBytes(shellCode, ByteArr{ 65, 191, 255, 255, 255, 255 });
	shellCode = _AppendToBytes(shellCode, ByteArr{ 199, 68, 36, 32, 255, 255, 0, 0 });
	shellCode = _AppendToBytes(shellCode, ByteArr{ 65, 185, 1, 0, 0, 0 });
	shellCode = _AppendToBytes(shellCode, ByteArr{ 73, 184, 1, 0, 0, 0, 0, 0, 0, 0 });
	shellCode = _AppendToBytes(shellCode, ByteArr{ 186, 1, 0, 0, 0 });

	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 185 });
	shellCode = _AppendToBytes(shellCode, _IntToBytes(对象指针, 8));

	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 184 });
	shellCode = _AppendToBytes(shellCode, _IntToBytes(透明CALL, 8));

	shellCode = _AppendToBytes(shellCode, ByteArr{ 255, 208, 72, 129, 196, 0, 2, 0, 0 });
	汇编执行(shellCode);
	shellCode.clear();
}

VOID 评分Call(int Value)
{
	加密(_ReadLong(评分基址) + 272, Value);
}

VOID 过图Call(int 方向)
{

}

__int64 取人物指针Call(__int64 globleRwAddr)
{
	__int64 空白地址 = globleRwAddr;

	ByteArr shellCode = ByteArr{ 72, 131, 236, 100 };  // sub rsp,100

	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 184 });  // mov rax  人物call
	shellCode = _AppendToBytes(shellCode, _IntToBytes(人物CALL, 8));

	shellCode = _AppendToBytes(shellCode, ByteArr{ 255, 208 });  // CALL rax

	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 163 });
	shellCode = _AppendToBytes(shellCode, _IntToBytes(空白地址, 8));

	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 131, 196, 100 });  // add rsp,100
	汇编执行(shellCode);
	__int64 返回地址 = _ReadLong(空白地址);

	return 返回地址;
}

static __int64 personAddr;
static __int64 personPointer;

VOID SetPerson(__int64 pAddr, __int64 pPointer)
{
	personAddr = pAddr;
	personPointer = pPointer;
}

__int64 GetPersonAddr()
{
	return personAddr;
}

__int64 GetPersonPointer()
{
	return personPointer;
}

VOID 取人物指针线程()
{
	static bool 状态变化;
	static __int64 空白地址;

	while (_ReadInt(5368709120) == 9460301)
	{
		if (_ReadLong(游戏状态) >= 1 && 状态变化 == false)
		{
			空白地址 = 全局空白 + 4000;
			__int64 人物指针 = 取人物指针Call(空白地址);
			SetPerson(空白地址, 人物指针);
			// 固定人物指针到此地址,方便后面读人物基址时用
			_WriteLong(空白地址, 人物指针);
			状态变化 = true;
		}
		if (_ReadLong(游戏状态) == 0)
		{
			状态变化 = false;
		}
		Sleep(300);
	}
}

VOID 区域Call(int 地图编号)
{
	__int64 局_区域基址 = _ReadLong(区域参数);
	__int64 局_区域CALL = 区域CALL;

	ByteArr shellCode = { 72, 131, 236, 48 };
	shellCode = _AppendToBytes(shellCode, ByteArr{ 65, 184 });
	shellCode = _AppendToBytes(shellCode, _IntToBytes(地图编号, 4));

	shellCode = _AppendToBytes(shellCode, ByteArr{ 186, 174, 12, 0, 0 });
	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 184, 255, 255, 255, 255, 0, 0, 0, 0 });

	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 185 });
	shellCode = _AppendToBytes(shellCode, _IntToBytes(区域参数, 8));

	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 139, 9 });

	shellCode = _AppendToBytes(shellCode, ByteArr{ 72, 184 });
	shellCode = _AppendToBytes(shellCode, _IntToBytes(局_区域CALL, 8));

	shellCode = _AppendToBytes(shellCode, ByteArr{ 255, 208, 72, 131, 196, 48 });
	汇编执行(shellCode);
	shellCode.clear();

	int 大区域 = _ReadInt(局_区域基址 + 区域偏移 + 0);
	int 小区域 = _ReadInt(局_区域基址 + 区域偏移 + 4);
	int 城镇X = _ReadInt(局_区域基址 + 区域偏移 + 8);
	int 城镇Y = _ReadInt(局_区域基址 + 区域偏移 + 12);
	组包移动(大区域, 小区域, 城镇X, 城镇Y);
}