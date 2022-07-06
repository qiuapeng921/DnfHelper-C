#include "pch.h"

#include <thread>
#include "自动.h"
#include "公用.h"


VOID 自动::自动开关() {
	MessageBoxW(NULL, L"自动线程", L"自动", MB_OK);
}


VOID 自动::自动线程() {
	while (true)
	{
		Sleep(1000);
		MessageBoxW(NULL, L"自动线程", L"自动", MB_OK);
	}
}

VOID 自动::进入城镇() {
}

VOID 自动::城镇处理() {
}

VOID 自动::进入选图() {
}

VOID 自动::返回角色() {
}

VOID 自动::进入副本() {
}

VOID 自动::模拟顺图() {
}

VOID 自动::退出副本() {
}