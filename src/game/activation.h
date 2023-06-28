#include <windows.h>

void MainThread();

void InitHelper();

LRESULT CALLBACK WinMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void MessageLoopOfAB();