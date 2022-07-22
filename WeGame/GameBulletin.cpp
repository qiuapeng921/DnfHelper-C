#include "pch.h"
#include "GameBulletin.h"
#include "ReadWrite.h"
#include "Common.h"
#include "GameCall.h"

static CEdit* windowPEdit;

VOID SetWindowPEdit(CEdit* pEdit)
{
	windowPEdit = pEdit;
}

CEdit* GetWindowPEdit() 
{
	return windowPEdit;
}

VOID 监控(CString message)
{
	CString data;
	data = data + "\r\n" + message;
	GetWindowPEdit()->ReplaceSel(data);
}

VOID SystemMessage(string message) {
	
}

VOID Message(string message,int type) {
	__int64 公告基址, 公告CALL_1;
	公告基址 = 公告参数;
	公告CALL_1 = 公告CALL;
	
	static __int64 空白地址1;
	__int64 空白地址2;

	if (空白地址1 == 0)
	{
		空白地址1 = (__int64)_ApplyMemory(500);
	}
	空白地址2 = 空白地址1 + 500;
	_WriteByteArr(空白地址2, _AppendToBytes(AnsiToUnicode("情歌 √  " + message), ByteArr{ 0, 0 }));
	_WriteLong(空白地址1 + 8, 空白地址2);
	_WriteLong(空白地址1 + 24, 0);
	_WriteLong(空白地址1 + 32, RGB(0, 255, 255));
	// 桃红色 RGB(255, 80, 128)
	// 艳青色 RGB(0, 255, 255)
	// 青绿色 RGB(0, 224, 128)
	// 桃红色 RGB(255, 80, 128)

	 // 公告类型 17系统公告 38普通公告
	int 公告类型 = 38;
	if (type == 2)
	{
		公告类型 = 17;
	}
	_WriteLong(空白地址1 + 36, 公告类型); 

	ByteArr 汇编数据 = ByteArr{ 72, 129, 236, 0, 1, 0, 0 };
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 186 });
	汇编数据 = _AppendToBytes(汇编数据, _IntToBytes(空白地址1, 8));

	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 190 });
	汇编数据 = _AppendToBytes(汇编数据, _IntToBytes(公告基址, 8));

	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 139, 54 });
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 137, 241 });
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 191, 255, 255, 255, 255 });

	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 184 });
	汇编数据 = _AppendToBytes(汇编数据, _IntToBytes(公告CALL_1, 8));

	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 255, 208 });
	汇编数据 = _AppendToBytes(汇编数据, ByteArr{ 72, 129, 196, 0, 1, 0, 0 });
	汇编执行(汇编数据);
	汇编数据.clear();
}