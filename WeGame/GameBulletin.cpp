#include "pch.h"
#include "GameBulletin.h"
#include "ReadWrite.h"

VOID 系统公告(CString 公告内容) {
	LPVOID static 空白地址;

	if (空白地址 == 0)
	{
		空白地址 = 申请_内存(400);
	}
}

VOID 神话公告(CString 公告内容) {

}