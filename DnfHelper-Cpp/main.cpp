#pragma comment(lib, "resources/XCGUI.lib")
#include "xcgui.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>


class CMyWnd
{
public:
    HWINDOW m_hWindow; //窗口句柄
    HELE    m_hButton; //按钮句柄

    BOOL Create() //创建窗口和按钮
    {
        m_hWindow = XWnd_Create(0, 0, 400, 300, L"界面库-窗口"); //创建窗口
        if (m_hWindow)
        {
            m_hButton = XBtn_Create(10, 60, 80, 25, L"按钮", m_hWindow); //创建按钮
            XEle_RegEventCPP(m_hButton, XE_BNCLICK, &CMyWnd::OnEventBtnClick); //注册按钮点击事件

            XWnd_AdjustLayout(m_hWindow); //调整布局,如果没有使用布局功能,可以不调用此函数
            XWnd_ShowWindow(m_hWindow, SW_SHOW); //显示窗口
            return TRUE;
        }
        return FALSE;
    }
    int OnEventBtnClick(BOOL* pbHandled) //按钮点击事件响应
    {
        //弹出消息框
        MessageBox(XWnd_GetHWND(m_hWindow), L"你点击了按钮", L"提示", MB_OK);
        *pbHandled = TRUE; //对该事件进行拦截,如果不需要拦截可以去掉该行代码
        return 0;    //事件的返回值
    }
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    XInitXCGUI(true); //初始化
    CMyWnd  MyWnd;
    if (MyWnd.Create())
    {
        XRunXCGUI(); //运行
    }
    XExitXCGUI(); //释放资源
    return 0;
}