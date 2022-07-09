#include "pch.h"
#include "GamePackage.h"
#include "Common.h"
#include "ReadWrite.h"
#include "GameCall.h"

static ByteArr packData;

VOID 缓冲Call(_int64 缓冲参数)
{
	packData = _AppendToBytes(packData, ByteArr{ 72, 131, 236, 96 });

	packData = _AppendToBytes(packData, ByteArr{ 186 });
	packData = _AppendToBytes(packData, _IntToBytes(缓冲参数, 4));

	packData = _AppendToBytes(packData, ByteArr{ 72, 185 });
	packData = _AppendToBytes(packData, _IntToBytes(发包基址, 8));

	packData = _AppendToBytes(packData, ByteArr{ 72, 139, 9 });

	packData = _AppendToBytes(packData, ByteArr{ 72, 184 });
	packData = _AppendToBytes(packData, _IntToBytes(缓冲CALL, 8));

	packData = _AppendToBytes(packData, ByteArr{ 255, 208 });
}

VOID 加密Call(__int64 加密参数, int  加密长度)
{
	packData = _AppendToBytes(packData, ByteArr{ 73, 199, 192 });
	packData = _AppendToBytes(packData, _IntToBytes(加密长度, 4));

	packData = _AppendToBytes(packData, ByteArr{ 72, 184 });
	packData = _AppendToBytes(packData, _IntToBytes(加密参数, 8));

	packData = _AppendToBytes(packData, ByteArr{ 72, 137, 68, 36, 32 });
	packData = _AppendToBytes(packData, ByteArr{ 72, 141, 84, 36, 32 });

	packData = _AppendToBytes(packData, ByteArr{ 72, 185 });
	packData = _AppendToBytes(packData, _IntToBytes(发包基址, 8));

	packData = _AppendToBytes(packData, ByteArr{ 72, 139, 9 });

	packData = _AppendToBytes(packData, ByteArr{ 72, 184 });
	packData = _AppendToBytes(packData, _IntToBytes(加密CALL, 8));

	packData = _AppendToBytes(packData, ByteArr{ 255, 208 });
}

VOID 发包Call()
{
	packData = _AppendToBytes(packData, ByteArr{ 72, 184 });
	packData = _AppendToBytes(packData, _IntToBytes(发包CALL, 8));

	packData = _AppendToBytes(packData, ByteArr{ 255, 208 });
	packData = _AppendToBytes(packData, ByteArr{ 72, 131, 196, 96 });
	汇编执行(packData);
	packData.clear();
}

// 位置 0角色1 位置1角色2
VOID 组包选择角色(int 位置)
{
	if (位置 < 0) {
		return;
	}
	缓冲Call(4);
	加密Call(位置, 2);
	发包Call();
}

VOID 组包分解(int 装备位置)
{
	if (装备位置 < 0)
	{
		return;
	}
	缓冲Call(26);
	加密Call(0, 1);
	加密Call(65535, 2);
	加密Call(317, 4);
	加密Call(1, 1);
	加密Call(装备位置, 2);
	发包Call();
}

VOID 组包拾取(int 物品地址)
{
	if (物品地址 < 0) {
		return;
	}
	缓冲Call(43);
	加密Call(物品地址, 4);
	加密Call(0, 1);
	加密Call(1, 1);
	加密Call(566, 2);
	加密Call(291, 2);
	加密Call(9961, 2);
	加密Call(553, 2);
	加密Call(285, 2);
	加密Call(18802, 2);
	加密Call(24743, 2);
	发包Call();
}

VOID 组包返回角色()
{
	缓冲Call(7);
	发包Call();
}

VOID 组包选图()
{
	缓冲Call(15);
	加密Call(0, 4);
	发包Call();
}

VOID 组包进图(int 编号, int 难度, int 深渊, int 练习)
{
	缓冲Call(16);
	加密Call(编号, 4);
	加密Call(难度, 1);
	加密Call(0, 2);
	加密Call(深渊, 1);//  ' 0正常 1深渊
	加密Call(练习, 1);//  ' 0正常 1练习
	加密Call(65535, 2);
	加密Call(0, 4);
	加密Call(0, 1);
	加密Call(0, 4);//  ' 任务
	加密Call(0, 1);
	加密Call(0, 4);
	发包Call();
}

VOID 组包翻牌(int 行, int 列)
{
	缓冲Call(69);
	发包Call();
	缓冲Call(70);
	发包Call();
	缓冲Call(71);
	加密Call(行, 1);
	加密Call(列, 1);
	发包Call();
	缓冲Call(1426);
	发包Call();
}

VOID 组包出图()
{
	缓冲Call(42);
	发包Call();
}

VOID 组包过图(int X, int Y)
{
	缓冲Call(45);
	加密Call(X, 1);
	加密Call(Y, 1);
	加密Call(0, 4);
	加密Call(0, 4);
	加密Call(0, 1);
	for (int i = 1; i <= 9; i++)
	{
		加密Call(0, 2);
	}
	for (int i = 1; i <= 8; i++)
	{
		加密Call(0, 4);
	}
	for (int i = 1; i <= 7; i++)
	{
		加密Call(0, 2);
	}
	加密Call(0, 4);
	for (int i = 1; i <= 3; i++)
	{
		加密Call(0, 2);
	}
	for (int i = 1; i <= 3; i++)
	{
		加密Call(0, 4);
	}
	加密Call(0, 2);
	加密Call(0, 1);
	发包Call();
}

VOID 组包移动(int 大地图ID, int 小地图ID, int 城镇X坐标, int 城镇Y坐标)
{
	缓冲Call(36);
	加密Call(大地图ID, 4);
	加密Call(小地图ID, 1);
	加密Call(城镇X坐标, 2);
	加密Call(城镇Y坐标, 2);
	加密Call(5, 1);
	加密Call(38, 4);
	加密Call(2, 2);
	加密Call(0, 4);
	加密Call(0, 1);
	发包Call();
}