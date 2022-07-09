
// WeGameDlg.cpp: 实现文件

#include "pch.h"
#include "framework.h"
#include "WeGame.h"
#include "WeGameDlg.h"
#include "afxdialogex.h"

#include "Driver.h"
#include "Common.h"
#include "GameFunction.h"
#include "Automatic.h"
#include "ReadWrite.h"
#include "VuDriver.h"
#include "GameBulletin.h"
#include "GameCall.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Driver drive;

// CWeGameDlg 对话框
CWeGameDlg::CWeGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEGAME_DIALOG, pParent)
	, 自动模式(0)
	, 刷图功能(0)
	, 过图方式(0)
	, 技能代码(0)
	, 跟随(TRUE)
	, 打怪(TRUE)
	, 角色数量(10)
	, 副本ID(192)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWeGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, 自动模式);
	DDX_CBIndex(pDX, IDC_COMBO2, 刷图功能);
	DDX_CBIndex(pDX, IDC_COMBO3, 过图方式);
	DDX_Text(pDX, IDC_EDIT2, 技能代码);
	DDX_Check(pDX, IDC_CHECK1, 跟随);
	DDX_Check(pDX, IDC_CHECK2, 打怪);
	DDX_Text(pDX, IDC_EDIT3, 角色数量);
	DDX_Text(pDX, IDC_EDIT1, 副本ID);
}

BEGIN_MESSAGE_MAP(CWeGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CWeGameDlg::激活)
	ON_BN_CLICKED(IDC_BUTTON1, &CWeGameDlg::卸载)
	ON_WM_HOTKEY()
END_MESSAGE_MAP()

// CWeGameDlg 消息处理程序
BOOL CWeGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 设置窗口标题
	SetWindowText(_GetCurrentTime());

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

void CWeGameDlg::日志公告(CString msg)
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	int nLength = pEdit->GetWindowTextLength();

	//选定当前文本的末端
	pEdit->SetSel(nLength, nLength);
	//l追加文本
	CString data;
	data = data + "\r\n" + msg;
	pEdit->ReplaceSel(data);
}

BOOL CWeGameDlg::无忧驱动() {

	if (!drive.OpenDriver(L"\\\\.\\vuDrv")) {
		//MessageBoxW(L"Vu驱动文件打开异常");
		return FALSE;
	}

	Vu驱动* vuDrive = new Vu驱动();

	vuDrive->设置驱动句柄(drive.hDriver);
	CHAR* key = "";

	//激活驱动->校验驱动有效性(激活驱动)
	LONG64 结果 = vuDrive->效验有效性(key);

	if (结果 <= 0)
	{
		CString resMsg;
		switch (结果)
		{
		case 0:
			resMsg = "参数错误";
			break;
		case -1:
			resMsg = "激活码不存在";
			break;
		case -2:
			resMsg = "账户余额不足";
			break;
		case -3:
			resMsg = "扣费失败";
			break;
		case -4:
			resMsg = "网络错误";
			break;
		case -5:
			resMsg = "驱动安装失败";
			break;
		case -6:
			resMsg = "有效性效验失败";
			break;
		default:
			resMsg = "未知错误";
		}
		return FALSE;
	}

	// 获取自身句柄
	//HANDLE hWnd = AfxGetMainWnd()->GetSafeHwnd();

	// VU_保护_安装();
	// VU_保护_进程_开始(GetCurrentProcessId(), true);
	// VU_保护_窗口_开始((DWORD64)hWnd, GetCurrentProcessId());
	// VU_保护_游戏_开始((DWORD64)窗口句柄, 进程ID);

	vuDrive->VU_内存_置读写模式(2, 0);

	// 停止驱动服务
	//CloseHandle(drive.hDriver);
	//drive.hDriver = INVALID_HANDLE_VALUE;

	return TRUE;
}

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
		日志公告(L"未启动游戏");
		return;
	}

	_DebugStringW(L"gameProcess = %d ", gameProcess);

	_SetProcessId(gameProcess, NULL);

	// 设置热键
	RegisterHotKey(this->GetSafeHwnd(), 1000, 0, VK_F1);
	RegisterHotKey(this->GetSafeHwnd(), 1001, 0, VK_F2);
	RegisterHotKey(this->GetSafeHwnd(), 1002, 0, VK_F3);
	RegisterHotKey(this->GetSafeHwnd(), 1010, 0, VK_END);

	RegisterHotKey(this->GetSafeHwnd(), 192, 0, VK_OEM_3);


	Message("激活成功-欢迎使用", 1);

	日志公告(L"F1 - 技能全屏");
	日志公告(L"F2 - 武器冰冻");
	日志公告(L"F3 - HOOK倍攻");
	日志公告(L"波浪 - 无形秒杀");
	日志公告(L"End - 自动刷图");

	// 全局获取人物地址
	_CreateThread(&取人物指针线程);

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
