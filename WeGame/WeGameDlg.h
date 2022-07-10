
// WeGameDlg.h: 头文件
#pragma once

// CWeGameDlg 对话框
class CWeGameDlg : public CDialogEx
{
// 构造
public:
	CWeGameDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL 无忧驱动();
	void 激活();
	afx_msg void 卸载();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	// 自动模式
	int 自动模式;
	// 刷图功能
	int 刷图功能;
	// 过图方式
	int 过图方式;
	// 过图方式
	int 技能代码;
	// 跟随
	BOOL 跟随;
	// 打怪
	BOOL 打怪;
	// 角色数量
	int 角色数量;
	// 副本ID
	int 副本ID;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CWeGameDlg app;