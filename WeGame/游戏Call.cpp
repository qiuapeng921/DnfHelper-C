#include "pch.h"
#include "游戏Call.h"

#include "读写.h"
#include "公用.h"
#include "判断.h"
#include "组包.h"

VOID 汇编执行(ByteArr 汇编代码)
{
	__int64 static 局_空白地址;
	if (局_空白地址 == 0)
	{
		局_空白地址 = (__int64)_ApplyMemory(1024);
	}
	__int64 汇编中转 = 局_空白地址 + 300;
	__int64 空白地址 = 局_空白地址 + 500;
	__int64 判断地址 = 空白地址 - 100;
	static bool 异步执行;
	if (异步执行) {
		return;
	}
	异步执行 = true;

	__int64 Hook汇编 = 汇编CALL;
	Hook汇编 = Hook汇编 + 144;
	__int64 Hook跳回 = Hook汇编 + 19;
	ByteArr Hook数据 = _ReadByteArr(Hook汇编, 19);
	ByteArr Hook原数据 = Hook数据;

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 184 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(判断地址, 8));

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 131, 56, 1, 117, 42, 72, 129, 236, 0, 3, 0, 0 });

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 187 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(空白地址, 8));

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 255, 211 });

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 184 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(判断地址, 8));

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 199, 0, 3, 0, 0, 0 });
	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 129, 196, 0, 3, 0, 0 });

	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 255, 37, 0, 0, 0, 0 });
	Hook数据 = _AppendToBytes(Hook数据, _IntToBytes(Hook跳回, 8));

	if (_ReadLong(汇编中转) == 0) {
		_WriteByteArr(汇编中转, Hook数据);
	}
	Hook数据.clear();

	_WriteByteArr(空白地址, _AppendToBytes(汇编代码, ByteArr{ 195 }));
	ByteArr tmp = { 255, 37, 0, 0, 0, 0 };
	tmp = _AppendToBytes(tmp, _IntToBytes(汇编中转, 8));
	tmp = _AppendToBytes(tmp, ByteArr{ 144, 144, 144, 144, 144 });
	_WriteByteArr(Hook汇编, tmp);
	_WriteLong(判断地址, 1);
	while (_ReadLong(判断地址) == 1)
	{
		Sleep(10);
	}
	_WriteByteArr(Hook汇编, Hook原数据);
	_WriteByteArr(空白地址, 取空白ByteArr(sizeof(汇编代码) + 16));

	异步执行 = false;
}


VOID 技能Call(__int64 触发指针, int 技能代码, int 技能伤害, int x, int y, int z, int 大小) {
	__int64 static 局_空白地址;
	if (局_空白地址 == 0)
	{
		局_空白地址 = (__int64)_ApplyMemory(1024);
	}
	__int64 空白地址 = 局_空白地址;
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
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 72, 185 }, _IntToBytes(空白地址, 8)));
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 72, 184 }, _IntToBytes(技能CALL, 8)));
	shellCode = _AppendToBytes(shellCode, { 255, 208, 72, 129, 196, 0, 2, 0, 0 });
	汇编执行(shellCode);
	shellCode.clear();
}

VOID  透明Call(__int64 对象指针)
{
	ByteArr shellCode = { 72, 129, 236, 0, 2, 0, 0 };
	shellCode = _AppendToBytes(shellCode, { 65, 191, 255, 255, 255, 255 });
	shellCode = _AppendToBytes(shellCode, { 199, 68, 36, 32, 255, 255, 0, 0 });
	shellCode = _AppendToBytes(shellCode, { 65, 185, 1, 0, 0, 0 });
	shellCode = _AppendToBytes(shellCode, { 73, 184, 1, 0, 0, 0, 0, 0, 0, 0 });
	shellCode = _AppendToBytes(shellCode, { 186, 1, 0, 0, 0 });
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 72, 185 }, _IntToBytes(对象指针, 8)));
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 72, 184 }, _IntToBytes(透明CALL, 8)));
	shellCode = _AppendToBytes(shellCode, { 255, 208, 72, 129, 196, 0, 2, 0, 0 });
	汇编执行(shellCode);
	shellCode.clear();
}

VOID 评分Call(int Value)
{
	加密(_ReadLong(评分基址) + 加密评分, Value);
}

__int64 取人物指针Call(__int64 空白地址)
{
	ByteArr shellCode = { 72, 131, 236, 100 };  // sub rsp,100

	shellCode = _AppendToBytes(shellCode, { 72, 184 });  // mov rax  人物call
	shellCode = _AppendToBytes(shellCode, _IntToBytes(人物CALL, 8));

	shellCode = _AppendToBytes(shellCode, { 255, 208 });  // CALL rax

	shellCode = _AppendToBytes(shellCode, { 72, 163 });
	shellCode = _AppendToBytes(shellCode, _IntToBytes(空白地址, 8));

	shellCode = _AppendToBytes(shellCode, { 72, 131, 196, 100 });  // add rsp,100
	汇编执行(shellCode);
	__int64 返回地址 = _ReadLong(空白地址);
	return 返回地址;
}

__int64 取人物基质() {
	__int64 static 局_空白地址;
	if (局_空白地址 == 0)
	{
		局_空白地址 = (__int64)_ApplyMemory(1024);
	}
	__int64 空白地址 = 局_空白地址;
	__int64 人物指针 = 取人物指针Call(空白地址);
	return 空白地址;
}

VOID 区域Call(int 地图编号)
{
	__int64 局_区域基址 = _ReadLong(区域参数);
	__int64 局_区域CALL = 区域CALL;

	ByteArr shellCode = { 72, 131, 236, 48 };
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 65, 184 }, _IntToBytes(地图编号, 4)));
	shellCode = _AppendToBytes(shellCode, { 186, 174, 12, 0, 0 });
	shellCode = _AppendToBytes(shellCode, { 72, 184, 255, 255, 255, 255, 0, 0, 0, 0 });
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 72, 185 }, _IntToBytes(区域参数, 8)));
	shellCode = _AppendToBytes(shellCode, { 72, 139, 9 });
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 72, 184 }, _IntToBytes(局_区域CALL, 8)));
	shellCode = _AppendToBytes(shellCode, { 255, 208, 72, 131, 196, 48 });
	汇编执行(shellCode);
	shellCode.clear();

	int 大区域 = _ReadInt(局_区域基址 + 区域偏移 + 0);
	int 小区域 = _ReadInt(局_区域基址 + 区域偏移 + 4);
	int 城镇X = _ReadInt(局_区域基址 + 区域偏移 + 8);
	int 城镇Y = _ReadInt(局_区域基址 + 区域偏移 + 12);
	组包移动(大区域, 小区域, 城镇X, 城镇Y);
}

VOID 坐标Call(int 对象横轴, int 对象纵轴, int 对象竖轴)
{
	__int64 触发指针 = _ReadLong(取人物基质());
	if (触发指针 < 1) return;

	ByteArr 汇编数据 = { 72, 129, 236, 0, 1, 0, 0 };
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes({ 65, 185 }, _IntToBytes(对象竖轴, 4)));
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes({ 65, 184 }, _IntToBytes(对象纵轴, 4)));
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes({ 186 }, _IntToBytes(对象横轴, 4)));
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes({ 72, 185 }, _IntToBytes(触发指针, 8)));
	汇编数据 = _AppendToBytes(汇编数据, { 72, 139, 1 });
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes({ 255, 144 }, _IntToBytes(坐标CALL偏移, 8)));
	汇编数据 = _AppendToBytes(汇编数据, { 72, 129, 196, 0, 1, 0, 0 });
	汇编执行(汇编数据);
	汇编数据.clear();
}

VOID 漂移Call(_int64 触发指针, int 对象横轴, int 对象纵轴, int 对象竖轴, int 速度)
{

}

int 顺图Call(int 顺图方向)
{
	__int64 static 局_空白地址;
	if (局_空白地址 == 0)
	{
		局_空白地址 = (__int64)_ApplyMemory(1024);
	}
	__int64 空白地址 = 局_空白地址;
	__int64 房间数据 = _ReadLong(_ReadLong(_ReadLong(房间编号) + 时间基址) + 顺图偏移);
	ByteArr shellCode = { 72, 129, 236, 0, 1, 0, 0 };
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 72, 185 }, _IntToBytes(房间数据, 8)));
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 186 }, _IntToBytes(顺图方向, 4)));
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 72, 184 }, _IntToBytes(坐标顺图CALL, 8)));
	shellCode = _AppendToBytes(shellCode, { 255, 208 });
	shellCode = _AppendToBytes(shellCode, _AppendToBytes({ 72, 163 }, _IntToBytes(空白地址, 8)));
	shellCode = _AppendToBytes(shellCode, { 72, 129, 196, 0, 1, 0, 0 });
	汇编执行(shellCode);
	shellCode.clear();
	return _ReadInt(空白地址);
}