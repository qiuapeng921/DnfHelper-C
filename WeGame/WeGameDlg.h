
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

// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	DECLARE_MESSAGE_MAP()
public:
	void 激活();
	afx_msg void 卸载();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CWeGameDlg app;