
// WeGameDlg.cpp: 实现文件

#include "pch.h"
#include "framework.h"
#include "WeGame.h"
#include "WeGameDlg.h"
#include "afxdialogex.h"

#include "Driver.h"
#include "Common.h"
#include "功能.h"
#include "自动.h"
#include "读写.h"
#include "公告.h"
#include "游戏Call.h"
#include "寻路.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWeGameDlg 对话框
CWeGameDlg::CWeGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


BEGIN_MESSAGE_MAP(CWeGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CWeGameDlg::激活)
	ON_BN_CLICKED(IDC_BUTTON1, &CWeGameDlg::卸载)
	ON_WM_HOTKEY()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

// 动态设置窗口标题动态设置窗口标题 start
DWORD WINAPI SetWindowTitle(PVOID pParam)
{
	CWeGameDlg* weGameDlg = (CWeGameDlg*)pParam;
	while (true)
	{
		SetWindowText(weGameDlg->GetSafeHwnd(), L"情歌 √ 当前时间：" + _GetCurrentTime());
		Sleep(1000);
	}
}
// 动态设置窗口标题 end


// CWeGameDlg 消息处理程序
BOOL CWeGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 
	// SetWindowText(windowTitle);

	// 启动线程设置窗口标题，需要传递窗口句柄
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&SetWindowTitle, this, 0, 0);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	int nLength = pEdit->GetWindowTextLength();
	//选定当前文本的末端
	pEdit->SetSel(nLength, nLength);
	SetWindowPEdit(pEdit);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWeGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWeGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


Driver drive;

void CWeGameDlg::激活()
{
	TCHAR szDrvPath[MAX_PATH];
	GetModuleFileName(NULL, szDrvPath, MAX_PATH);
	*(_tcsrchr(szDrvPath, _T('\\')) + 1) = _T('\0');
	_tcscat_s(szDrvPath, MAX_PATH, _T("Randw.sys"));

	if (szDrvPath == NULL)
	{
		MessageBoxW(L"驱动文件未找到");
		//CDialogEx::OnCancel();
		return;
	}

	BOOL result = drive.LoadDriver(szDrvPath, L"Drivecontrol", L"Drivecontrol");
	if (!result)
	{
		drive.UnLoadDriver(L"Drivecontrol");
		MessageBoxW(L"加载驱动失败");
		return;
	}

	DWORD gameProcess = _GetProcessId(L"dnf.exe");

	HWND gameHandle = ::FindWindowW(L"地下城与勇士", L"地下城与勇士");

	if (gameProcess == 0)
	{
		监控(L"未启动游戏");
		return;
	}

	_DebugStringW(L"gameProcess = %d ", gameProcess);

	_SetProcessId(gameProcess, NULL);

	// 设置热键
	RegisterHotKey(this->GetSafeHwnd(), 1000, 0, VK_F1);
	RegisterHotKey(this->GetSafeHwnd(), 1001, 0, VK_F2);
	RegisterHotKey(this->GetSafeHwnd(), 1002, 0, VK_F3);
	RegisterHotKey(this->GetSafeHwnd(), 1010, 0, VK_END);
	// 波浪
	RegisterHotKey(this->GetSafeHwnd(), 192, 0, VK_OEM_3);


	RegisterHotKey(this->GetSafeHwnd(), 1000, MOD_CONTROL, VK_UP);//上
	RegisterHotKey(this->GetSafeHwnd(), 1001, MOD_CONTROL, VK_DOWN);//下
	RegisterHotKey(this->GetSafeHwnd(), 1002, MOD_CONTROL, VK_LEFT);//左
	RegisterHotKey(this->GetSafeHwnd(), 1003, MOD_CONTROL, VK_RIGHT);//右
	RegisterHotKey(this->GetSafeHwnd(), 1004, MOD_ALT, VK_UP);//上
	RegisterHotKey(this->GetSafeHwnd(), 1005, MOD_ALT, VK_DOWN);//下
	RegisterHotKey(this->GetSafeHwnd(), 1006, MOD_ALT, VK_LEFT);//左
	RegisterHotKey(this->GetSafeHwnd(), 1007, MOD_ALT, VK_RIGHT);//右


	游戏公告("激活成功-欢迎使用", 1);

	监控(L"F1 - 技能全屏");
	监控(L"F2 - 武器冰冻");
	监控(L"F3 - 自身倍攻");
	监控(L"~  - 无形秒杀");
	监控(L"End - 自动刷图");

	_InitConfig();
	// 禁用激活按钮
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
}

void CWeGameDlg::卸载()
{
	UnregisterHotKey(this->GetSafeHwnd(), 1000);
	UnregisterHotKey(this->GetSafeHwnd(), 1001);
	UnregisterHotKey(this->GetSafeHwnd(), 1002);
	UnregisterHotKey(this->GetSafeHwnd(), 1010);
	UnregisterHotKey(this->GetSafeHwnd(), 192);

	UnregisterHotKey(this->GetSafeHwnd(), 10000);//上
	UnregisterHotKey(this->GetSafeHwnd(), 10001);//下
	UnregisterHotKey(this->GetSafeHwnd(), 10002);//左
	UnregisterHotKey(this->GetSafeHwnd(), 10003);//右
	UnregisterHotKey(this->GetSafeHwnd(), 10004);//上
	UnregisterHotKey(this->GetSafeHwnd(), 10005);//下
	UnregisterHotKey(this->GetSafeHwnd(), 10006);//左
	UnregisterHotKey(this->GetSafeHwnd(), 10007);//右

	if (drive.UnLoadDriver(L"Drivecontrol") == FALSE) {
		_DebugStringW(L"驱动服务卸载失败");
	}
	_DebugStringW(L"驱动服务卸载完成");

	MessageBoxW(L"助手以安全卸载");

	// 关闭窗口界面
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CWeGameDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nHotKeyId) {
	case 1000:
		技能开关();
		break;
	case 1001:
		武器冰冻();
		break;
	case 1002:
		HOOK伤害();
		break;
	case 1010:
		自动开关();
		break;
	case 10000:
		组包_顺图(2);
		break;
	case 10001:
		组包_顺图(3);
		break;
	case 10002:
		组包_顺图(0);
		break;
	case 10003:
		组包_顺图(1);
		break;
	case 10004:
		坐标_顺图(2);
		break;
	case 10005:
		坐标_顺图(3);
		break;
	case 10006:
		坐标_顺图(0);
		break;
	case 10007:
		坐标_顺图(1);
		break;
	case 192:
		无形秒杀();
		break;
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

/*
屏蔽Esc和Enter 退出对话框
*/
BOOL CWeGameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
	{
		return TRUE;
	}
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_ESCAPE))
	{
		return TRUE;
	}
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_TAB))
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


LRESULT CWeGameDlg::OnNcHitTest(CPoint point)
{
	LRESULT ret = CDialog::OnNcHitTest(point);

	if (HTTOP == ret || HTBOTTOM == ret || HTLEFT == ret || HTRIGHT == ret || HTBOTTOMLEFT == ret || HTBOTTOMRIGHT == ret || HTTOPLEFT == ret || HTTOPRIGHT == ret || HTCAPTION == ret) {
		return HTCLIENT;
	}

	return ret;
}
