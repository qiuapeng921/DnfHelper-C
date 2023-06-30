//
// Created by Administrator on 2023/06/28.
//

// 主线程
void MainThread();

// 初始化
void InitHelper();

// 窗口消息
LRESULT CALLBACK WinMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 热键消息
void MessageLoopOfAB();