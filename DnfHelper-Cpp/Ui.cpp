#include "公用.h"
#include "日志.h"
#include "读写.h"

const wchar_t* svgIcon = LR"(<svg t="1674984352573" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="10315" width="16" height="16"><path d="M901.957085 349.126786c-60.072164-87.975001-153.76426-100.09183-187.170868-101.49977-79.698013-8.106329-155.59885 46.931378-196.0025 46.931377-40.40365 0-102.779718-45.822091-168.86763-44.627473-86.908379 1.279947-166.990375 50.515229-211.788509 128.421315-90.32157 156.665472-23.12437 388.762468 64.850631 515.818508 43.048873 62.248073 94.332069 132.133161 161.6146 129.615933 64.850631-2.559893 89.425607-41.982251 167.673013-41.982251 78.418066 0 100.433149 41.982251 169.03829 40.702304 69.799758-1.279947 114.000583-63.400025 156.665473-125.818758 49.405941-72.188992 69.714429-141.98875 70.909045-145.572601-1.578601-0.725303-135.973001-52.221824-137.380942-207.095371-1.279947-129.573268 105.68093-191.778676 110.502062-194.893213zM715.852839 0.042665c-51.496521 2.133244-113.829924 34.302571-150.820382 77.479438-33.107954 38.3984-58.706887 99.622516-50.899213 158.414733 57.51227 4.479813 112.720637-29.182784 148.473814-72.530311 35.710512-43.176868 59.816174-103.377026 53.245781-163.36386z" fill="#1afa29" opacity=".65" p-id="10316"></path></svg>)";

HWINDOW hWindow;
HELE    hButton;
HELE	cardEdit;
HELE	activation;
HELE content;
HXCGUI	runTime;


BOOL Create() //创建窗口和按钮
{
	wstring title = L"情歌 √ 当前时间：" + get_current_time_string();
	hWindow = XWnd_Create(0, 0, 300, 400, title.c_str(), 0, window_style_modal); //创建窗口
	// 设置窗口图标
	XWnd_SetIcon(hWindow, XImage_LoadSvgStringW(svgIcon));
	// 禁止改变大小
	XWnd_EnableDragBorder(hWindow, false);
	// 设置边框
	XWnd_SetBorderSize(hWindow, 0, 30, 0, 0);
	// 设置窗口置顶
	XWnd_SetTop(hWindow);


	if (hWindow) {
		XShapeText_Create(0, 35, 60, 30, L"卡号:", hWindow);
		cardEdit = XEdit_Create(35, 35, 200, 30, hWindow);
		XEdit_EnablePassword(cardEdit, true);
		XEdit_SetText(cardEdit, L"19930921");
		XEdit_SetTextAlign(cardEdit, edit_textAlign_flag_center);

		activation = XBtn_Create(240, 35, 50, 30, L"激活", hWindow);
		XEle_RegEventC(activation, XE_BNCLICK, OnEventBtnClick);

		content = XEdit_Create(1, 70, 298, 300, hWindow);
		XEdit_EnableMultiLine(content, true);
		XEdit_EnableReadOnly(content, true);
		XEdit_AutoScroll(content);
		XSView_ShowSBarV(content, true);
		XSView_ShowSBarH(content, true);
		XSView_ScrollBottom(content);
		XEdit_EnableAutoWrap(content, true);

		XShapeText_Create(1, 375, 60, 30, L"运行时间:", hWindow);
		runTime = XShapeText_Create(56, 375, 60, 30, get_running_time_string().c_str(), hWindow);

		XShapeText_Create(220, 375, 60, 30, L"版本号:", hWindow);
		XShapeText_Create(260, 375, 60, 30, L"v1.0.0", hWindow);

		SetTimer(0, 1000, 1000, (TIMERPROC)OnTitleTimer);
		SetTimer(0, 1001, 1000, (TIMERPROC)OnRunTimer);

		XWnd_AdjustLayout(hWindow);
		XWnd_ShowWindow(hWindow, SW_SHOW);

		return TRUE;
	}

	return FALSE;
}

INT OnWndClose(BOOL* pbHandled) {
	UnregisterHotKey(NULL, 1);

	return true;
}


INT OnEventBtnClick(BOOL* pbHandled) {

	设置日志句柄(content);

	DWORD processId = GetProcessIdByName(L"DNF.exe");
	if (processId == 0)
	{
		日志输出(L"未启动游戏 \n");
		return 0;
	}

	// TODO 未实现卡密判断等待后续添加

	// 设置读写进程id
	SetProcessId(processId);

	日志输出(L"激活成功-欢迎使用 \n");
	日志输出(format_string(L"当前时间：%s \n", get_current_time_string().c_str()));

	// 禁用激活按钮
	XEle_Enable(activation, false);

	// 注册热键
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, VK_F1);
	RegisterHotKey(NULL, 2, MOD_NOREPEAT, VK_F2);
	RegisterHotKey(NULL, 3, MOD_NOREPEAT, VK_F3);
	RegisterHotKey(NULL, 4, MOD_NOREPEAT, VK_END);
	RegisterHotKey(NULL, 5, MOD_NOREPEAT, VK_OEM_3);//反撇号键
	RegisterHotKey(NULL, 20, MOD_CONTROL | MOD_NOREPEAT, VK_LEFT);
	RegisterHotKey(NULL, 21, MOD_CONTROL | MOD_NOREPEAT, VK_RIGHT);
	RegisterHotKey(NULL, 22, MOD_CONTROL | MOD_NOREPEAT, VK_UP);
	RegisterHotKey(NULL, 23, MOD_CONTROL | MOD_NOREPEAT, VK_DOWN);

	// 消息循环，等待热键触发
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			switch (msg.wParam) {
			case 1:
				日志输出(L"你按下了 F1 键 \n");
				break;
			case 2:
				日志输出(L"你按下了 F2 键！\n");
				break;
			case 3:
				日志输出(L"你按下了 F3 键！\n");
				break;
			case 4:
				日志输出(L"你按下了 End 键！\n");
				break;
			case 5:
				日志输出(L"你按下了反撇号键！\n");
				break;
			case 20:
				日志输出(L"你按下了 CTRL+LEFT 键！\n");
				break;
			case 21:
				日志输出(L"你按下了 CTRL+RIGHT 键！\n");
				break;
			case 22:
				日志输出(L"你按下了 CTRL+UP 键！\n");
				break;
			case 23:
				日志输出(L"你按下了 CTRL+DOWN 键！\n");
				break;
			default:
				break;
			}
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

VOID OnTitleTimer(UINT nTimerID, BOOL* pbHandled)
{
	wstring title = L"情歌 √ 当前时间：" + get_current_time_string();
	XWnd_SetTitle(hWindow, title.c_str());
	XWnd_Redraw(hWindow, false);
	return;
}

VOID OnRunTimer(UINT nTimerID, BOOL* pbHandled)
{
	XShapeText_SetText(runTime, get_running_time_string().c_str());
	XWnd_Redraw(hWindow, false);
	return;
}