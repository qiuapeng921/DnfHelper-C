#include "Call.h"
#include "读写.h"
#include "公用.h"
#include "判断.h"
#include "组包.h"
#include "基址.h"


void 汇编执行(vector<BYTE> 汇编代码)
{
	INT64 static 局_空白地址;
	if (局_空白地址 == 0)
	{
		局_空白地址 = (INT64)申请内存64(1024);
	}
	INT64 汇编中转 = 局_空白地址 + 300;
	INT64 空白地址 = 局_空白地址 + 500;
	INT64 判断地址 = 空白地址 - 100;
	static BOOL 异步执行;
	if (异步执行) {
		return;
	}
	异步执行 = TRUE;

	INT64 Hook汇编 = 汇编CALL;
	Hook汇编 = Hook汇编 + 144;
	INT64 Hook跳回 = Hook汇编 + 19;
	vector<BYTE> Hook数据 = 读字节数组(Hook汇编, 19);
	vector<BYTE> Hook原数据 = Hook数据;

	Hook数据 = 字节集追加(Hook数据, { { 72, 184 } });
	Hook数据 = 字节集追加(Hook数据, { IntToByteArr(判断地址,8) });

	Hook数据 = 字节集追加(Hook数据, { { 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 } });

	Hook数据 = 字节集追加(Hook数据, { { 72, 187 } });
	Hook数据 = 字节集追加(Hook数据, { IntToByteArr(空白地址,8) });

	Hook数据 = 字节集追加(Hook数据, { { 255, 211 } });

	Hook数据 = 字节集追加(Hook数据, { { 72, 184 } });
	Hook数据 = 字节集追加(Hook数据, { IntToByteArr(判断地址,8) });

	Hook数据 = 字节集追加(Hook数据, { { 199, 0, 3, 0, 0, 0 } });
	Hook数据 = 字节集追加(Hook数据, { { 72, 129, 196, 0, 3, 0, 0 } });

	Hook数据 = 字节集追加(Hook数据, { { 255, 37, 0, 0, 0, 0 } });
	Hook数据 = 字节集追加(Hook数据, { IntToByteArr(Hook跳回,8) });

	if (读长整数型(汇编中转) == 0) {
		写字节数组(汇编中转, Hook数据);
	}
	Hook数据.clear();

	写字节数组(空白地址, 字节集追加(汇编代码, { { 195 } }));
	vector<byte> tmp = { 255, 37, 0, 0, 0, 0 };
	tmp = 字节集追加(tmp, { IntToByteArr(汇编中转,8) });
	tmp = 字节集追加(tmp, { { 144, 144, 144, 144, 144 } });
	写字节数组(Hook汇编, tmp);
	写长整数型(判断地址, 1);
	while (读长整数型(判断地址) == 1)
	{
		Sleep(10);
	}
	写字节数组(Hook汇编, Hook原数据);
	写字节数组(空白地址, MakeByteArr(sizeof(汇编代码) + 16));

	异步执行 = false;
}

void 技能Call(INT64 触发指针, int 技能代码, int 技能伤害, int x, int y, int z, float 大小) {
	INT64 static 局_空白地址;
	if (局_空白地址 == 0)
	{
		局_空白地址 = (INT64)申请内存64(1024);
	}
	INT64 空白地址 = 局_空白地址;
	写长整数型(空白地址, 触发指针);
	写整数型(空白地址 + 16, 技能代码);
	写长整数型(空白地址 + 20, 技能伤害);
	写整数型(空白地址 + 32, x);
	写整数型(空白地址 + 36, y);
	写整数型(空白地址 + 40, z);
	写整数型(空白地址 + 140, (int)大小);
	写整数型(空白地址 + 144, 65535);
	写整数型(空白地址 + 148, 65535);
	vector<byte> shellCode = { 72, 129, 236, 0, 2, 0, 0 };
	shellCode = 字节集追加(shellCode, { { 72, 185 },IntToByteArr(空白地址,8) });
	shellCode = 字节集追加(shellCode, { { 72, 184 },IntToByteArr(技能CALL,8) });
	shellCode = 字节集追加(shellCode, { { 255, 208, 72, 129, 196, 0, 2, 0, 0 } });
	汇编执行(shellCode);
	shellCode.clear();
}

void  透明Call(INT64 对象指针)
{
	vector<byte> shellCode = { 72, 129, 236, 0, 2, 0, 0 };
	shellCode = 字节集追加(shellCode, { { 65, 191, 255, 255, 255, 255 } });
	shellCode = 字节集追加(shellCode, { { 199, 68, 36, 32, 255, 255, 0, 0} });
	shellCode = 字节集追加(shellCode, { { 65, 185, 1, 0, 0, 0 } });
	shellCode = 字节集追加(shellCode, { {73, 184, 1, 0, 0, 0, 0, 0, 0, 0 } });
	shellCode = 字节集追加(shellCode, { {186, 1, 0, 0, 0 } });
	shellCode = 字节集追加(shellCode, { { 72, 185 }, IntToByteArr(对象指针,8) });
	shellCode = 字节集追加(shellCode, { { 72, 184 }, IntToByteArr(透明CALL,8) });
	shellCode = 字节集追加(shellCode, { {255, 208, 72, 129, 196, 0, 2, 0, 0 } });
	汇编执行(shellCode);
	shellCode.clear();
}

INT64 取人物指针Call(INT64 空白地址)
{
	vector<byte> shellCode = { 72, 131, 236, 100 };
	shellCode = 字节集追加(shellCode, { { 72, 184 } });
	shellCode = 字节集追加(shellCode, { IntToByteArr(人物CALL,8) });
	shellCode = 字节集追加(shellCode, { { 255, 208 } });
	shellCode = 字节集追加(shellCode, { {72, 163 } });
	shellCode = 字节集追加(shellCode, { IntToByteArr(空白地址,8) });
	shellCode = 字节集追加(shellCode, { { 72, 131, 196, 100 } });
	汇编执行(shellCode);
	INT64 返回地址 = 读长整数型(空白地址);
	return 返回地址;
}

INT64 取人物基质() {
	INT64 static 局_空白地址;
	if (局_空白地址 == 0)
	{
		局_空白地址 = (INT64)申请内存64(1024);
	}
	INT64 空白地址 = 局_空白地址;
	INT64 人物指针 = 取人物指针Call(空白地址);
	return 空白地址;
}

void 区域Call(int 地图编号)
{
	INT64 局_区域基址 = 读长整数型(区域参数);
	INT64 局_区域CALL = 区域CALL;

	vector<byte> shellCode = { 72, 131, 236, 48 };
	shellCode = 字节集追加(shellCode, { { 65, 184 }, IntToByteArr(地图编号,8) });
	shellCode = 字节集追加(shellCode, { {186, 174, 12, 0, 0 } });
	shellCode = 字节集追加(shellCode, { {72, 184, 255, 255, 255, 255, 0, 0, 0, 0 } });
	shellCode = 字节集追加(shellCode, { { 72, 185 }, IntToByteArr(区域参数,8) });
	shellCode = 字节集追加(shellCode, { {72, 139, 9 } });
	shellCode = 字节集追加(shellCode, { { 72, 184 }, IntToByteArr(局_区域CALL,8) });
	shellCode = 字节集追加(shellCode, { {255, 208, 72, 131, 196, 48 } });
	汇编执行(shellCode);
	shellCode.clear();

	int 大区域 = 读整数型(局_区域基址 + 区域偏移 + 0);
	int 小区域 = 读整数型(局_区域基址 + 区域偏移 + 4);
	int 城镇X = 读整数型(局_区域基址 + 区域偏移 + 8);
	int 城镇Y = 读整数型(局_区域基址 + 区域偏移 + 12);
	组包移动(大区域, 小区域, 城镇X, 城镇Y);
}

void 坐标Call(INT32 对象横轴, INT32 对象纵轴, INT32 对象竖轴)
{
	INT64 触发指针 = 读长整数型(取人物基质());
	if (触发指针 < 1) return;

	vector<byte> 汇编数据 = { 72, 129, 236, 0, 1, 0, 0 };
	汇编数据 = 字节集追加(汇编数据, { { 65, 185 }, IntToByteArr(对象竖轴,4) });
	汇编数据 = 字节集追加(汇编数据, { { 65, 184 }, IntToByteArr(对象纵轴,4) });
	汇编数据 = 字节集追加(汇编数据, { { 186 }, IntToByteArr(对象横轴,4) });
	汇编数据 = 字节集追加(汇编数据, { { 72, 185 }, IntToByteArr(触发指针,8) });
	汇编数据 = 字节集追加(汇编数据, { {72, 139, 1 } });
	汇编数据 = 字节集追加(汇编数据, { { 255, 144 }, IntToByteArr(坐标CALL偏移,8) });
	汇编数据 = 字节集追加(汇编数据, { {72, 129, 196, 0, 1, 0, 0 } });
	汇编执行(汇编数据);
	汇编数据.clear();
}

void 漂移Call(int X, int Y, int Z, int 速度)
{
	INT64 指针 = 读长整数型(人物基址);

	vector<BYTE> shellCode = { 72, 129, 236, 0, 8, 0, 0 };
	shellCode = 字节集追加(shellCode, { { 185, 241, 0, 0, 0 } });
	shellCode = 字节集追加(shellCode, { { 72, 184 }, IntToByteArr(申请内存,8) });
	shellCode = 字节集追加(shellCode, { {255, 208, 72, 139, 240, 72, 139, 200 } });
	shellCode = 字节集追加(shellCode, { { 72,184 }, IntToByteArr(漂移CALL,8) });
	shellCode = 字节集追加(shellCode, { { 255, 208, 185 }, IntToByteArr(X,8) });
	shellCode = 字节集追加(shellCode, { {137, 8, 185 }, IntToByteArr(Y,8) });
	shellCode = 字节集追加(shellCode, { {137, 72, 4, 185 }, IntToByteArr(Z,8) });
	shellCode = 字节集追加(shellCode, { {137, 72, 8, 72, 141, 72, 24, 186 }, IntToByteArr(速度,8) });
	shellCode = 字节集追加(shellCode, { {72, 184 }, IntToByteArr(漂移CALL2,8) });
	shellCode = 字节集追加(shellCode, { {255, 208 } });
	shellCode = 字节集追加(shellCode, { {72, 141, 84, 36, 112, 49, 219, 72, 137, 92, 36, 112, 72, 137, 92, 36, 120, 49, 210, 72, 141, 76, 36, 112 } });
	shellCode = 字节集追加(shellCode, { {72, 184 }, IntToByteArr(写入内存,8) });
	shellCode = 字节集追加(shellCode, { {255, 208, 72, 139, 206, 72, 139, 1 } });
	shellCode = 字节集追加(shellCode, { {72,186 }, IntToByteArr(指针,8) });
	shellCode = 字节集追加(shellCode, { {72, 49, 219, 73, 189, 255, 255, 255, 255, 255, 255, 255, 255 } });
	shellCode = 字节集追加(shellCode, { {137, 92, 36, 64, 72, 137, 92, 36, 56, 68, 137, 108, 36, 48 } });
	shellCode = 字节集追加(shellCode, { {199, 68, 36, 40, 232, 2, 0, 0 } });
	shellCode = 字节集追加(shellCode, { {72, 141, 124, 36, 112, 72, 137, 124, 36, 32, 69, 51, 201 } });
	shellCode = 字节集追加(shellCode, { {73,184 }, IntToByteArr(指针,8) });
	shellCode = 字节集追加(shellCode, { {255, 144 }, IntToByteArr(312,8) });
	shellCode = 字节集追加(shellCode, { {72, 129, 196, 0, 8, 0, 0 } });
	汇编执行(shellCode);
	shellCode.clear();
}