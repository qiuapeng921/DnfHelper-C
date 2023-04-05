#include "Ui.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(true);

	if (Create())
	{
		XRunXCGUI();
	}
	XExitXCGUI();
	return 0;
}