#include "日志.h"
#include "公用.h"

HELE	editContent;


VOID 设置日志句柄(HELE hele) {
	editContent = hele;
}

VOID 日志输出(const wchar_t* message) {
	XEdit_AddTextUser(editContent, message);
}