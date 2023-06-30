//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "activation.h"
#include "config.h"
#include "notice.h"

void MainThread() {
	RegisterHotKey(nullptr, 0, 0, VK_HOME);
	MSG lpMsg;
	while (GetMessage(&lpMsg, nullptr, 0, 0)) {
		if (WM_HOTKEY == lpMsg.message) {
			if (HIWORD(lpMsg.lParam) == VK_HOME) {
				InitHelper();
				return;
			}
		}
		Sleep(10);
	}
}



void InitHelper() {
	LoadConfigIni();
	if (!ConfigIniExist()) {
		WriteConfigIni();
	}

	ColorfulNotice(L"呼出成功,欢迎使用情歌");

	// 全局.游戏句柄 = GetForegroundWindow();
	// 全局.窗口消息 = (WNDPROC)SetWindowLongPtr(全局.游戏句柄, GWLP_WNDPROC, (ULONG64)窗口进程);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MessageLoopOfAB, nullptr, 0, nullptr);
}


LRESULT CALLBACK WinMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_KEYUP) {
		if (wParam == VK_END) {}
		if (wParam == VK_F1) {}
		if (wParam == VK_F2) {}
		if (wParam == VK_OEM_3) {}
	}
	if (uMsg == WM_SYSKEYDOWN)//按下ALT
	{
		if (wParam == VK_F1) {}
		if (wParam == VK_F2) {}
		if (wParam == VK_F3) {}
		if (wParam == VK_F4) {
			keybd_event(88, MapVirtualKey(88, 0), 0, 0);//按下
			Sleep(50);
			keybd_event(88, MapVirtualKey(88, 0), KEYEVENTF_KEYUP, 0);//松开
		}
		if (wParam == VK_UP) {}
		if (wParam == VK_DOWN) {}
		if (wParam == VK_LEFT) {}
		if (wParam == VK_RIGHT) {}
	}

	return CallWindowProc(nullptr, hWnd, uMsg, wParam, lParam);
}


void MessageLoopOfAB() {
	RegisterHotKey(nullptr, 0, 0, VK_F1);
	RegisterHotKey(nullptr, 0, 0, VK_END);
	RegisterHotKey(nullptr, 0, 0, VK_OEM_3);
	RegisterHotKey(nullptr, 0, MOD_CONTROL, VK_UP);
	RegisterHotKey(nullptr, 0, MOD_CONTROL, VK_DOWN);
	RegisterHotKey(nullptr, 0, MOD_CONTROL, VK_LEFT);
	RegisterHotKey(nullptr, 0, MOD_CONTROL, VK_RIGHT);
	RegisterHotKey(nullptr, 0, MOD_ALT, VK_UP);
	RegisterHotKey(nullptr, 0, MOD_ALT, VK_DOWN);
	RegisterHotKey(nullptr, 0, MOD_ALT, VK_LEFT);
	RegisterHotKey(nullptr, 0, MOD_ALT, VK_RIGHT);
	MSG lpMsg;
	while (GetMessage(&lpMsg, nullptr, 0, 0)) {
		if (WM_HOTKEY == lpMsg.message) {
			if (HIWORD(lpMsg.lParam) == VK_F1) {}
			if (HIWORD(lpMsg.lParam) == VK_END) {}
			if (HIWORD(lpMsg.lParam) == VK_OEM_3) {
				// 技能Call(0, 54141, 0, 0, 0, 0, 0);
			}
		}
		Sleep(10);
	}
}