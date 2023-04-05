#include "组包.h"
#include "读写.h"
#include "Call.h"
#include "公用.h"
#include "基址.h"

static vector<BYTE> packData;


VOID 缓冲Call(_int64 缓冲参数)
{
	packData = 字节集追加(packData, { { 72, 129, 236, 0, 1, 0, 0 } });
	packData = 字节集追加(packData, { { 72, 185 }, IntToByteArr(发包基址,8) });
	packData = 字节集追加(packData, { { 186 }, IntToByteArr(缓冲参数,8) });
	packData = 字节集追加(packData, { {72, 184 }, IntToByteArr(缓冲CALL,8) });
	packData = 字节集追加(packData, { { 255, 208 } });
	packData = 字节集追加(packData, { {72, 129, 196, 0, 1, 0, 0 } });
}
VOID 加密Call(__int64 加密参数, int  加密长度)
{
	packData = 字节集追加(packData, { { 72, 129, 236, 0, 1, 0, 0 } });
	packData = 字节集追加(packData, { { 72, 185 }, IntToByteArr(发包基址,8) });
	packData = 字节集追加(packData, { {72, 186 }, IntToByteArr(加密参数,8) });
	switch (加密长度)
	{
	case 1:
		packData = 字节集追加(packData, { { 72, 184 }, IntToByteArr(加密包CALL,8) });
		break;
	case 2:
		packData = 字节集追加(packData, { { 72, 184 }, IntToByteArr(加密包CALL2,8) });
		break;
	case 4:
		packData = 字节集追加(packData, { {72, 184 }, IntToByteArr(加密包CALL4,8) });
		break;
	case 8:
		packData = 字节集追加(packData, { {72, 184 }, IntToByteArr(加密包CALL8,8) });
		break;
	}
	packData = 字节集追加(packData, { { 255, 208 } });
	packData = 字节集追加(packData, { { 72, 129, 196, 0, 1, 0, 0 } });
}


VOID 发包Call()
{
	packData = 字节集追加(packData, { { 72, 129, 236, 0, 1, 0, 0 } });
	packData = 字节集追加(packData, { {72, 184 }, IntToByteArr(发包CALL,8) });
	packData = 字节集追加(packData, { { 255, 208 } });
	packData = 字节集追加(packData, { {72, 129, 196, 0, 1, 0, 0 } });
	汇编执行(packData);
	packData.clear();
}


VOID 提交任务(int id)
{
	缓冲Call(34);
	加密Call(34, 2);
	加密Call(id, 2);
	加密Call(-1, 2);
	加密Call(1, 2);
	加密Call(-1, 2);
	发包Call();
}
VOID 接取任务(int id)
{
	缓冲Call(31);
	加密Call(31, 2);
	加密Call(id, 2);
	发包Call();
}
VOID 放弃任务(int id)
{
	缓冲Call(32);
	加密Call(32, 2);
	加密Call(id, 2);
	发包Call();

}
VOID 完成任务(int id, int type)
{
	type = 1;
	缓冲Call(33);
	加密Call(33, 2);
	加密Call(id, 2);
	if (type == 1) {
		加密Call(16, 1);
	}
	if (type == 2) {
		加密Call(32, 1);
	}
	if (type == 3) {
		加密Call(64, 1);
	}
	加密Call(0, 1);
	加密Call(0, 1);
	发包Call();

}
VOID 组包_提炼(int 提取器位置, int 装备位置)
{
	缓冲Call(408);
	加密Call(2, 1);
	加密Call(提取器位置, 2);
	加密Call(0, 1);
	加密Call(装备位置, 2);
	发包Call();
}
void 组包整理()
{
	缓冲Call(20);
	加密Call(6, 4);
	加密Call(16, 1);
	加密Call(0, 1);
	加密Call(24, 1);
	加密Call(1, 1);
	加密Call(32, 1);
	加密Call(0, 1);
	发包Call();
}
VOID 组包跳过()
{
	缓冲Call(1449);
	发包Call();
}


// 位置 0角色1 位置1角
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

VOID 组包_卖物(int 装备位置)
{
	缓冲Call(22);
	加密Call(317, 4);
	加密Call(95, 4);
	加密Call(1, 1);
	加密Call(0, 1);
	加密Call(装备位置, 2);
	加密Call(1, 4);
	加密Call(23, 4);
	发包Call();
}

VOID 组包拾取(ULONG64 物品地址)
{
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
	加密Call(小地图ID, 4);
	加密Call(城镇X坐标, 2);
	加密Call(城镇Y坐标, 2);
	加密Call(5, 1);
	加密Call(38, 4);
	加密Call(1, 2);
	加密Call(0, 4);
	加密Call(0, 1);
	发包Call();
}