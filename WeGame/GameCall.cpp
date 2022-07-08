#include "pch.h"
#include "GameCall.h"
#include "ReadWrite.h"
#include "Common.h"
#include "Address.h"

VOID  Call::物品Call(INT64 物品代码)
{

}

VOID  Call::特效Call(INT type)
{

}

VOID  Call::透明Call(INT64 对象指针)
{

}


VOID Call::奔跑Call(INT x, INT y, INT Speed)
{

}

VOID Call::释放Call(INT64 触发指针, INT 技能代码, INT 技能伤害, INT x, INT y, INT z)
{

}

VOID Call::评分Call(INT Value)
{

}

VOID Call::过图Call(INT 方向)
{

}


INT64 申请属性内存Call(INT 属性类型)
{
	return 0;
}

VOID 写入光环范围Call(INT64 光环指针, INT 范围数值, INT x, INT y)
{

}

VOID 生效属性内存Call(INT64 人物指针, INT64 光环指针)
{

}

ByteArr 取空白ByteArr(int num) {
	ByteArr res;
	for (size_t i = 0; i < num; i++)
	{
		res.push_back(0);
	}
	return res;
}

VOID 汇编执行(vector<byte> 汇编代码) {
	__int64 汇编中转, 空白地址, Hook汇编, Hook跳回, 判断地址;

	static bool 异步执行;

	汇编中转 = 全局空白 + 300;
	空白地址 = 全局空白 + 500;
	判断地址 = 空白地址 - 100;
	if (异步执行) {
		return;
	}

	异步执行 = true;

	Hook汇编 = 汇编CALL;
	Hook汇编 = Hook汇编 + 144;
	Hook跳回 = Hook汇编 + 19;
	ByteArr Hook数据 = _ReadByteArr(Hook汇编, 19);
	ByteArr Hook原数据 = Hook数据;


	Hook数据 = _AppendToBytes(Hook数据, ByteArr{ 72, 184 }),
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

	_WriteByteArr(空白地址, _AppendToBytes(汇编代码, ByteArr{ 195 }));
	_WriteByteArr(Hook汇编, _AppendToBytes(_AppendToBytes(ByteArr{ 255, 37, 0, 0, 0, 0 }, _IntToBytes(汇编中转, 8)), ByteArr{ 144, 144, 144, 144, 144 }));
	_WriteLong(判断地址, 1);
	while (_ReadLong(判断地址) == 1)
	{
		Sleep(10);
	}

	_WriteByteArr(Hook汇编, Hook原数据);
	_WriteByteArr(空白地址, 取空白ByteArr(sizeof(汇编代码) + 16));
	异步执行 = false;
}


__int64 取人物指针Call()
{
	ByteArr 汇编数据;
	__int64 空白地址, 返回地址;

	空白地址 = 全局空白3 + 4000;
	汇编数据 = ByteArr{ 72, 129, 236, 0, 1, 0, 0 };  // sub rsp,100
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes(ByteArr{ 72, 184 }, _IntToBytes(人物CALL, 8)));  // mov rax  人物call
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 255, 208 });  // CALL rax
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes(ByteArr{ 72, 163 }, _IntToBytes(空白地址, 8)));
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 129, 196, 0, 1, 0, 0 });  // add rsp,100
	汇编执行(汇编数据);
	返回地址 = _ReadLong(空白地址);
	return 返回地址;
}
