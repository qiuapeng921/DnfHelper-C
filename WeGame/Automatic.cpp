#include "pch.h"

#include <thread>
#include "Automatic.h"
#include "Common.h"


VOID Automatic::AutomaticSwitch() {
	MessageBoxW(NULL, L"Automatic线程", L"Automatic", MB_OK);
}

VOID Automatic::AutomaticThread() {
	while (true)
	{
		Sleep(1000);
		MessageBoxW(NULL, L"Automatic线程", L"Automatic", MB_OK);
	}
}

VOID Automatic::进入城镇() {
}

VOID Automatic::城镇处理() {
}

VOID Automatic::进入选图() {
}

VOID Automatic::返回角色() {
}

VOID Automatic::进入副本() {
}

VOID Automatic::模拟顺图() {
}

VOID Automatic::退出副本() {
}