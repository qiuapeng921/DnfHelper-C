#include "pch.h"
#include "GameBulletin.h"
#include "ReadWrite.h"
#include "Common.h"
#include "Address.h"


VOID SystemMessage(CString message) {
	LPVOID static 空白地址;

	if (空白地址 == 0)
	{
		空白地址 = _ApplyMemory(400);
	}
}

VOID Message(CString message,int type) {
	__int64 公告基址, 公告CALL_1, 空白地址1, 空白地址2;
	ByteArr 汇编数据;
	公告基址 = 公告参数;
	公告CALL_1 = 公告CALL;
	空白地址1 = 全局空白 + 800;
	空白地址2 = 全局空白 + 1000;

	//_WriteByteArr(空白地址2, _AppendToBytes(文本到字节集(公告内容), ByteArr{ 0, 0 }));
	_WriteLong(空白地址1 + 8, 空白地址2);
	_WriteLong(空白地址1 + 24, 0);
	_WriteLong(空白地址1 + 32, RGB(255, 80, 128)); // 桃红色
	_WriteLong(空白地址1 + 36, 38);  // 公告类型 17系统公告 38普通公告
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 129, 236, 0, 1, 0, 0 });
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes(ByteArr(72, 186), _IntToBytes(空白地址1,8)));
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes(ByteArr(72, 190), _IntToBytes(公告基址,8)));
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 139, 54 });
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 137, 241 });
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 191, 255, 255, 255, 255 });
	汇编数据 = _AppendToBytes(汇编数据, _AppendToBytes(ByteArr(72, 184), _IntToBytes(公告CALL_1,8)));
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 255, 208 });
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 129, 196, 0, 1, 0, 0 });
	//汇编执行(汇编数据);
}