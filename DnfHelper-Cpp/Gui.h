/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once
#include "Windows.h"
//3.3.8
////////////输入输出///////////////////
#ifndef  __in
#define  __in
#endif

#ifndef  __out
#define  __out
#endif

#ifndef  __in_out
#define  __in_out
#endif


#define  in_buffer_  //标识为内存指针, 非变量指针
#define  out_buffer_

#define  XC_API extern "C"

#define  XC_NAME1   L"name1"
#define  XC_NAME2   L"name2"
#define  XC_NAME3   L"name3"
#define  XC_NAME4   L"name4"
#define  XC_NAME5   L"name5"
#define  XC_NAME6   L"name6"

#ifndef  GetAValue
#define  GetAValue(rgba)         (LOBYTE((rgba)>>24))
#endif

#ifndef  RGBA
#define  RGBA(r, g, b, a)        ((BYTE)a<<24 | (BYTE)r | (BYTE)g<<8 | (BYTE)b<<16)
#endif

#define  COLOR_MAKE(r,g,b,a)     ((BYTE)a<<24 | (BYTE)r | (BYTE)g<<8 | (BYTE)b<<16)
#define  COLORREF_MAKE(r,g,b,a)  ((BYTE)a<<24 | (BYTE)r | (BYTE)g<<8 | (BYTE)b<<16)

#define  COLORREF_MAKE2(rgb,a)        ((BYTE)a<<24 | GetRValue(rgb) | GetGValue(rgb)<<8 | GetBValue(rgb)<<16)
#define  COLORREF_SET_RGB(color,rgb)  ((color & 0xFF000000) | (rgb & 0xFFFFFF))
#define  COLORREF_SET_A(color,a)      ((color & 0xFFFFFF) | ((BYTE)a<<24))
#define  COLORREF_GET_A(color)        ((BYTE)(color>>24))

#ifdef _WIN64
typedef  __int64  vint;
#else
typedef  int      vint;
#endif


//如果出现重复定义POINTF,请注释掉下面定义POINTF
#ifndef __IOleControlSite_INTERFACE_DEFINED__
struct POINTF
{
	float x;
	float y;
};
#endif

typedef   void  bkInfo_i;  //背景信息

/*@声明
#define  WM_LBUTTONDOWN
#define  SW_SHOW
#define  WM_PAINT
#define  WM_CLOSE
#define  WM_DESTROY
#define  WM_NCDESTROY
#define  WM_MOUSEMOVE
#define  WM_LBUTTONUP
#define  WM_RBUTTONDOWN
#define  WM_RBUTTONUP
#define  WM_LBUTTONDBLCLK
#define  WM_RBUTTONDBLCLK
#define  WM_MOUSEWHEEL
#define  WM_EXITSIZEMOVE
#define  WM_MOUSEHOVER
#define  WM_MOUSELEAVE
#define  WM_SIZE
#define  WM_TIMER
#define  WM_SETFOCUS
#define  WM_KILLFOCUS
#define  WM_KEYDOWN
#define  WM_CAPTURECHANGE
#define  WM_SETCURSOR
#define  WM_CHAR
#define  WM_DROPFILES
*/

/////////////////////////////////////////////////////////////////////
/////////////////////句柄类型定义//////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#define DECLARE_HANDLEX(name) struct name##__ { int unused; }; typedef struct name##__ *name

/// @defgroup groupHandle   句柄类型
/// @{

//@别名  炫彩句柄
typedef void* HXCGUI;       ///<资源句柄
//@别名  窗口句柄
DECLARE_HANDLEX(HWINDOW);     ///<窗口资源句柄
//@别名  元素句柄
DECLARE_HANDLEX(HELE);        ///<元素资源句柄
//@别名  菜单句柄
DECLARE_HANDLEX(HMENUX);      ///<菜单资源句柄
//@别名  绘图句柄
DECLARE_HANDLEX(HDRAW);       ///<图形绘制资源句柄
//@别名  图片句柄
DECLARE_HANDLEX(HIMAGE);      ///<图片资源句柄
//@别名  字体句柄
DECLARE_HANDLEX(HFONTX);      ///<炫彩字体句柄
//@别名  背景句柄
DECLARE_HANDLEX(HBKM);        ///<背景内容管理器句柄
//@别名  模板句柄
DECLARE_HANDLEX(HTEMP);       ///<模板句柄
//@别名  SVG句柄
DECLARE_HANDLEX(HSVG);        ///<SVG句柄
///@}

#ifndef _INC_SHELLAPI
DECLARE_HANDLEX(HDROP);
#endif

/////////////////////////////////////////////////////////////////////
/////////////////////炫彩对象类型及样式/////////////////////////////////
/////////////////////////////////////////////////////////////////////

//对象类型决定功能
//对象样式决定外观
/// @defgroup group_type_style_  对象类型及样式
/// @{

/// @defgroup group_ObjectType 对象句柄类型(XC_OBJECT_TYPE)
/// @{
enum XC_OBJECT_TYPE
{
	XC_ERROR = -1,   ///<错误类型
	XC_NOTHING = 0,    ///<啥也不是
	XC_WINDOW = 1,    ///<窗口
	XC_MODALWINDOW = 2,    ///<模态窗口
	XC_FRAMEWND = 3,    ///<框架窗口
	XC_FLOATWND = 4,    ///<浮动窗口
	XC_COMBOBOXWINDOW = 11,   ///<组合框弹出下拉列表窗口 comboBoxWindow_        
	XC_POPUPMENUWINDOW = 12,  ///<弹出菜单主窗口 popupMenuWindow_       
	XC_POPUPMENUCHILDWINDOW = 13,   ///<弹出菜单子窗口 popupMenuChildWindow_  
	XC_OBJECT_UI = 19,   ///<可视对象
	XC_WIDGET_UI = 20,   ///<窗口组件
	//元素
	XC_ELE = 21,   ///<基础元素
	XC_ELE_LAYOUT = 53,   ///<布局元素
	XC_LAYOUT_FRAME = 54,   ///<流式布局
	XC_BUTTON = 22,   ///<按钮
	XC_EDIT = 45,   ///<编辑框
	XC_EDITOR = 46,   ///<代码编辑框

	XC_RICHEDIT = 23,   ///<富文本编辑框(已废弃), 请使用XC_EDIT
	XC_COMBOBOX = 24,   ///<下拉组合框
	XC_SCROLLBAR = 25,   ///<滚动条
	XC_SCROLLVIEW = 26,   ///<滚动视图
	XC_LIST = 27,   ///<列表
	XC_LISTBOX = 28,   ///<列表框
	XC_LISTVIEW = 29,   ///<列表视图,大图标
	XC_TREE = 30,   ///<列表树
	XC_MENUBAR = 31,   ///<菜单条
	XC_SLIDERBAR = 32,   ///<滑动条
	XC_PROGRESSBAR = 33,   ///<进度条
	XC_TOOLBAR = 34,   ///<工具条
	XC_MONTHCAL = 35,   ///<月历卡片
	XC_DATETIME = 36,   ///<日期时间
	XC_PROPERTYGRID = 37,   ///<属性网格
	XC_EDIT_COLOR = 38,   ///<颜色选择框
	XC_EDIT_SET = 39,   ///<设置编辑框
	XC_TABBAR = 40,   ///<tab条
	XC_TEXTLINK = 41,   ///<文本链接按钮

	XC_PANE = 42,   ///<窗格
	XC_PANE_SPLIT = 43,   ///<窗格拖动分割条
	XC_MENUBAR_BUTTON = 44,   ///<菜单条上的按钮
	//	XC_TOOLBAR_BUTTON       =45,   ///<工具条上按钮
	//	XC_PROPERTYPAGE_LABEL   =46,   ///<属性页标签按钮
	//	XC_PIER                 =47,   ///<窗格停靠码头
	//	XC_BUTTON_MENU          =48,   ///<弹出菜单按钮
	//	XC_VIRTUAL_ELE          =49,   ///<虚拟元素
	XC_EDIT_FILE = 50,   ///<EditFile 文件选择编辑框
	XC_EDIT_FOLDER = 51,   ///<EditFolder  文件夹选择编辑框
	XC_LIST_HEADER = 52,   ///<列表头元素

	XC_SHAPE = 61,    ///<形状对象
	XC_SHAPE_TEXT = 62,    ///<形状对象-文本
	XC_SHAPE_PICTURE = 63,    ///<形状对象-图片
	XC_SHAPE_RECT = 64,    ///<形状对象-矩形
	XC_SHAPE_ELLIPSE = 65,    ///<形状对象-圆
	XC_SHAPE_LINE = 66,    ///<形状对象-直线
	XC_SHAPE_GROUPBOX = 67,    ///<形状对象-组框
	XC_SHAPE_GIF = 68,    ///<形状对象-GIF
	XC_SHAPE_TABLE = 69,    ///<形状对象-表格

	//其他类型
	XC_MENU = 81,   ///<弹出菜单
	XC_IMAGE = 82,         ///<图片
	XC_IMAGE_TEXTURE = XC_IMAGE,   ///<图片纹理,图片源,图片素材
	XC_HDRAW = 83,   ///<绘图操作
	XC_FONT = 84,   ///<炫彩字体
	//	XC_FLASH             =85,   ///<flash   
	//	XC_PANE_CELL         =86,   ///<...
	//	XC_WEB               =87,   ///<...
	XC_IMAGE_FRAME = 88,   ///<图片帧,指定图片的渲染属性
	XC_SVG = 89,   ///<SVG矢量图形

	XC_LAYOUT_OBJECT = 101, ///<布局对象LayoutObject, 已废弃
	XC_ADAPTER = 102, ///<数据适配器Adapter
	XC_ADAPTER_TABLE = 103, ///<数据适配器AdapterTable
	XC_ADAPTER_TREE = 104, ///<数据适配器AdapterTree
	XC_ADAPTER_LISTVIEW = 105, ///<数据适配器AdapterListView
	XC_ADAPTER_MAP = 106, ///<数据适配器AdapterMap
	XC_BKINFOM = 116, ///<背景管理器

	//无实体对象,只是用来判断布局
	XC_LAYOUT_LISTVIEW = 111,  ///<内部使用
	XC_LAYOUT_LIST = 112,  ///<内部使用
	XC_LAYOUT_OBJECT_GROUP = 113,  ///<内部使用
	XC_LAYOUT_OBJECT_ITEM = 114,  ///<内部使用
	XC_LAYOUT_PANEL = 115,  ///<内部使用

	//无实体对象,只是用来判断类型
//	XC_LIST_ITEM       =121,     //列表项模板 list_item
//	XC_LISTVIEW_GROUP  =122,
//	XC_LISTVIEW_ITEM   =123,
XC_LAYOUT_BOX = 124,      ///<布局盒子,复合类型

XC_ANIMATION_SEQUENCE = 131,   ///<动画序列
XC_ANIMATION_GROUP = 132,   ///<动画同步组
XC_ANIMATION_ITEM = 133,   ///<动画项
};
///@}


/// @defgroup group_ObjectTypeEx   对象扩展类型(XC_OBJECT_TYPE_EX,功能扩展)
/// @{
enum XC_OBJECT_TYPE_EX
{
	xc_ex_error = -1,        ///<错误类型
	button_type_default = 0, ///<默认类型
	button_type_radio,     ///<单选按钮
	button_type_check,     ///<多选按钮
	button_type_close,     ///<窗口关闭按钮
	button_type_min,       ///<窗口最小化按钮
	button_type_max,       ///<窗口最大化还原按钮

	element_type_layout,   ///<布局元素,启用布局功能的元素
};
///@}


/// @defgroup group_ObjectStyle 对象样式(XC_OBJECT_STYLE,用于区分外观)
/// @{
enum  XC_OBJECT_STYLE
{
	xc_style_default = 0,
	button_style_default = xc_style_default,  ///<默认风格
	button_style_radio,                 ///<单选按钮
	button_style_check,                 ///<多选按钮
	button_style_icon,                  ///<图标按钮		   
	button_style_expand,                ///<展开按钮

	button_style_close,			        ///<关闭按钮
	button_style_max,			        ///<最大化按钮
	button_style_min,			        ///<最小化按钮

	button_style_scrollbar_left,         ///<水平滚动条-左按钮
	button_style_scrollbar_right,        ///<水平滚动条-右按钮
	button_style_scrollbar_up,           ///<垂直滚动条-上按钮
	button_style_scrollbar_down,         ///<垂直滚动条-下按钮
	button_style_scrollbar_slider_h,     ///<水平滚动条-滑块
	button_style_scrollbar_slider_v,     ///<垂直滚动条-滑块

	button_style_tabBar,                 ///<Tab条-按钮
	button_style_slider,                 ///<滑动条-滑块

	button_style_toolBar,                ///<工具条-按钮
	button_style_toolBar_left,           ///<工具条-左滚动按钮
	button_style_toolBar_right,          ///<工具条-右滚动按钮

	button_style_pane_close,             ///<窗格-关闭按钮
	button_style_pane_lock,              ///<窗格-锁定按钮
	button_style_pane_menu,              ///<窗格-菜单按钮

	button_style_pane_dock_left,         ///<窗格-码头按钮左
	button_style_pane_dock_top,          ///<窗格-码头按钮上
	button_style_pane_dock_right,        ///<窗格-码头按钮右
	button_style_pane_dock_bottom,       ///<窗格-码头按钮下

	element_style_frameWnd_dock_left,    ///<框架窗口-停靠码头左
	element_style_frameWnd_dock_top,     ///<框架窗口-停靠码头上
	element_style_frameWnd_dock_right,   ///<框架窗口-停靠码头右
	element_style_frameWnd_dock_bottom,  ///<框架窗口-停靠码头下

	element_style_toolBar_separator,     ///<工具条-分割线
	listBox_style_comboBox,              ///<组合框-下拉列表框  ,下拉组合框弹出的ListBox
};
///@}

/// @defgroup group_WindowStyle  窗口样式(window_style_)
/// @{
enum  window_style_
{
	window_style_nothing = 0x0000,   ///<什么也没有
	window_style_caption = 0x0001,   ///<标题栏
	window_style_border = 0x0002,   ///<边框,如果没有指定,那么边框大小为0
	window_style_center = 0x0004,   ///<窗口居中
	window_style_drag_border = 0x0008,   ///<拖动窗口边框
	window_style_drag_window = 0x0010,   ///<拖动窗口
	window_style_allow_maxWindow = 0x0020,   ///<允许窗口最大化

	window_style_icon = 0x0040,   ///<图标
	window_style_title = 0x0080,   ///<标题
	window_style_btn_min = 0x0100,   ///<控制按钮-最小化
	window_style_btn_max = 0x0200,   ///<控制按钮-最大化
	window_style_btn_close = 0x0400,   ///<控制按钮-关闭

	///窗口样式-控制按钮: 居中 图标, 标题, 关闭按钮, 最大化按钮, 最小化按钮
	window_style_default = (window_style_caption | window_style_border | window_style_center | \
	window_style_drag_border | window_style_allow_maxWindow | window_style_icon | \
		window_style_title | window_style_btn_min | window_style_btn_max | window_style_btn_close),

	///窗口样式-简单: 居中
	window_style_simple = (window_style_caption | window_style_border | window_style_center | window_style_drag_border | window_style_allow_maxWindow),

	///窗口样式-弹出窗口: 图标, 标题, 关闭按钮
	window_style_pop = (window_style_caption | window_style_border | window_style_center | \
		window_style_drag_border | window_style_allow_maxWindow | window_style_icon | \
		window_style_title | window_style_btn_close),

	///模态窗口样式-控制按钮: 居中, 图标, 标题, 关闭按钮
	window_style_modal = (window_style_caption | window_style_border | window_style_center | \
		window_style_icon | window_style_title | window_style_btn_close),

	///模态窗口样式-简单: 居中
	window_style_modal_simple = (window_style_caption | window_style_border | window_style_center),
};

///@}
///@}

/////////////////////////////////////////////////////////////////////
/////////////////////宏定义///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/// @defgroup group_macro_def  宏定义
/// @{

#ifdef _DEBUG
#define XTRACEA   _xtrace
#define XTRACE    _xtracew
#define XERRORA   XTRACEA 
#define XERROR    XTRACE
#else
#define XTRACEA
#define XTRACE
#define XERROR 
#define XERRORW
#endif

#define  XC_GetObjectByUID_(T)  XC_GetObjectByUID(XRes_GetIDValue(L#T))
#define  GetLayoutFile()        GetLayoutFile()
#define  XC_LAYOUT_FILE(file)   const wchar_t*  GetLayoutFile(){ return file; };
#define  XC_EVENT_DECLARE_MARK
#define  XC_EVENT_REGISTER_MARK
#define  XC_EVENT_IMPLEMENT_MARK(T)

#define  CLOUDUI_flag_openUrl       1
#define  CLOUDUI_flag_downloadFile  2
#define  CLOUDUI_flag_downloadFileComplete      3
#define  CLOUDUI_flag_complete      4

/// @name  窗口位置
/// @{
#define  WINDOW_TOP            1 //上
#define  WINDOW_BOTTOM         2 //下
#define  WINDOW_LEFT           3 //左
#define  WINDOW_RIGHT          4 //右
#define  WINDOW_TOPLEFT        5 //左上角
#define  WINDOW_TOPRIGHT       6 //右上角
#define  WINDOW_BOTTOMLEFT     7 //左下角
#define  WINDOW_BOTTOMRIGHT    8 //右下角
#define  WINDOW_CAPTION        9 //标题栏移动窗口区域
#define  WINDOW_BODY           10
/// @}

/// @name  特殊ID
/// @{
#define  XC_ID_ROOT            0   ///<根节点
#define  XC_ID_ERROR          -1   ///<ID错误
#define  XC_ID_FIRST          -2   ///<插入开始位置
#define  XC_ID_LAST           -3   ///<插入末尾位置
/// @}

///@name 菜单ID , 当前未使用
///@{
#define  IDM_CLIP          1000000000    ///<剪切
#define  IDM_COPY          1000000001    ///<复制
#define  IDM_PASTE         1000000002    ///<粘贴
#define  IDM_DELETE        1000000003    ///<删除
#define  IDM_SELECTALL     1000000004    ///<全选
#define  IDM_DELETEALL     1000000005    ///<清空
///@}


//窗格菜单 当前未使用
#define  IDM_LOCK          1000000006    ///<锁定
#define  IDM_DOCK          1000000007    ///<停靠
#define  IDM_FLOAT         1000000008    ///<浮动
#define  IDM_HIDE          1000000009    ///<隐藏

//#define  edit_style_no        0  ///<无效样式
#define  edit_style_default   1    ///<edit 默认样式

#define   TEXT_BUFFER_SIZE     10240  ///<共享文本缓冲区大小
/// @}

/////////////////////////////////////////////////////////////////////
/////////////////////窗口事件/////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

//窗口消息
/**
@addtogroup wndMSG

<hr>
<h2>Windows 标准消息</h2>
- @ref WM_PAINT 窗口绘制消息
- @ref WM_CLOSE 窗口关闭消息.
- @ref WM_DESTROY 窗口销毁消息.
- @ref WM_NCDESTROY 窗口非客户区销毁消息.
- @ref WM_LBUTTONDOWN 窗口鼠标左键按下消息
- @ref WM_LBUTTONUP 窗口鼠标左键弹起消息.
- @ref WM_RBUTTONDOWN 窗口鼠标右键按下消息.
- @ref WM_RBUTTONUP 窗口鼠标右键弹起消息.
- @ref WM_LBUTTONDBLCLK 窗口鼠标左键双击消息.
- @ref WM_RBUTTONDBLCLK 窗口鼠标右键双击消息.
- @ref WM_MOUSEMOVE 窗口鼠标移动消息.
- @ref WM_MOUSEHOVER 窗口鼠标悬停消息
- @ref WM_MOUSELEAVE 窗口鼠标离开消息.
- @ref WM_MOUSEWHEEL 窗口鼠标滚轮滚动消息.
- @ref WM_CAPTURECHANGED 窗口鼠标捕获改变消息.
- @ref WM_KEYDOWN 窗口键盘按键消息.
- @ref WM_KEYUP 窗口键盘弹起消息.
- @ref WM_CHAR       窗口字符消息.
- @ref WM_SIZE 窗口大小改变消息.
- @ref WM_EXITSIZEMOVE 窗口退出移动或调整大小模式循环改，详情参见MSDN.
- @ref WM_TIMER 窗口定时器消息.
- @ref WM_SETFOCUS 窗口获得焦点.
- @ref WM_KILLFOCUS 窗口失去焦点.
- @ref WM_SETCURSOR  窗口设置鼠标光标.
- @ref WM_DROPFILES  拖动文件到窗口.
- @ref other 其他Windows系统消息,包含你自定义的Windows消息.

<hr>
@anchor WM_PAINT WM_PAINT 窗口绘制消息
@code   int CALLBACK OnWndDrawWindow(HDRAW hDraw,BOOL *pbHandled) @endcode
@param  hDraw   图形绘制句柄.

<hr>
@anchor WM_CLOSE WM_CLOSE 窗口关闭消息.
@code   int CALLBACK OnWndClose(BOOL *pbHandled) @endcode

<hr>
@anchor WM_DESTROY WM_DESTROY 窗口销毁消息.
@code   int CALLBACK OnWndDestroy(BOOL *pbHandled)  @endcode

<hr>
@anchor WM_NCDESTROY WM_NCDESTROY 窗口非客户区销毁消息.
@code   int CALLBACK OnWndNCDestroy(BOOL *pbHandled) @endcode

<hr>
@anchor WM_LBUTTONDOWN WM_LBUTTONDOWN 窗口鼠标左键按下消息
@code   int CALLBACK OnWndLButtonDown(UINT nFlags,POINT *pPt,BOOL *pbHandled) @endcode
@param  flags   请参见MSDN WM_LBUTTONDOWN.
@param  pPt     鼠标坐标点.

<hr>
@anchor WM_LBUTTONUP WM_LBUTTONUP 窗口鼠标左键弹起消息.
@code   int CALLBACK OnWndLButtonUp(UINT nFlags,POINT *pPt,BOOL *pbHandled) @endcode
@param  flags   请参见MSDN WM_LBUTTONUP.
@param  pPt     鼠标坐标点.

<hr>
@anchor WM_RBUTTONDOWN WM_RBUTTONDOWN 窗口鼠标右键按下消息.
@code   int CALLBACK OnWndRButtonDown(UINT nFlags,POINT *pPt,BOOL *pbHandled) @endcode
@param  flags   请参见MSDN WM_RBUTTONDOWN.
@param  pPt     鼠标坐标点.

<hr>
@anchor WM_RBUTTONUP WM_RBUTTONUP 窗口鼠标右键弹起消息.
@code   int CALLBACK OnWndRButtonUp(UINT nFlags,POINT *pPt,BOOL *pbHandled) @endcode
@param  flags   请参见MSDN WM_RBUTTONUP.
@param  pPt     鼠标坐标点.

<hr>
@anchor WM_LBUTTONDBLCLK WM_LBUTTONDBLCLK 窗口鼠标左键双击消息.
@code   int CALLBACK OnWndLButtonDBClick(UINT nFlags,POINT *pPt,BOOL *pbHandled) @endcode
@param  flags   请参见MSDN WM_LBUTTONDBLCLK.
@param  pPt     鼠标坐标点.

<hr>
@anchor WM_RBUTTONDBLCLK WM_RBUTTONDBLCLK 窗口鼠标右键双击消息.
@code   int CALLBACK OnWndRButtonDBClick(UINT nFlags,POINT *pPt,BOOL *pbHandled) @endcode
@param  flags   请参见MSDN WM_RBUTTONDBLCLK.
@param  pPt     鼠标坐标点.

<hr>
@anchor WM_MOUSEMOVE WM_MOUSEMOVE 窗口鼠标移动消息.
@code   int CALLBACK OnWndMouseMove(UINT nFlags,POINT *pPt,BOOL *pbHandled)  @endcode
@param  flags   请参见MSDN WM_MOUSEMOVE wParam参数.
@param  pPt     鼠标坐标点.

<hr>
@anchor WM_MOUSEHOVER WM_MOUSEHOVER 窗口鼠标悬停消息.
@code   int CALLBACK OnWndMouseHover(UINT nFlags,POINT *pPt,BOOL *pbHandled) @endcode
@param  flags  请参见MSDN WM_MOUSEHOVER消息wParam参数.
@param  pPt    鼠标位置

<hr>
@anchor WM_MOUSELEAVE WM_MOUSELEAVE 窗口鼠标离开消息.
@code   int CALLBACK OnWndMouseLeave(BOOL *pbHandled) @endcode

<hr>
@anchor WM_MOUSEWHEEL WM_MOUSEWHEEL 窗口鼠标滚轮滚动消息.
@code   int CALLBACK OnWndMouseWheel(UINT nFlags,POINT *pPt,BOOL *pbHandled) @endcode
@param  flags   请参见MSDN WM_MOUSEWHEEL消息wParam参数.
@param  pPt     鼠标坐标点.

<hr>
@anchor WM_CAPTURECHANGED WM_CAPTURECHANGED 窗口鼠标捕获改变消息.
@code   int CALLBACK OnWndCaptureChanged(HWND hWnd,BOOL *pbHandled) @endcode
@param  hWnd    获得鼠标捕获的窗口句柄.

<hr>
@anchor WM_KEYDOWN WM_KEYDOWN 窗口键盘按下消息.
@code   int CALLBACK OnWndKeyDown(WPARAM wParam,LPARAM lParam,BOOL *pbHandled) @endcode
@note   wParam,lParam:请参见MSDN WM_KEYDOWN.
<hr>
@anchor WM_KEYUP WM_KEYUP 窗口键盘弹起消息.
@code   int CALLBACK OnWndKeyUp(WPARAM wParam,LPARAM lParam,BOOL *pbHandled) @endcode
@note   wParam,lParam:请参见MSDN WM_KEYUP.

<hr>
@anchor  WM_CHAR WM_CHAR 窗口字符输入消息.
@code    int CALLBACK OnWndChar(WPARAM wParam,LPARAM lParam,BOOL *pbHandled) @endcode
@note    wParam,lParam:请参见MSDN WM_CHAR.

<hr>
@anchor WM_SIZE WM_SIZE 窗口大小改变消息.
@code   int CALLBACK OnWndSize(UINT nFlags,SIZE *pSize,BOOL *pbHandled) @endcode
@param  flags   请参见MSDN WM_SIZE消息wParam参数.
@param  pSize   窗口大小.

<hr>
@anchor WM_EXITSIZEMOVE WM_EXITSIZEMOVE 窗口退出移动或调整大小模式循环，详情参见MSDN.
@code   int CALLBACK OnWndExitSizeMove(BOOL *pbHandled) @endcode

<hr>
@anchor WM_TIMER WM_TIMER 窗口定时器消息.
@code   int CALLBACK OnWndTimer(UINT nIDEvent,BOOL *pbHandled) @endcode
@param  nIDEnent 定时器标示符.
@param  uElapse  指定所经过的系统启动以来的毫秒数,这是由GetTickCount函数的返回值.

<hr>
@anchor WM_SETFOCUS WM_SETFOCUS 窗口获得焦点.
@code   int CALLBACK OnWndSetFocus(BOOL *pbHandled) @endcode

<hr>
@anchor WM_KILLFOCUS WM_KILLFOCUS 窗口失去焦点.
@code   int CALLBACK OnWndKillFocus(BOOL *pbHandled) @endcode

<hr>
@anchor  WM_SETCURSOR WM_SETCURSOR 窗口设置鼠标光标.
@code    int CALLBACK OnWndSetCursor(WPARAM wParam,LPARAM lParam,BOOL *pbHandled) @endcode
@note    wParam,lParam:请参见MSDN WM_SETCURSOR.

<hr>
@anchor  WM_DROPFILES WM_DROPFILES 拖动文件到窗口消息,需启用:XWnd_EnableDragFiles()
@code    int CALLBACK OnDropFiles(HDROP hDropInfo , BOOL *pbHandled) @endcode
@note    请参见MSDN WM_DROPFILES.

<hr>
@anchor other 其他Windows系统消息,包含你自定义的Windows消息.
@code   int CALLBACK OnWndOther(WPARAM wParam,LPARAM lParam,BOOL *pbHandled) @endcode
@param  wParam  消息参数.
@param  lParam  消息参数.
@note   参数信息请参见MSDN.
@{
*/

//窗口消息-包含系统非客户区消息
#define  XWM_EVENT_ALL        WM_APP+1000 //事件投递 -------不公开-------不需要注册

//wParam:left-top坐标组合; lParam:right-bottom坐标组合; 如果这2个参数为空,那么重绘整个窗口
//#define  XWM_REDRAW           WM_APP+1007  //窗口重绘延时 ----不公开-----内部自定义消息

//重绘元素,内部使用
#define  XWM_REDRAW_ELE       0x7000+1 //重绘元素 wParam:元素句柄, lParam:RECT*基于窗口坐标

///@brief 窗口消息过程
///@code  int CALLBACK OnWndProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL *pbHandled)  @endcode
#define  XWM_WINDPROC         0x7000+2    //注册窗口处理过程

#define  XWM_DRAW_T           0x7000+3    //窗口绘制,内部使用, wParam:0, lParam:0

#define  XWM_TIMER_T          0x7000+4    //内部使用, wParam:hXCGUI, lParam:ID

#define  XWM_CLOUDUI_DOWNLOADFILE_COMPLETE   0x7000+6  //内部使用

#define  XWM_CLOUNDUI_OPENURL_WAIT    0x7000+7 //内部使用

#define  XWM_CALL_UI_THREAD   0x7000+8     //内部使用

/// @brief  炫彩定时器,非系统定时器,注册消息XWM_TIMER接收
/// @code  int CALLBACK OnWndXCTimer(UINT nTimerID,BOOL *pbHandled)  @endcode
/// @param nTimerID   定时器ID
#define  XWM_XC_TIMER         0x7000+5 //wParam:定时器ID, lParam:0

///@brief 菜单弹出
///@code  int CALLBACK OnWndMenuPopup(HMENUX hMenu, BOOL *pbHandled) @endcode
#define  XWM_MENU_POPUP       0x7000+11

///@brief 菜单弹出窗口
///@code  int CALLBACK OnWndMenuPopupWnd(HMENUX hMenu,menu_popupWnd_ *pInfo,BOOL *pbHandled) @endcode
#define  XWM_MENU_POPUP_WND     0x7000+12    

///@brief 菜单选择
///@code  int CALLBACK OnWndMenuSelect(int nID,BOOL *pbHandled) @endcode
#define  XWM_MENU_SELECT       0x7000+13 //菜单选择 wParam:菜单项ID, lParam:0

///@brief 菜单退出
///@code  int CALLBACK OnWndMenuExit(BOOL *pbHandled) @endcode
#define  XWM_MENU_EXIT         0x7000+14 //菜单退出 wParam:0, lParam:0

///@brief 绘制菜单背景, 启用该功能需要调用XMenu_EnableDrawBackground().
///@code  int CALLBACK OnWndMenuDrawBackground(HDRAW hDraw,menu_drawBackground_ *pInfo,BOOL *pbHandled) @endcode
#define  XWM_MENU_DRAW_BACKGROUND   0x7000+15 //绘制菜单背景

/// @brief 绘制菜单项事件, 启用该功能需要调用XMenu_EnableDrawItem().
/// @code  int CALLBACK OnMenuDrawItem(HDRAW hDraw,menu_drawItem_* pInfo,BOOL *pbHandled) @endcode
#define  XWM_MENU_DRAWITEM             0x7000+16  //绘制菜单项 

#define  XWM_COMBOBOX_POPUP_DROPLIST   0x7000+17  //弹出下拉组框列表,内部使用

///@brief 浮动窗格
///@code  int CALLBACK OnWndFloatPane(HWINDOW hFloatWnd, HELE hPane, BOOL *pbHandled) @endcode
#define  XWM_FLOAT_PANE               0x7000+18 //浮动窗格, 窗格从框架窗口中弹出,变成浮动窗格

///@brief 窗口绘制完成消息
///@code   int CALLBACK OnWndDrawWindowEnd(HDRAW hDraw,BOOL *pbHandled) @endcode
#define  XWM_PAINT_END               0x7000+19

///@brief 窗口绘制完成并且已经显示到屏幕
///@code   int CALLBACK OnWndDrawWindowDisplay(BOOL *pbHandled) @endcode
#define  XWM_PAINT_DISPLAY           0x7000+20

///@brief  框架窗口码头弹出窗格  当用户点击码头上的按钮时,显示对应的窗格,当失去焦点时自动隐藏窗格
///@param  hWindowDock 弹出窗格窗口句柄
///@param  hPane       窗格句柄
///@code   int CALLBACK OnWndDocPopup(HWINDOW hWindowDock,  HELE hPane, BOOL *pbHandled) @endcode
#define  XWM_DOCK_POPUP              0x7000+21

///@brief  浮动窗口拖动   用户拖动浮动窗口移动,显示停靠提示
///@param  hFloatWnd 拖动的浮动窗口句柄
///@param  hArray    HWINDOW array[6],窗格停靠提示窗口句柄数组,有6个成员,分别为:[0]中间十字, [1]左侧,[2]顶部,[3]右侧,[4]底部, [5]停靠位置预览 
///@code   int CALLBACK OnWndFloatWndDrag(HWINDOW hFloatWnd, HWINDOW* hArray, BOOL *pbHandled) @endcode
#define  XWM_FLOATWND_DRAG           0x7000+22


//窗格显示隐藏
//int CALLBACK OnWndPaneShow(HELE hPane, BOOL bShow, BOOL *pbHandled);
#define  XWM_PANE_SHOW              0x7000+23
///@}

/////////////////////////////////////////////////////////////////////
/////////////////元素事件/////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//元素事件
/// @addtogroup eleEvents
/// @{


/// @brief 元素处理过程事件.
/// @code  int CALLBACK OnEventProc(UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL *pbHandled) @endcode
#define  XE_ELEPROCE         1     ///元素事件处理过程

/// @brief 元素绘制事件
/// @code  int CALLBACK OnDraw(HDRAW hDraw,BOOL *pbHandled)  @endcode
#define  XE_PAINT            2

/// @brief 该元素及子元素绘制完成事件.启用该功能需要调用XEle_EnableEvent_XE_PAINT_END()
/// @code  int CALLBACK OnPaintEnd(HDRAW hDraw,BOOL *pbHandled) @endcode
#define  XE_PAINT_END        3     //元素及子元素绘制完成后触发,需要启用该功能,XEle_EnableEvent_XE_PAINT_END()

/// @brief 滚动视图绘制事件.
/// @code int CALLBACK OnDrawScrollView(HDRAW hDraw,BOOL *pbHandled) @endcode
#define  XE_PAINT_SCROLLVIEW   4

/// @brief 元素鼠标移动事件.
/// @code  int CALLBACK OnMouseMove(UINT nFlags, POINT *pPt, BOOL *pbHandled)  @endcode
#define  XE_MOUSEMOVE        5

/// @brief 元素鼠标进入事件.
/// @code  int CALLBACK OnMouseStay(BOOL *pbHandled) @endcode
#define  XE_MOUSESTAY        6   ///停留

/// @brief 元素鼠标悬停事件.
/// @code  int CALLBACK OnMouseHover(UINT nFlags, POINT *pPt, BOOL *pbHandled) @endcode
#define  XE_MOUSEHOVER       7   ///悬停

/// @brief 元素鼠标离开事件.
/// @param  hEleStay 将获得鼠标停留状态的元素.
/// @code  int CALLBACK OnMouseLeave(HELE hEleStay,BOOL *pbHandled) @endcode
#define  XE_MOUSELEAVE       8   ///离开

/// @brief 元素鼠标滚轮滚动事件. 如果非滚动视图需要调用 XEle_EnableEvent_XE_MOUSEWHEEL()
/// @code  int CALLBACK OnMouseWheel(UINT nFlags,POINT *pPt,BOOL *pbHandled) @endcode
/// @param flags      见MSDN中WM_MOUSEWHEEL消息wParam参数说明.
#define  XE_MOUSEWHEEL         9  //鼠标滚轮  wParam:标识,lParam:POINT坐标

/// @brief 鼠标左键按下事件.
/// @code  int CALLBACK OnLButtonDown(UINT nFlags, POINT *pPt,BOOL *pbHandled)  @endcode
#define  XE_LBUTTONDOWN        10

/// @brief 鼠标左键弹起事件.
/// @code  int CALLBACK OnLButtonUp(UINT nFlags, POINT *pPt,BOOL *pbHandled) @endcode
#define  XE_LBUTTONUP          11

/// @brief 鼠标右键按下事件.
/// @code  int CALLBACK OnRButtonDown(UINT nFlags, POINT *pPt,BOOL *pbHandled)  @endcode
#define  XE_RBUTTONDOWN        12

/// @brief 鼠标右键弹起事件.
/// @code int CALLBACK OnRButtonUp(UINT nFlags, POINT *pPt,BOOL *pbHandled)  @endcode
#define  XE_RBUTTONUP          13

/// @brief 鼠标左键双击事件.
/// @code   int CALLBACK OnLButtonDBClick(UINT nFlags, POINT *pPt,BOOL *pbHandled) @endcode
#define  XE_LBUTTONDBCLICK     14


//#define  XE_RBUTTONDBCLICK     15


/// @brief 炫彩定时器,非系统定时器,定时器消息 XM_TIMER.
/// @code int CALLBACK OnEleXCTimer(UINT nTimerID,BOOL *pbHandled) @endcode
/// @param hEle        元素句柄.
/// @param nTimerID    定时器ID.
#define  XE_XC_TIMER             16  //wParam:定时器ID, lParam:0

/// @brief 调整布局事件. 暂停使用
/// @code int CALLBACK OnAdjustLayout(int nFlags, UINT nAdjustNo, BOOL *pbHandled) @endcode
#define  XE_ADJUSTLAYOUT         17

/// @brief 调整布局完成事件.
/// @code int CALLBACK OnAdjustLayoutEnd(int nFlags, UINT nAdjustNo, BOOL *pbHandled) @endcode
#define  XE_ADJUSTLAYOUT_END     18

/// @brief 元素工具提示弹出事件.
/// @code int CALLBACK OnTooltipPopup(HWINDOW hWindow, const wchar_t* pText, BOOL *pbHandled) @endcode
#define  XE_TOOLTIP_POPUP        19

/// @brief 元素获得焦点事件.
/// @code int CALLBACK OnSetFocus(BOOL *pbHandled) @endcode
#define XE_SETFOCUS 31

/// @brief 元素失去焦点事件.
/// @code int CALLBACK OnKillFocus(BOOL *pbHandled) @endcode
#define  XE_KILLFOCUS          32

/// @brief 元素即将销毁事件. 在销毁子对象之前触发
/// @code int CALLBACK OnDestroy(BOOL *pbHandled) @endcode
#define  XE_DESTROY            33   //元素销毁

/// @brief 元素销毁完成事件. 在销毁子对象之后触发
/// @code int CALLBACK OnDestroyeEnd(BOOL *pbHandled) @endcode
#define  XE_DESTROY_END        42   //元素销毁

/// @brief 元素大小改变事件.
/// @code int CALLBACK OnSize(int nFlags, UINT nAdjustNo, BOOL *pbHandled) @endcode
/// @param  nFlags  adjustLayout_
#define  XE_SIZE               36

/// @brief 元素显示隐藏事件.
/// @code  int CALLBACK OnShow(BOOL bShow,BOOL *pbHandled) @endcode
#define  XE_SHOW               37  //wParam:TRUE或FALSE, lParam:0

/// @brief 元素设置字体事件.
/// @code  int CALLBACK OnSetFont(BOOL *pbHandled) @endcode
#define  XE_SETFONT           38

/// @brief 元素按键事件.
/// @code  int CALLBACK OnEventKeyDown(WPARAM wParam,LPARAM lParam,BOOL *pbHandled) @endcode
/// @note  wParam,lParam:请参见MSDN WM_KEYDOWN. 
#define  XE_KEYDOWN            39 //wParam和lParam参数与标准消息相同

/// @brief 元素按键事件.
/// @code  int CALLBACK OnEventKeyUp(WPARAM wParam,LPARAM lParam,BOOL *pbHandled) @endcode
/// @note  wParam,lParam:请参见MSDN WM_KEYDOWN. 
#define  XE_KEYUP             40 //wParam和lParam参数与标准消息相同

/// @brief 通过TranslateMessage函数翻译的字符事件.
/// @code  int CALLBACK OnEventChar(WPARAM wParam,LPARAM lParam,BOOL *pbHandled) @endcode
/// @note   wParam,lParam:请参见MSDN WM_KEYDOWN. 
#define  XE_CHAR               41  //wParam和lParam参见MSDN

#define  XE_SYSKEYDOWN     42

#define  XE_SYSKEYUP       43

/// @brief 元素设置鼠标捕获.
/// @code int CALLBACK OnSetCapture(BOOL *pbHandled) @endcode
#define  XE_SETCAPTURE      51

/// @brief 元素失去鼠标捕获.
/// @code int CALLBACK OnKillCapture(BOOL *pbHandled) @endcode
#define  XE_KILLCAPTURE     52

/// @brief 设置鼠标光标
/// @code int CALLBACK OnSetCursor(WPARAM wParam,LPARAM lParam,BOOL *pbHandled) @endcode
#define  XE_SETCURSOR            53  // SetCursor

///@brief 菜单弹出
///@code  int CALLBACK OnMenuPopup(HMENUX hMenu, BOOL *pbHandled) @endcode
#define  XE_MENU_POPUP       57

///@brief 菜单弹出窗口
///@code  int CALLBACK OnMenuPopupWnd(HMENUX hMenu,menu_popupWnd_* pInfo,BOOL *pbHandled) @endcode
#define  XE_MENU_POPUP_WND     58

/// @brief 弹出菜单项选择事件.
/// @code  int CALLBACK OnMenuSelect(int nItem,BOOL *pbHandled) @endcode
/// @param nItem          菜单项id.
#define  XE_MENU_SELECT      59  //菜单项选择 wParam:菜单ID,lParam:0

///@brief 绘制菜单背景, 启用该功能需要调用XMenu_EnableDrawBackground().
///@code  int CALLBACK OnMenuDrawBackground(HDRAW hDraw,menu_drawBackground_ *pInfo,BOOL *pbHandled) @endcode
#define  XE_MENU_DRAW_BACKGROUND   60 //绘制菜单背景

/// @brief 绘制菜单项事件, 启用该功能需要调用XMenu_EnableDrawItem().
/// @code  int CALLBACK OnMenuDrawItem(HDRAW hDraw,menu_drawItem_* pInfo,BOOL *pbHandled) @endcode
#define  XE_MENU_DRAWITEM    61  //绘制菜单项 

/// @brief 弹出菜单退出事件.
/// @code  int CALLBACK OnMenuExit(BOOL *pbHandled) @endcode
#define  XE_MENU_EXIT        62 //菜单退出

/// @brief 按钮点击事件.
/// @code int CALLBACK OnBtnClick(BOOL *pbHandled) @endcode
#define  XE_BNCLICK            34

/// @brief 按钮选中事件.
/// @code int CALLBACK OnButtonCheck(BOOL bCheck,BOOL *pbHandled) @endcode
#define  XE_BUTTON_CHECK       35  //按钮选中事件

/// @brief 滚动视图元素水平滚动事件,滚动视图触发.
/// @code  int CALLBACK OnScrollViewScrollH(int pos,BOOL *pbHandled) @endcode
/// @param pos         当前滚动点.
#define  XE_SCROLLVIEW_SCROLL_H    54  //滚动视图 滚动事件 wParam:滚动点,lParam:0 (滚动视图触发,表明滚动视图已滚动完成)

/// @brief 滚动视图元素垂直滚动事件,滚动视图触发.
/// @code  int CALLBACK OnScrollViewScrollV(int pos,BOOL *pbHandled) @endcode
/// @param pos         当前滚动点.
#define  XE_SCROLLVIEW_SCROLL_V    55  //滚动视图 滚动事件 wParam:滚动点,lParam:0 (滚动视图触发,表明滚动视图已滚动完成)

/// @brief 滚动条元素滚动事件,滚动条触发.
/// @code  int CALLBACK OnSBarScroll(int pos,BOOL *pbHandled) @endcode
/// @param pos   当前滚动点.
#define  XE_SBAR_SCROLL        56   //滚动条滚动事件 wParam:滚动点,lParam:0 (滚动条触发)

/// @brief 滑动条元素,滑块位置改变事件.
/// @code  int CALLBACK OnSliderBarChange(int pos,BOOL *pbHandled) @endcode
#define  XE_SLIDERBAR_CHANGE   63

/// @brief 进度条元素,进度改变事件.
/// @code  int CALLBACK OnProgressBarChange(int pos,BOOL *pbHandled) @endcode
#define  XE_PROGRESSBAR_CHANGE  64

/// @brief 组合框下拉列表项选择事件.
/// @code  int CALLBACK OnComboBoxSelect(int iItem,BOOL *pbHandled)  @endcode
#define  XE_COMBOBOX_SELECT       71   //组合框项选择  

/// @brief 组合框下拉列表项选择完成事件,编辑框内容已经改变.
/// @code  int CALLBACK OnComboBoxSelectEnd(int iItem,BOOL *pbHandled)  @endcode
#define  XE_COMBOBOX_SELECT_END   74   //组合框项选择  

/// @brief 组合框下拉列表弹出事件.
/// @code  int CALLBACK OnComboBoxPopupList(HWINDOW hWindow,HELE hListBox,BOOL *pbHandled)  @endcode
#define  XE_COMBOBOX_POPUP_LIST   72

/// @brief 组合框下拉列表退出事件.
/// @code  int CALLBACK OnComboBoxExitList(BOOL *pbHandled)  @endcode
#define  XE_COMBOBOX_EXIT_LIST    73

/// @brief 列表框元素-项模板创建事件, 模板复用机制需先启用; 替换模板无效判断nFlag,因为内部会检查模板是否改变,不用担心重复
/// @code int CALLBACK OnListBoxTemplateCreate(listBox_item_* pItem, int nFlag, BOOL *pbHandled) @endcode
/// @param nFlag  0:状态改变; 1:新模板实例; 2:旧模板复用 
#define  XE_LISTBOX_TEMP_CREATE     81

/// @brief 列表框元素-项模板创建完成事件,模板复用机制需先启用;不管是新建还是复用,都需要更新数据, 当为复用时不要注册事件以免重复注册
/// @code int CALLBACK OnListBoxTemplateCreateEnd(listBox_item_* pItem, int nFlag, BOOL *pbHandled) @endcode
/// @param nFlag  0:状态改变(复用); 1:新模板实例; 2:旧模板复用
#define  XE_LISTBOX_TEMP_CREATE_END     82
#define  XE_LISTBOX_TEMP_UPDATE   XE_LISTBOX_TEMP_CREATE_END

/// @brief 列表框元素,项模板销毁.
/// @code int CALLBACK OnListBoxTemplateDestroy(listBox_item_* pItem, int nFlag, BOOL *pbHandled) @endcode
/// @param  nFlag   0:正常销毁;  1:移动到缓存(不会被销毁,临时缓存备用,当需要时被复用)
#define  XE_LISTBOX_TEMP_DESTROY    83

/// @brief 列表框元素,项模板调整坐标. 已停用
/// @code  int CALLBACK OnListBoxTemplateAdjustCoordinate(listBox_item_* pItem, BOOL *pbHandled) @endcode
#define  XE_LISTBOX_TEMP_ADJUST_COORDINATE  84

/// @brief 列表框元素,项绘制事件.
/// @code  int CALLBACK OnListBoxDrawItem(HDRAW hDraw,listBox_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_LISTBOX_DRAWITEM     85

/// @brief 列表框元素,项选择事件.
/// @code  int CALLBACK OnListBoxSelect(int iItem,BOOL *pbHandled)  @endcode
#define  XE_LISTBOX_SELECT       86

/// @brief 列表元素-项模板创建事件,模板复用机制需先启用;替换模板无效判断nFlag,因为内部会检查模板是否改变,不用担心重复
/// @code  int CALLBACK OnListTemplateCreate(list_item_* pItem,int nFlag, BOOL *pbHandled) @endcode
/// @param nFlag  0:状态改变; 1:新模板实例; 2:旧模板复用 
#define  XE_LIST_TEMP_CREATE     101

/// @brief 列表元素-项模板创建完成事件,模板复用机制需先启用;不管是新建还是复用,都需要更新数据, 当为复用时不要注册事件以免重复注册
/// @code  int CALLBACK OnListTemplateCreateEnd(list_item_* pItem, int nFlag, BOOL *pbHandled) @endcode
/// @param nFlag  0:状态改变(复用); 1:新模板实例; 2:旧模板复用
#define  XE_LIST_TEMP_CREATE_END     102
#define  XE_LIST_TEMP_UPDATE  XE_LIST_TEMP_CREATE_END 

/// @brief 列表元素,项模板销毁.
/// @code int CALLBACK OnListTemplateDestroy(list_item_* pItem, int nFlag, BOOL *pbHandled) @endcode
/// @param  nFlag   0:正常销毁;  1:移动到缓存(不会被销毁,临时缓存备用,当需要时被复用)
#define  XE_LIST_TEMP_DESTROY    103

/// @brief 列表元素,项模板调整坐标. 已停用
/// @code  typedef int CALLBACK OnListTemplateAdjustCoordinate(list_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_LIST_TEMP_ADJUST_COORDINATE  104

/// @brief 列表元素,绘制项.
/// @code  int CALLBACK OnListDrawItem(HDRAW hDraw,list_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_LIST_DRAWITEM                105

/// @brief 列表元素,项选择事件.
/// @code  int CALLBACK OnListSelect(int iItem,BOOL *pbHandled) @endcode
#define  XE_LIST_SELECT                  106

/// @brief 列表元素绘制列表头项.
/// @code  int CALLBACK OnListHeaderDrawItem(HDRAW hDraw, list_header_item_* pItem, BOOL *pbHandled) @endcode
#define  XE_LIST_HEADER_DRAWITEM         107

/// @brief 列表元素,列表头项点击事件.
/// @code  int CALLBACK OnListHeaderClick(int iItem, BOOL *pbHandled) @endcode
#define  XE_LIST_HEADER_CLICK            108

/// @brief 列表元素,列表头项宽度改变事件.
/// @code  int CALLBACK OnListHeaderItemWidthChange(int iItem, int nWidth BOOL *pbHandled) @endcode
#define  XE_LIST_HEADER_WIDTH_CHANGE     109

/// @brief 列表元素,列表头项模板创建.
/// @code  int CALLBACK OnListHeaderTemplateCreate(list_header_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_LIST_HEADER_TEMP_CREATE          110

/// @brief 列表元素,列表头项模板创建完成事件.
/// @code  int CALLBACK OnListHeaderTemplateCreateEnd(list_header_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_LIST_HEADER_TEMP_CREATE_END      111

/// @brief 列表元素,列表头项模板销毁.
/// @code int CALLBACK OnListHeaderTemplateDestroy(list_header_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_LIST_HEADER_TEMP_DESTROY          112

/// @brief 列表元素,列表头项模板调整坐标. 已停用
/// @code  typedef int CALLBACK OnListHeaderTemplateAdjustCoordinate(list_header_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_LIST_HEADER_TEMP_ADJUST_COORDINATE  113


/// @brief 列表树元素-项模板创建,模板复用机制需先启用; 替换模板无效判断nFlag,因为内部会检查模板是否改变,不用担心重复
/// @code  int CALLBACK OnTreeTemplateCreate(tree_item_* pItem,int nFlag, BOOL *pbHandled) @endcode
/// @param nFlag  0:状态改变; 1:新模板实例; 2:旧模板复用 
#define  XE_TREE_TEMP_CREATE             121  

/// @brief 列表树元素-项模板创建完成,模板复用机制需先启用; 不管是新建还是复用,都需要更新数据, 当为复用时不要注册事件以免重复注册
/// @code  int CALLBACK OnTreeTemplateCreateEnd(tree_item_* pItem, int nFlag, BOOL *pbHandled) @endcode
/// @param nFlag  0:状态改变(复用); 1:新模板实例; 2:旧模板复用
#define  XE_TREE_TEMP_CREATE_END         122
#define  XE_TREE_TEMP_UPDATE   XE_TREE_TEMP_CREATE_END

/// @brief 列表树元素-项模板销毁,模板复用机制需先启用;
/// @code  int CALLBACK OnTreeTemplateDestroy(tree_item_* pItem, int nFlag, BOOL *pbHandled) @endcode
/// @param  nFlag   0:正常销毁;  1:移动到缓存(不会被销毁,临时缓存备用,当需要时被复用)
#define  XE_TREE_TEMP_DESTROY            123 

/// @brief 树元素,项模板,调整项坐标. 已停用
/// @code  int CALLBACK OnTreeTemplateAdjustCoordinate(tree_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_TREE_TEMP_ADJUST_COORDINATE  124  

/// @brief 树元素,绘制项.
/// @code  int CALLBACK OnTreeDrawItem(HDRAW hDraw,tree_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_TREE_DRAWITEM                125  

/// @brief 树元素,项选择事件.
/// @code  int CALLBACK OnTreeSelect(int nItemID,BOOL *pbHandled) @endcode
/// @param nItemID  项ID.
#define  XE_TREE_SELECT                 126

/// @brief 树元素,项展开收缩事件.
/// @code int CALLBACK OnTreeExpand(int id,BOOL bExpand,BOOL *pbHandled) @endcode
#define  XE_TREE_EXPAND                 127

/// @brief 树元素,用户正在拖动项, 可对参数值修改.
/// @code int CALLBACK OnTreeDragItemIng(tree_drag_item_* pInfo, BOOL *pbHandled) @endcode 
#define  XE_TREE_DRAG_ITEM_ING           128

/// @brief 树元素,拖动项事件.
/// @code int CALLBACK OnTreeDragItem(tree_drag_item_* pInfo, BOOL *pbHandled) @endcode 
#define  XE_TREE_DRAG_ITEM               129

/// @brief 列表视元素-项模板创建事件,模板复用机制需先启用; 替换模板无效判断nFlag,因为内部会检查模板是否改变,不用担心重复
/// @code  int CALLBACK OnListViewTemplateCreate(listView_item_* pItem,int nFlag, BOOL *pbHandled) @endcode
/// @param nFlag  0:状态改变(当前未使用); 1新模板实例; 2旧模板复用 
#define  XE_LISTVIEW_TEMP_CREATE           141

/// @brief 列表视元素-项模板创建完成事件,模板复用机制需先启用; 不管是新建还是复用,都需要更新数据, 当为复用时不要注册事件以免重复注册
/// @code  int CALLBACK OnListViewTemplateCreateEnd(listView_item_* pItem,int nFlag, BOOL *pbHandled) @endcode
/// @param nFlag  0:状态改变(复用,当前未使用); 1:新模板实例; 2:旧模板复用 
#define  XE_LISTVIEW_TEMP_CREATE_END           142
#define  XE_LISTVIEW_TEMP_UPDATE     XE_LISTVIEW_TEMP_CREATE_END

/// @brief 列表视元素-项模板销毁, 模板复用机制需先启用;
/// @code  int CALLBACK OnListViewTemplateDestroy(listView_item_* pItem, int nFlag, BOOL *pbHandled) @endcode
/// @param  nFlag   0:正常销毁;  1:移动到缓存列表(不会被销毁, 临时缓存备用, 当需要时被复用)
#define  XE_LISTVIEW_TEMP_DESTROY           143

/// @brief 列表视元素,项模板调整坐标.已停用
/// @code  int CALLBACK OnListViewTemplateAdjustCoordinate(listView_item_* pItem,BOOL *pbHandled) @endcode
#define  XE_LISTVIEW_TEMP_ADJUST_COORDINATE   144

/// @brief 列表视元素,自绘项.
/// @code int CALLBACK OnListViewDrawItem(HDRAW hDraw,listView_item_* pItem,BOOL *pbHandled)  @endcode
#define  XE_LISTVIEW_DRAWITEM              145

/// @brief 列表视元素,项选择事件.
/// @code int CALLBACK OnListViewSelect(int iGroup,int iItem,BOOL *pbHandled) @endcode
#define  XE_LISTVIEW_SELECT            146

/// @brief 列表视元素,组展开收缩事件.
/// @code int CALLBACK OnListViewExpand(int iGroup,BOOL bExpand,BOOL *pbHandled) @endcode
#define  XE_LISTVIEW_EXPAND         147

/// @brief 属性网格元素 项值改变事件
/// @code   int CALLBACK OnPGridValueChange(int nItemID,BOOL *pbHandled) @endcode
/// @param  nItemID  项ID.
#define  XE_PGRID_VALUE_CHANGE     151

/// @code int CALLBACK OnPGridItemSet(int nItemID, BOOL *pbHandled)  @endcode
#define  XE_PGRID_ITEM_SET          152

/// @code int CALLBACK OnPGridItemSelect(int nItemID, BOOL *pbHandled)  @endcode
#define  XE_PGRID_ITEM_SELECT         153  //项选择

/// @code int CALLBACK OnPGridItemAdjustCoordinate(propertyGrid_item_* pItem, BOOL *pbHandled)  @endcode
#define  XE_PGRID_ITEM_ADJUST_COORDINATE  154

/// @code int CALLBACK OnPGridItemDestroy(int nItemID, BOOL *pbHandled)  @endcode
#define  XE_PGRID_ITEM_DESTROY   155

/// @code int CALLBACK OnPGridItemExpand(int nItemID, BOOL bExpand, BOOL *pbHandled) @endcode
#define  XE_PGRID_ITEM_EXPAND    156


/// @code int CALLBACK OnEditSet(BOOL *pbHandled)  @endcode
#define  XE_EDIT_SET           180

/// @code int CALLBACK OnEditDrawRow(HDRAW hDraw, int iRow, BOOL *pbHandled)  @endcode
#define  XE_EDIT_DRAWROW    181   //暂未使用

/// @code int CALLBACK OnEditChanged(BOOL *pbHandled)  @endcode
#define  XE_EDIT_CHANGED   182  //内容被更改

/// @code int CALLBACK OnEditPosChanged(int iPos, BOOL *pbHandled)  @endcode
#define  XE_EDIT_POS_CHANGED    183  //位置改变

/// @code int CALLBACK OnEditStyleChanged(int iStyle, BOOL *pbHandled)  @endcode
#define  XE_EDIT_STYLE_CHANGED  184  //样式改变

/// @code int CALLBACK OnEditEnterGetTabAlign(BOOL *pbHandled)  @endcode
#define  XE_EDIT_ENTER_GET_TABALIGN    185  //回车TAB对齐,返回需要TAB数量

/// @code int CALLBACK OnEditSwapRow(int iRow, int bArrowUp, BOOL *pbHandled)  @endcode
#define  XE_EDIT_SWAPROW     186     //交换行

/// @brief 多行内容改变事件 例如:区块注释操作, 区块缩进操作, 代码格式化
/// @code int CALLBACK OnEditChangeRows(int iRow, int nRows, BOOL *pbHandled)  @endcode
/// @param iRow   开始行
/// @param nRows  改变行数量
#define  XE_EDITOR_MODIFY_ROWS         190  //多行内容修改事件

/// @code int CALLBACK OnEditorSetBreakpoint(int iRow, BOOL bCheck, BOOL *pbHandled)  @endcode
#define  XE_EDITOR_SETBREAKPOINT       191 //设置断点

/// @code int CALLBACK OnEditorRemoveBreakpoint(int iRow, BOOL *pbHandled)  @endcode
#define  XE_EDITOR_REMOVEBREAKPOINT    192 //移除断点

// iRow: 更改行开始位置索引,  if(nChangeRows>0) iEnd= iRow + nChangeRows
// nChangeRows: 改变行数, 正数添加行, 负数删除行
/// @code int CALLBACK OnEditorBreakpointChanged(int iRow, int nChangeRows, BOOL *pbHandled)  @endcode
#define  XE_EDIT_ROW_CHANGED  193 //可对断点位置修改

/// @code int CALLBACK OnEditorAutoMatchSelect(int iRow, int nRows, BOOL *pbHandled)  @endcode
#define  XE_EDITOR_AUTOMATCH_SELECT  194

/// @brief  TabBar标签按钮选择改变事件
/// @code   int CALLBACK OnTabBarSelect(int iItem, BOOL *pbHandled) @endcode
/// @param  iItem  标签位置索引.
#define  XE_TABBAR_SELECT    221

/// @brief  TabBar标签按钮删除事件
/// @code   int CALLBACK OnTabBarDelete(int iItem, BOOL *pbHandled) @endcode
/// @param  iItem  标签位置索引.
#define  XE_TABBAR_DELETE    222

/// @brief  月历元素日期改变事件
/// @code   int CALLBACK OnCalendarChange(BOOL *pbHandled) @endcode
#define  XE_MONTHCAL_CHANGE   231   //月历 日期改变事件

/// @brief  日期时间元素,内容改变事件
/// @code   int CALLBACK OnDateTimeChange(BOOL *pbHandled) @endcode
#define  XE_DATETIME_CHANGE    241   //日期时间元素  改变事件

/// @brief  日期时间元素,弹出月历卡片事件
/// @code   int CALLBACK OnDateTimePopupMonthCal(HWINDOW hMonthCalWnd,HELE hMonthCal,BOOL *pbHandled) @endcode
#define  XE_DATETIME_POPUP_MONTHCAL     242   //日期时间元素  弹出月历事件

/// @brief  日期时间元素,弹出的月历卡片退出事件
/// @code   int CALLBACK OnDateTimeExitMonthCal(HWINDOW hMonthCalWnd,HELE hMonthCal,BOOL *pbHandled) @endcode
#define  XE_DATETIME_EXIT_MONTHCAL      243   //日期时间元素  退出月历事件

/// @brief  文件拖放事件, 需先启用:XWnd_EnableDragFiles()
/// @code   int CALLBACK OnDropFiles(HDROP hDropInfo, BOOL *pbHandled) @endcode
#define  XE_DROPFILES                 250  

//#define  XE_LISTVIEW_DRAG_INSERT
//#define  XE_PANE_LOACK
//#define  XE_PANE_DOCK
//#define  XE_PANE_FLOAT

/// @code   int CALLBACK OnEditColorChange(COLORREF color, BOOL *pbHandled) @endcode
#define  XE_EDIT_COLOR_CHANGE        260
///@}


//////////////////////////////////////////////////////////////////
//////////////////枚举定义/////////////////////////////////////////
//////////////////////////////////////////////////////////////////

/// @defgroup  group_enum   枚举类型
/// @{

/// @defgroup groupWindow_position 窗口位置(window_position_)
/// @{
enum   window_position_
{
	window_position_error = -1,  ///<错误
	window_position_top = 0,     ///<top
	window_position_bottom,    ///<bottom
	window_position_left,      ///<left
	window_position_right,     ///<right
	window_position_body,      ///<body
	window_position_window,    ///<window 整个窗口 
};
///@}

/// @defgroup groupElement_position UI元素位置(element_position_)
/// @{
enum element_position_
{
	element_position_no = 0x00,     ///<无效
	element_position_left = 0x01,     ///<左边
	element_position_top = 0x02,		///<上边
	element_position_right = 0x04,		///<右边
	element_position_bottom = 0X08,		///<下边
};
///@}

/// @defgroup group_position 位置标识(element_position_)
/// @{
enum position_flag_
{
	position_flag_left,          ///<左
	position_flag_top,           ///<上
	position_flag_right,         ///<右
	position_flag_bottom,        ///<下
	position_flag_leftTop,       ///<左上角
	position_flag_leftBottom,    ///<左下角
	position_flag_rightTop,      ///<右上角
	position_flag_rightBottom,   ///<右下角
	position_flag_center,        ///<中心
};
///@}

//透明窗口
/// @defgroup groupWindowTransparent 炫彩窗口透明标识(window_transparent_)
/// @{
enum  window_transparent_
{
	window_transparent_false = 0,   ///<默认窗口,不透明
	window_transparent_shaped,    ///<透明窗口,带透明通道,异型
	window_transparent_shadow,    ///<阴影窗口,带透明通道,边框阴影,窗口透明或半透明
	window_transparent_simple,    ///<透明窗口,不带透明通道,指定半透明度,指定透明色
	window_transparent_win7,      ///<WIN7玻璃窗口,需要WIN7开启特效,当前未启用,当前未启用.
};
///@}


/// @defgroup groupMenu 弹出菜单(menu)
/// @{

///@name 弹出菜单项标识(menu_item_flag_)
///@{
enum   menu_item_flag_
{
	menu_item_flag_normal = 0x00,   ///<正常
	menu_item_flag_select = 0x01,   ///<选择或鼠标停留
	menu_item_flag_stay = 0x01,   ///<选择或鼠标停留 等于 menu_item_flag_select
	menu_item_flag_check = 0x02,   ///<勾选
	menu_item_flag_popup = 0x04,   ///<弹出
	menu_item_flag_separator = 0x08,   ///<分隔栏 ID号任意,ID号被忽略
	menu_item_flag_disable = 0x10,   ///<禁用
};
///@}

///@name 弹出菜单方向(menu_popup_position_)
///@{
enum  menu_popup_position_
{
	menu_popup_position_left_top = 0,      ///<左上角
	menu_popup_position_left_bottom,     ///<左下角
	menu_popup_position_right_top,       ///<右上角
	menu_popup_position_right_bottom,    ///<右下角
	menu_popup_position_center_left,     ///<左居中
	menu_popup_position_center_top,      ///<上居中
	menu_popup_position_center_right,    ///<右居中
	menu_popup_position_center_bottom,   ///<下居中
};
///@}
///@}

/// @defgroup groupImageDrawType 图片绘制类型(image_draw_type_)
/// @{
enum  image_draw_type_
{
	image_draw_type_default = 0,     ///<默认
	image_draw_type_stretch,       ///<拉伸
	image_draw_type_adaptive,      ///<自适应,九宫格
	image_draw_type_tile,          ///<平铺
	image_draw_type_fixed_ratio,   ///<固定比例,当图片超出显示范围时,按照原始比例压缩显示图片
	image_draw_type_adaptive_border,  ///<九宫格不绘制中间区域
};
///@}


//状态--------------------------------------
/// @defgroup groupCommonState3 普通三种状态(common_state3_)
/// @{
enum  common_state3_
{
	common_state3_leave = 0,  ///<离开
	common_state3_stay,     ///<停留
	common_state3_down,     ///<按下
};

///@}

/// @defgroup groupButtonStateFlag 按钮状态(button_state_)
/// @{
enum  button_state_
{
	button_state_leave = 0,   ///<离开状态
	button_state_stay,      ///<停留状态
	button_state_down,      ///<按下状态
	button_state_check,     ///<选中状态
	button_state_disable,   ///<禁用状态
};
///@}

/// @defgroup   groupComboBoxState 组合框状态(comboBox_state_)
/// @{
enum  comboBox_state_
{
	comboBox_state_leave = 0,   ///<鼠标离开状态
	comboBox_state_stay = 1,    ///<鼠标停留状态
	comboBox_state_down = 2,    ///<按下状态
};
///@}

/// @defgroup groupListItemState 列表项状态(list_item_state_)
/// 适用于(列表,列表框,列表视图)
/// @{
enum  list_item_state_
{
	list_item_state_leave = 0,   ///<项鼠标离开状态
	list_item_state_stay = 1,    ///<项鼠标停留状态
	list_item_state_select = 2,  ///<项选择状态
	list_item_state_cache = 3,   ///<缓存的项
};
///@}


/// @defgroup groupTreeItemState  列表树项状态(tree_item_state_)
/// @{
enum  tree_item_state_
{
	tree_item_state_leave = 0,   ///<项鼠标离开状态
	tree_item_state_stay = 1,    ///<项鼠标停留状态
	tree_item_state_select = 2,  ///<项选择状态
};
///@}


//按钮图标对齐方式
/// @defgroup groupButtonIconAlign 按钮图标对齐方式(button_icon_align_)
/// @{
enum  button_icon_align_
{
	button_icon_align_left = 0,  ///<图标在左边
	button_icon_align_top,     ///<图标在顶部
	button_icon_align_right,   ///<图标在右边
	button_icon_align_bottom,  ///<图标在底部
};
///@}

/// @defgroup  groupListDrawItemBkFlag  项背景绘制标志位(List,ListBox,ListView,Tree)
/// @{
enum  list_drawItemBk_flag_
{
	list_drawItemBk_flag_nothing = 0x000,     ///<不绘制
	list_drawItemBk_flag_leave = 0x001,       ///<绘制鼠标离开状态项背景
	list_drawItemBk_flag_stay = 0x002,        ///<绘制鼠标选择状态项背景
	list_drawItemBk_flag_select = 0x004,      ///<绘制鼠标停留状态项项背景
	list_drawItemBk_flag_group_leave = 0x008, ///<绘制鼠标离开状态组背景,当项为组时
	list_drawItemBk_flag_group_stay = 0x010,  ///<绘制鼠标停留状态组背景,当项为组时

	list_drawItemBk_flag_line = 0x020,        ///<列表绘制水平分割线
	list_drawItemBk_flag_lineV = 0x040,        ///<列表绘制垂直分割线

};
/// @}

//弹出消息框类型
/// @defgroup groupMessageBox 弹出消息框(messageBox_flag_)
/// @{
enum  messageBox_flag_
{
	messageBox_flag_other = 0x00,    ///<其他
	messageBox_flag_ok = 0x01,    ///<确定按钮
	messageBox_flag_cancel = 0x02,    ///<取消按钮

	messageBox_flag_icon_appicon = 0x01000,  ///<图标 应用程序  IDI_APPLICATION
	messageBox_flag_icon_info = 0x02000,  ///<图标 信息     IDI_ASTERISK
	messageBox_flag_icon_qustion = 0x04000,  ///<图标 问询/帮助/提问   IDI_QUESTION
	messageBox_flag_icon_error = 0x08000,  ///<图标 错误/拒绝/禁止  IDI_ERROR
	messageBox_flag_icon_warning = 0x10000,  ///<图标 警告       IDI_WARNING
	messageBox_flag_icon_shield = 0x20000,  ///<图标 盾牌/安全   IDI_SHIELD
};
///@}

///@defgroup GroupPropertyGrid_item_type    属性网格项类型(propertyGrid_item_type_)
///@{
enum  propertyGrid_item_type_
{
	propertyGrid_item_type_text = 0,      ///<默认,字符串类型
	propertyGrid_item_type_edit,        ///<编辑框
	propertyGrid_item_type_edit_color,  ///<颜色选择元素
	propertyGrid_item_type_edit_file,   ///<文件选择编辑框
	propertyGrid_item_type_edit_set,    ///<设置
	propertyGrid_item_type_comboBox,    ///<组合框
	propertyGrid_item_type_group,       ///<组
	propertyGrid_item_type_panel,       ///<面板
};
///@}

///@defgroup  GroupZOrder    Z序位置(zorder_)
///@{
enum zorder_
{
	zorder_top,    ///<最上面
	zorder_bottom, ///<最下面
	zorder_before, ///<指定目标下面
	zorder_after,  ///<指定目标上面
};
///@}

///@defgroup Group_pane_align_  窗格对齐(pane_align_)
///@{
enum pane_align_
{
	pane_align_error = -1,  ///<错误
	pane_align_left = 0,    ///<左侧
	pane_align_top,       ///<顶部
	pane_align_right,     ///<右侧
	pane_align_bottom,    ///<底部
	pane_align_center,    ///<居中
};
///@}

///@defgroup Group_layout_align_  布局对齐(layout_align_)
///@{
enum  layout_align_
{
	layout_align_left = 0,		  ///<左侧
	layout_align_top,			  ///<顶部
	layout_align_right,			  ///<右侧
	layout_align_bottom,		  ///<底部
	layout_align_center,		  ///<居中
	layout_align_equidistant,     ///<等距
};
///@}

/// @defgroup groupLayoutSize 布局大小类型(layout_size_)
/// @{
enum  layout_size_
{
	layout_size_fixed = 0, ///<固定大小
	layout_size_fill,      ///<fill 填充父
	layout_size_auto,      ///<auto 自动大小,根据内容计算大小
	layout_size_weight,    ///<weight 比例,按照比例分配剩余空间
	layout_size_percent,   ///<百分比
	layout_size_disable,   ///<disable 不使用
};
///@}

/// @defgroup  groupLayoutAlignAxis 布局轴对齐(layout_align_axis_)
/// @{
enum layout_align_axis_
{
	layout_align_axis_auto = 0,   ///<无
	layout_align_axis_start,      ///<水平布局(顶部), 垂直布局(左侧)
	layout_align_axis_center,     ///<居中
	layout_align_axis_end,        ///<水平布局(底部), 垂直布局(右侧)
};
///@}

///@defgroup Group_edit_textAlign_flag_  编辑框文本对齐(edit_textAlign_flag_)
///@{
enum edit_textAlign_flag_
{
	edit_textAlign_flag_left = 0x0,   ///<左侧
	edit_textAlign_flag_right = 0x1,   ///<右侧
	edit_textAlign_flag_center = 0x2,   ///<水平居中

	edit_textAlign_flag_top = 0x0,  ///<顶部
	edit_textAlign_flag_bottom = 0x4,  ///<底部
	edit_textAlign_flag_center_v = 0x8,  ///<垂直居中
};
///@}

///@defgroup Group_pane_state_  窗格状态(pane_state_)
///@{
enum pane_state_
{
	pane_state_error = -1,
	pane_state_any = 0,
	pane_state_lock,   ///<锁定
	pane_state_dock,   ///<停靠码头
	pane_state_float,  ///<浮动窗格
};
///@}

///@defgroup Group_textFormatFlag_    文本对齐(textFormatFlag_)
///@{
enum  textFormatFlag_
{
	textAlignFlag_left = 0,      ///<左对齐
	textAlignFlag_top = 0,      ///<垂直顶对齐
	textAlignFlag_left_top = 0x4000, ///<内部保留
	textAlignFlag_center = 0x1,    ///<水平居中
	textAlignFlag_right = 0x2,    ///<右对齐.

	textAlignFlag_vcenter = 0x4,    ///<垂直居中
	textAlignFlag_bottom = 0x8,    ///<垂直底对齐

	textFormatFlag_DirectionRightToLeft = 0x10,   ///<从右向左顺序显示文本
	textFormatFlag_NoWrap = 0x20,   ///<禁止换行
	textFormatFlag_DirectionVertical = 0x40,   ///<垂直显示文本
	textFormatFlag_NoFitBlackBox = 0x80,   ///<允许部分字符延伸该字符串的布局矩形。默认情况下，将重新定位字符以避免任何延伸
	textFormatFlag_DisplayFormatControl = 0x100,  ///<控制字符（如从左到右标记）随具有代表性的标志符号一起显示在输出中。
	textFormatFlag_NoFontFallback = 0x200,      ///<对于请求的字体中不支持的字符，禁用回退到可选字体。缺失的任何字符都用缺失标志符号的字体显示，通常是一个空的方块
	textFormatFlag_MeasureTrailingSpaces = 0x400, ///<包括每一行结尾处的尾随空格。在默认情况下，MeasureString 方法返回的边框都将排除每一行结尾处的空格。设置此标记以便在测定时将空格包括进去
	textFormatFlag_LineLimit = 0x800,      ///<如果内容显示高度不够一行,那么不显示
	textFormatFlag_NoClip = 0x1000,     ///<允许显示标志符号的伸出部分和延伸到边框外的未换行文本。在默认情况下，延伸到边框外侧的所有文本和标志符号部分都被剪裁

	textTrimming_None = 0,        ///<不使用去尾
	textTrimming_Character = 0x40000,  ///<以字符为单位去尾
	textTrimming_Word = 0x80000,  ///<以单词为单位去尾
	textTrimming_EllipsisCharacter = 0x8000,   ///<以字符为单位去尾,省略部分使用且略号表示
	textTrimming_EllipsisWord = 0x10000,  ///<以单词为单位去尾,
	textTrimming_EllipsisPath = 0x20000,  ///<略去字符串中间部分，保证字符的首尾都能够显示  
};
///@}

///@defgroup Group_textFormatFlag_dwrite_    D2D文本渲染模式(XC_DWRITE_RENDERING_MODE)
///@{
enum XC_DWRITE_RENDERING_MODE
{
	XC_DWRITE_RENDERING_MODE_DEFAULT = 0,                    ///<指定根据字体和大小自动确定呈现模式。
	XC_DWRITE_RENDERING_MODE_ALIASED,						 ///<指定不执行抗锯齿。 每个像素要么设置为文本的前景色，要么保留背景的颜色。
	XC_DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC,			 ///<使用与别名文本相同的度量指定 ClearType 呈现。 字形只能定位在整个像素的边界上。
	XC_DWRITE_RENDERING_MODE_CLEARTYPE_GDI_NATURAL,			 ///<使用使用 CLEARTYPE_NATURAL_QUALITY 创建的字体，使用与使用 GDI 的文本呈现相同的指标指定 ClearType 呈现。 与使用别名文本相比，字形度量更接近其理想值，但字形仍然位于整个像素的边界上。
	XC_DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL,				 ///<仅在水平维度中指定具有抗锯齿功能的 ClearType 渲染。这通常用于中小字体大小（最多 16 ppem）。
	XC_DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL_SYMMETRIC,	 ///<指定在水平和垂直维度上具有抗锯齿的 ClearType 渲染。这通常用于较大的尺寸，以使曲线和对角线看起来更平滑，但会牺牲一些柔和度。
	XC_DWRITE_RENDERING_MODE_OUTLINE,                        ///<指定渲染应绕过光栅化器并直接使用轮廓。 这通常用于非常大的尺寸。
};
///@}

///@defgroup Group_listItemTemp_type_    列表项模板类型(listItemTemp_type_)
///@{
enum listItemTemp_type_
{
	listItemTemp_type_tree = 0x01,					  ///<tree
	listItemTemp_type_listBox = 0x02,				  ///<listBox
	listItemTemp_type_list_head = 0x04,				  ///<list 列表头
	listItemTemp_type_list_item = 0x08,				  ///<list 列表项
	listItemTemp_type_listView_group = 0x10,		  ///<listView 列表视组
	listItemTemp_type_listView_item = 0x20,			  ///<listView 列表视项
	listItemTemp_type_list = listItemTemp_type_list_head | listItemTemp_type_list_item,  ///<list (列表头)与(列表项)组合
	listItemTemp_type_listView = listItemTemp_type_listView_group | listItemTemp_type_listView_item, ///<listView (列表视组)与(列表视项)组合
};
///@}

///@defgroup Group_adjustLayout    调整布局标识位(adjustLayout_)
///@{
enum adjustLayout_
{
	adjustLayout_no = 0x00,  ///<不调整布局
	adjustLayout_all = 0x01,  ///<强制调整自身和子对象布局.
	adjustLayout_self = 0x02,  ///<只调整自身布局,不调整子对象布局.
	//xc_adjustLayout_free = 0x03   调整布局,非强制性, 只调整坐标改变的对象
};
///@}

/// @defgroup group_edit_macro 编辑框类型(edit_type_)
/// @{
enum edit_type_
{
	edit_type_none = 0,   ///<普通编辑框,   每行的高度相同
	edit_type_editor,     ///<代码编辑框,   每行的高度相同,  功能继承普通编辑框
	edit_type_richedit,   ///<富文本编辑框,  每行的高度可能不同
	edit_type_chat,       ///<聊天气泡,     每行的高度可能不同, 功能继承富文本编辑框
	edit_type_codeTable,  ///<代码表格,内部使用,  每行的高度相同, 未使用
};

enum edit_style_type_
{
	edit_style_type_font_color = 1,  ///<字体
	edit_style_type_image,           ///<图片
	edit_style_type_obj,             ///<UI对象
};

///Edit 聊天气泡对齐方式
enum chat_flag_
{
	chat_flag_left = 0x1,    ///<左侧
	chat_flag_right = 0x2,   ///<右侧
	chat_flag_center = 0x4,  ///<中间
	chat_flag_next_row_bubble = 0x8,   ///<下一行显示气泡
};
///@}

/// @defgroup group_table  形状表格标识(table_flag_)
/// @{

///@name  形状表格标识(table_flag_)
///@{
enum  table_flag_
{
	table_flag_full = 0,   ///<铺满组合单元格
	table_flag_none,       ///<正常最小单元格
};
///@}

///@name  形状表格线标识(table_line_flag_)
///@{
enum  table_line_flag_
{
	table_line_flag_left = 0x1,   ///<待补充
	table_line_flag_top = 0x2,   ///<待补充
	table_line_flag_right = 0x4,	 ///<待补充
	table_line_flag_bottom = 0x8,   ///<待补充
	table_line_flag_left2 = 0x10,  ///<待补充
	table_line_flag_top2 = 0x20,	 ///<待补充
	table_line_flag_right2 = 0x40,	 ///<待补充
	table_line_flag_bottom2 = 0x80,	 ///<待补充
};
///@}
///@}

/// @defgroup group_monthCal_button_type_    月历元素上的按钮类型(monthCal_button_type_)
/// @{
enum monthCal_button_type_
{
	monthCal_button_type_today = 0,  ///< 今天按钮
	monthCal_button_type_last_year,  ///< 上一年
	monthCal_button_type_next_year,  ///< 下一年
	monthCal_button_type_last_month, ///< 上一月
	monthCal_button_type_next_month, ///< 下一月
};
///@}

///@defgroup  group_fontStyle_  字体样式(fontStyle_)
///@{
enum fontStyle_
{
	fontStyle_regular = 0,     ///<正常
	fontStyle_bold = 1,        ///<粗体
	fontStyle_italic = 2,      ///<斜体
	fontStyle_boldItalic = 3,  ///<粗斜体
	fontStyle_underline = 4,   ///<下划线
	fontStyle_strikeout = 8    ///<删除线
};
///@}

///@defgroup  group_adapter_date_type_    数据适配器数据类型(adapter_date_type_)
///@{
enum  adapter_date_type_
{
	adapter_date_type_error = -1,
	adapter_date_type_int = 0,     ///<整形
	adapter_date_type_float = 1,   ///<浮点型
	adapter_date_type_string = 2,  ///<字符串
	adapter_date_type_image = 3,   ///<图片
};
///@}

/// @defgroup group_ease_type_  缓动类型(ease_type_)
/// @{
enum ease_type_
{
	easeIn,      ///<从慢到快
	easeOut,     ///<从快到慢
	easeInOut,   ///<从慢到快再到慢
};
///@}

///@defgroup   group_ease_flag_  缓动标识(ease_flag_)
///@{
enum ease_flag_
{
	ease_flag_linear,			///<线性, 直线
	ease_flag_quad,			    ///<二次方曲线
	ease_flag_cubic,			///<三次方曲线, 圆弧
	ease_flag_quart,			///<四次方曲线
	ease_flag_quint,			///<五次方曲线

	ease_flag_sine,				///<正弦, 在末端变化
	ease_flag_expo,			    ///<突击, 突然一下
	ease_flag_circ,		        ///<圆环, 好比绕过一个圆环
	ease_flag_elastic,		    ///<强力回弹
	ease_flag_back,				///<回弹, 比较缓慢
	ease_flag_bounce,		    ///<弹跳, 模拟小球落地弹跳

	ease_flag_in = 0x010000, ///<从慢到快
	ease_flag_out = 0x020000, ///<从快到慢
	ease_flag_inOut = 0x030000, ///<从慢到快再到慢
};
///@}

///@defgroup   group_notifyMsg_skin_  通知消息外观(notifyMsg_skin_)
///@{
enum  notifyMsg_skin_
{
	notifyMsg_skin_no,         ///<默认
	notifyMsg_skin_success,    ///<成功
	notifyMsg_skin_warning,	   ///<警告
	notifyMsg_skin_message,	   ///<消息
	notifyMsg_skin_error,	   ///<错误
};
///@}

///@defgroup group_animation_move_  动画移动标识(animation_move_)
///@{
enum animation_move_
{
	animation_move_x = 0x01,   ///<X轴移动
	animation_move_y = 0x02,   ///<Y轴移动
};
///@}

///@defgroup group_bkInfo_align_flag_  背景对象对齐方式(bkObject_align_flag_)
///@{
enum bkObject_align_flag_  //背景对象对齐方式
{
	bkObject_align_flag_no = 0x000,    ///<无
	bkObject_align_flag_left = 0x001,    ///<左对齐, 当设置此标识时,外间距(margin.left)代表左侧间距; 当right未设置时,那么外间距(margin.right)代表宽度;
	bkObject_align_flag_top = 0x002,    ///<顶对齐, 当设置此标识时,外间距(margin.top)代表顶部间距; 当bottom未设置时,那么外间距(margin.bottom)代表高度;
	bkObject_align_flag_right = 0x004,    ///<右对齐, 当设置此标识时,外间距(margin.right)代表右侧间距; 当left未设置时,那么外间距(margin.left)代表宽度;
	bkObject_align_flag_bottom = 0x008,    ///<底对齐, 当设置此标识时,外间距(margin.bottom)代表底部间距; 当top未设置时,那么外间距(margin.top)代表高度;
	bkObject_align_flag_center = 0x010,    ///<水平居中, 当设置此标识时,外间距(margin.left)代表宽度;
	bkObject_align_flag_center_v = 0x020,  ///<垂直居中, 当设置此标识时,外间距(margin.top)代表高度; 
};
///@}


///@defgroup group_frameWnd_cell_type_  框架窗口单元格类型(frameWnd_cell_type_)
enum frameWnd_cell_type_
{
	frameWnd_cell_type_no = 0,   ///<无
	frameWnd_cell_type_pane = 1,   ///<窗格
	frameWnd_cell_type_group = 2,   ///<窗格组
	frameWnd_cell_type_bodyView = 3,   ///<主视图区
	frameWnd_cell_type_top_bottom = 4,   ///<上下布局
	frameWnd_cell_type_left_right = 5,   ///<左右布局
};


///@}

/////////////////////////////////////////////////////////////////////
//////////////炫彩组合状态/////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/// @defgroup group_combo_StateFlag  组合状态
/// @{

///@defgroup group_window_state_flag_  窗口状态(window_state_flag_)
///@{
enum  window_state_flag_
{
	window_state_flag_nothing = 0x0000,  ///<无
	window_state_flag_leave = 0x0001,  ///<整个窗口
	window_state_flag_body_leave = 0x0002,  ///<窗口-body
	window_state_flag_top_leave = 0x0004,  ///<窗口-top
	window_state_flag_bottom_leave = 0x0008,  ///<窗口-bottom
	window_state_flag_left_leave = 0x0010,  ///<窗口-left
	window_state_flag_right_leave = 0x0020,  ///<窗口-right

	window_state_flag_layout_body = 0x20000000, ///<布局内容区
};
///@}

///@defgroup  group_element_state_flag_ 元素状态(element_state_flag_)
///@{
enum  element_state_flag_
{
	element_state_flag_nothing = window_state_flag_nothing,  ///<无
	element_state_flag_enable = 0x0001,  ///<启用
	element_state_flag_disable = 0x0002,  ///<禁用
	element_state_flag_focus = 0x0004,  ///<焦点
	element_state_flag_focus_no = 0x0008,  ///<无焦点
	element_state_flag_focusEx = 0x40000000,  ///<该元素或该元素的子元素拥有焦点
	element_state_flag_focusEx_no = 0x80000000,  ///<无焦点Ex

	layout_state_flag_layout_body = window_state_flag_layout_body, ///<布局内容区

	element_state_flag_leave = 0x0010,  ///<鼠标离开
	element_state_flag_stay = 0x0020,  ///<为扩展模块保留
	element_state_flag_down = 0x0040,  ///<为扩展模块保留
};
///@}

///@defgroup  group_button_state_flag_ 按钮状态(button_state_flag_)
///@{
enum  button_state_flag_
{
	button_state_flag_leave = element_state_flag_leave,  ///<鼠标离开
	button_state_flag_stay = element_state_flag_stay,   ///<鼠标停留
	button_state_flag_down = element_state_flag_down,   ///<鼠标按下

	button_state_flag_check = 0x0080, ///<选中
	button_state_flag_check_no = 0x0100, ///<未选中

	button_state_flag_WindowRestore = 0x0200, ///<窗口还原
	button_state_flag_WindowMaximize = 0x0400, ///<窗口最大化
};
///@}

///@defgroup   group_comboBox_state_flag_  组合框状态(comboBox_state_flag_)
///@{
enum comboBox_state_flag_
{
	comboBox_state_flag_leave = element_state_flag_leave, ///<鼠标离开
	comboBox_state_flag_stay = element_state_flag_stay,  ///<鼠标停留
	comboBox_state_flag_down = element_state_flag_down,  ///<鼠标按下
};
///@}

///@defgroup   group_listBox_state_flag_  列表框状态(listBox_state_flag_)
///@{
enum listBox_state_flag_
{
	listBox_state_flag_item_leave = 0x0080, ///<项鼠标离开
	listBox_state_flag_item_stay = 0x0100, ///<项鼠标停留

	listBox_state_flag_item_select = 0x0200, ///<项选择
	listBox_state_flag_item_select_no = 0x0400, ///<项未选择
};
///@}

///@defgroup   group_list_state_flag_  列表状态(list_state_flag_)
///@{
enum list_state_flag_
{
	list_state_flag_item_leave = 0x0080, ///<项鼠标离开
	list_state_flag_item_stay = 0x0100, ///<项鼠标停留

	list_state_flag_item_select = 0x0200, ///<项选择
	list_state_flag_item_select_no = 0x0400, ///<项未选择
};
///@}

///@defgroup   group_listHeader_state_flag_  列表头状态(listHeader_state_flag_)
///@{
enum listHeader_state_flag_
{
	listHeader_state_flag_item_leave = 0x0080, ///<项鼠标离开
	listHeader_state_flag_item_stay = 0x0100, ///<项鼠标停留
	listHeader_state_flag_item_down = 0x0200, ///<项鼠标按下
};
///@}

///@defgroup   group_listView_state_flag_ 列表视图状态(listView_state_flag_)
///@{
enum listView_state_flag_
{
	listView_state_flag_item_leave = 0x0080,  ///<项鼠标离开
	listView_state_flag_item_stay = 0x0100,  ///<项鼠标停留

	listView_state_flag_item_select = 0x0200,  ///<项选择
	listView_state_flag_item_select_no = 0x0400,  ///<项未选择

	listView_state_flag_group_leave = 0x0800,  ///<组鼠标离开
	listView_state_flag_group_stay = 0x1000,  ///<组鼠标停留

	listView_state_flag_group_select = 0x2000,  ///<组选择
	listView_state_flag_group_select_no = 0x4000,  ///<组未选择
};
///@}

///@defgroup   group_tree_state_flag_ 列表树状态(tree_state_flag_)
///@{
enum tree_state_flag_
{
	tree_state_flag_item_leave = 0x0080,  ///<项鼠标离开
	tree_state_flag_item_stay = 0x0100,  ///<项鼠标停留,保留值, 暂未使用

	tree_state_flag_item_select = 0x0200,  ///<项选择
	tree_state_flag_item_select_no = 0x0400,  ///<项未选择

	tree_state_flag_group = 0x0800,  ///<项为组
	tree_state_flag_group_no = 0x1000,  ///<项不为组
};
///@}

///@defgroup   group_monthCal_state_flag_  月历卡片状态(monthCal_state_flag_)
///@{
enum monthCal_state_flag_
{
	monthCal_state_flag_leave = element_state_flag_leave,  ///<离开状态

	monthCal_state_flag_item_leave = 0x0080,     ///< 项-离开
	monthCal_state_flag_item_stay = 0x0100,     ///< 项-停留
	monthCal_state_flag_item_down = 0x0200,     ///< 项-按下

	monthCal_state_flag_item_select = 0x0400,     ///< 项-选择
	monthCal_state_flag_item_select_no = 0x0800,     ///< 项-未选择

	monthCal_state_flag_item_today = 0x1000,     ///< 项-今天
	//	monthCal_state_flag_item_other      = 0x2000,     ///< 项-上月及下月
	monthCal_state_flag_item_last_month = 0x2000,     ///< 项-上月
	monthCal_state_flag_item_cur_month = 0x4000,     ///< 项-当月
	monthCal_state_flag_item_next_month = 0x8000,     ///< 项-下月
};
///@}

///@defgroup   group_propertyGrid_state_flag_  属性网格状态(propertyGrid_state_flag_)
///@{
enum propertyGrid_state_flag_
{
	propertyGrid_state_flag_item_leave = 0x0080,  	 ///<离开
	propertyGrid_state_flag_item_stay = 0x0100,	 ///<停留

	propertyGrid_state_flag_item_select = 0x0200,	 ///<选择
	propertyGrid_state_flag_item_select_no = 0x0400,	 ///<未选择

	propertyGrid_state_flag_group_leave = 0x0800,	 ///<组离开
	propertyGrid_state_flag_group_expand = 0x1000,	 ///<组展开
	propertyGrid_state_flag_group_expand_no = 0x2000,	 ///<组未展开
};
///@}

///@defgroup   group_pane_state_flag_  窗格状态(pane_state_flag_)
///@{
enum pane_state_flag_
{
	pane_state_flag_leave = element_state_flag_leave,  ///<离开
	pane_state_flag_stay = element_state_flag_stay,   ///<停留

	pane_state_flag_caption = 0x0080,  ///<标题
	pane_state_flag_body = 0x0100,  ///<内容区
};
///@}

///@defgroup   group_layout_state_flag_  布局状态(layout_state_flag_)
///@{
enum layout_state_flag_
{
	layout_state_flag_nothing = window_state_flag_nothing,  ///<无
	layout_state_flag_full = 0x0001,   ///<完整背景
	layout_state_flag_body = 0x0002,   ///<内容区域, 不包含边大小
};
///@}
///@}

/////////////////////////////////////////////////////////////////////
//////////////定义结构体///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

///@defgroup  group_struct_  结构体定义
///@{

typedef   struct lua_State lua_State;

struct  RECTF
{
	float  left;
	float  top;
	float  right;
	float  bottom;
};

///边大小
struct borderSize_  //4条边的大小
{
	int  leftSize;   ///<左边大小
	int  topSize;    ///<上边大小
	int  rightSize;  ///<右边大小
	int  bottomSize; ///<下边大小
};
typedef  borderSize_  spaceSize_, paddingSize_, marginSize_;

///位置点
struct  position_
{
	int  iRow;    ///<行索引
	int  iColumn; ///<列索引
};

///ListBox 列表框项信息
struct listBox_item_
{
	int     index;      ///<项索引
	vint    nUserData;  ///<用户绑定数据
	int     nHeight;    ///<项默认高度
	int     nSelHeight; ///<项选中时高度
	list_item_state_  nState;  ///<状态
	RECT    rcItem;     ///<项坐标
	HELE    hLayout;    ///<布局元素
	HTEMP   hTemp;      ///<列表项模板
};

///ListBox 列表框项信息2
struct listBox_item_info_
{
	vint    nUserData;  ///<用户绑定数据
	int     nHeight;    ///<项高度, -1使用默认高度
	int     nSelHeight; ///<项选中时高度, -1使用默认高度
};

///ListView 列表视项ID
struct  listView_item_id_
{
	int  iGroup;   ///<组索引
	int  iItem;    ///<项索引
};

///List 列表项信息
struct list_item_
{
	int     index;             ///<项索引(行索引)
	int     iSubItem;          ///<子项索引(列索引)
	vint    nUserData;         ///<用户数据
	list_item_state_  nState;  ///<状态
	RECT    rcItem;     ///<未使用
	HELE    hLayout;    ///<布局元素
	HTEMP   hTemp;      ///<列表项模板
};

///List 列表头项信息
struct list_header_item_
{
	int     index;           ///<项索引
	vint    nUserData;       ///<用户数据

	BOOL    bSort;           ///<是否支持排序
	int     nSortType;       ///<排序方式,0无效,1升序,2降序
	int     iColumnAdapter;  ///<对应数据适配器中的列索引

	common_state3_  nState;  ///<状态
	RECT      rcItem;        ///<坐标
	HELE      hLayout;       ///<布局元素
	HTEMP     hTemp;         ///<列表项模板
};

///Tree 树项信息
struct tree_item_
{
	int     nID;				 ///<项ID
	int     nDepth;				 ///<深度
	int     nHeight;			 ///<项高度
	int     nSelHeight;			 ///<项选中状态高度
	vint    nUserData;			 ///<用户数据
	BOOL    bExpand;			 ///<展开
	tree_item_state_  nState;	 ///<状态
	RECT    rcItem;              ///<坐标
	HELE    hLayout;             ///<布局元素
	HTEMP   hTemp;               ///<列表项模板
};

///ListView 列表视项信息
struct listView_item_
{
	int     iGroup;            ///<项所述组索引 -1没有组
	int     iItem;             ///<项在数组中位置索引,如果此致为-1,那么为组
	vint    nUserData;         ///<用户绑定数据
	list_item_state_  nState;  ///<状态  
	RECT    rcItem;            ///<整个区域,包含边框
	HELE    hLayout;           ///<布局元素
	HTEMP   hTemp;             ///<列表项模板 
};

/// @defgroup group_menu_macro Menu菜单
/// @{

///菜单-弹出窗口信息
struct  menu_popupWnd_
{
	HWINDOW hWindow;    ///<窗口句柄
	int     nParentID;  ///<父项ID
};

///菜单背景自绘结构
struct menu_drawBackground_
{
	HMENUX  hMenu;      ///<菜单句柄
	HWINDOW hWindow;    ///<当前弹出菜单项的窗口句柄
	int     nParentID;  ///<父项ID
};

///菜单项自绘结构
struct  menu_drawItem_
{
	HMENUX     hMenu;       ///<菜单句柄
	HWINDOW    hWindow;     ///<当前弹出菜单项的窗口句柄
	int        nID;         ///<ID
	int        nState;	    ///<状态 @ref menu_item_flag_
	int        nShortcutKeyWidth; ///<右侧快捷键占位宽度
	RECT       rcItem;      ///<坐标
	HIMAGE     hIcon;       ///<菜单项图标
	const wchar_t* pText;   ///<文本
};
///@}

///树UI元素拖动项
struct tree_drag_item_
{
	int  nDragItem;  ///< 拖动项ID
	int  nDestItem;  ///< 目标项ID
	int  nType;      ///< 停放相对目标位置,0:(上)停放到目标的上面, 1:(下)停放到目标的下面, 3:(中)停放到目标的的子项, 
};

///字体信息
struct  font_info_
{
	int   nSize;                 ///<字体大小,单位(pt,磅).
	int   nStyle;                ///<字体样式 fontStyle_
	wchar_t  name[LF_FACESIZE];  ///<字体名称
};

///PGrid 属性网格项信息
struct propertyGrid_item_
{
	propertyGrid_item_type_ nType; ///<类型
	int   nID;           ///<项ID
	int   nDepth;        ///<深度
	vint  nUserData;     ///<用户数据
	int   nNameColWidth; ///<名称列宽度

	RECT  rcItem;   ///<坐标
	RECT  rcExpand; ///<展开
	BOOL  bExpand;  ///<是否展开
	BOOL  bShow;    ///<是否可见
};


///Edit 样式信息
struct edit_style_info_
{
	USHORT   type;              ///<样式类型
	USHORT   nRef;              ///<引用计数
	HXCGUI   hFont_image_obj;   ///<句柄(字体,图片,UI对象)
	COLORREF color;             ///<颜色
	BOOL     bColor;            ///<是否使用颜色
};

///Edit 数据复制-样式
struct edit_data_copy_style_
{
	UINT     hFont_image_obj; ///<句柄(字体,图片,UI对象), 使用UINT目的当64位时可以节约4字节内存
	COLORREF color;           ///<颜色
	BOOL     bColor;          ///<是否使用颜色
};

///Edit 数据复制
struct edit_data_copy_
{
	int  nCount;       ///<内容数量
	int  nStyleCount;  ///<样式数量
	edit_data_copy_style_* pStyle; ///<样式数组
	UINT* pData;       ///<内容数组 高位2字节:样式索引, 低位2字节:值
};

///Editor 颜色信息
struct editor_color_
{
	BOOL       bAlignLineArrow;            ///<对齐线 - 是否显示箭头
	COLORREF   clrMargin1;                 ///<侧边栏 - 背景色1, 显示断点
	COLORREF   clrMargin2;                 ///<侧边栏 - 背景色2, 显示行号
	COLORREF   clrMargin_text;             ///<侧边栏 - 文本色 - 行号颜色
	COLORREF   clrMargin_breakpoint;       ///<侧边栏 - 断点色
	COLORREF   clrMargin_breakpointBorder; ///<侧边栏 - 断点描边色
	COLORREF   clrMargin_runRowArrow;      ///<侧边栏 - 调试位置箭头
	COLORREF   clrMargin_curRow;           ///<侧边栏 - 当前行指示色,光标所在行
	COLORREF   clrMargin_error;            ///<侧边栏 - 错误指示色

	COLORREF   clrCurRowFull;       ///<突出显示当前行颜色
	COLORREF   clrMatchSel;         ///<匹配选择文本背景色
	COLORREF   clrAlignLine;        ///<对齐线
	COLORREF   clrAlignLineSel;     ///<对齐线 - 选择内容块
	COLORREF   clrFunSplitLine;     ///<函数分割线颜色 new
	BOOL       funSplitLineMode;    ///<函数分割线-填充模式: 0:无, 1:线, 2:填充

	//选择文本背景 通过API设置
	//插入符颜色   通过API设置

	int       styleSys;             ///<系统关键字  return, break, for
	int       styleFunction;        ///<函数
	int       styleVar;             ///<变量
	int       styleDataType;        ///<基础数据类型  int, byte, char
	int       styleClass;           ///<类  class
	int       styleMacro;           ///<宏
	int       styleEnum;            ///<枚举   new
	int       styleNumber;          ///<数字
	int       styleString;          ///<字符串
	int       styleComment;         ///<注释
	int       StylePunctuation;     ///<标点符号  new
};

/// 月历元素项数据
struct monthCal_item_
{
	int  nDay;     ///< 日期
	int  nType;    ///< 1上月,2当月,3下月
	int  nState;   ///< 组合状态 monthCal_state_flag_
	RECT rcItem;   ///< 项坐标
};

///@}


///@defgroup  group_func_  炫彩回调函数定义
///@{

typedef void (CALLBACK* funDebugError)(const char* pInfo);       //错误回调
typedef BOOL(CALLBACK* funLoadFile)(const wchar_t* pFileName);  //图片资源文件加载回调
typedef void (CALLBACK* funCloudEvent)(const wchar_t* pFileName, int nEvent, HXCGUI hXCGUI);  //云UI事件回调
typedef vint(CALLBACK* funCallUiThread)(vint data);
typedef void (CALLBACK* funIdle)();
typedef void (CALLBACK* funExit)();

///@brief 动画回调
///@param hAnimation 动画序列或动画组句柄
///@param flag       当前忽略
typedef  void(CALLBACK* funAnimation)(HXCGUI hAnimation, int flag);

///@brief 动画项回调
///@param hAnimation 动画项句柄
///@param flag       当前进度(0.0f-1.0f)
typedef  void(CALLBACK* funAnimationItem)(HXCGUI hAnimation, float pos);

///@}


///////////////////////////////////////////////////////////////////////////////////
/////////////事件注册//////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

class bind_event_cpp
{
public:
	virtual BOOL  Equal(bind_event_cpp* p) = 0;
	virtual void* GetThis() = 0;
	virtual void* GetMFun(int& nSize) = 0;
	virtual int HandleEvent(HELE hEle, BOOL bHnadle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled) = 0;
	virtual int HandleEventWnd(HWINDOW hWindow, BOOL bHnadle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled) = 0;
};

template<class R, class C, class F>
class bind_event_cpp_ : public bind_event_cpp
{
public:
	bind_event_cpp_(C* c, F f) :_c(c), _f(f) { }
	virtual BOOL Equal(bind_event_cpp* p) {
		if (_c != p->GetThis())
			return FALSE;
		int size = 0;
		void* f = p->GetMFun(size);
		if (sizeof(F) == size)
		{
			if (0 == memcmp(f, &_f, size))
				return TRUE;
		}
		return FALSE;
	}
	virtual void* GetThis() { return (void*)_c; }
	virtual void* GetMFun(int& nSize) { nSize = sizeof(F); return &_f; }

	template<class H, class A1>
	int CallT(int (C::* f)(A1), H hEleOrWindow, BOOL bHnadle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled)
	{
		if (!bHnadle)
			return (_c->*f)(pbHandled);
		MessageBoxA(NULL, "HandleEvent_cpp_Call a1", "error", 0);
		return 0;
	}
	template<class H, class A1, class A2>
	int CallT(int (C::* f)(A1, A2), H hEleOrWindow, BOOL bHnadle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled)
	{
		if (!bHnadle)
			return (_c->*f)((A1)wParam, pbHandled);
		return (_c->*f)((A1)hEleOrWindow, pbHandled);
	}
	template<class H, class A1, class A2, class A3>
	int CallT(int (C::* f)(A1, A2, A3), H hEleOrWindow, BOOL bHnadle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled)
	{
		if (!bHnadle)
			return (_c->*f)((A1)wParam, (A2)lParam, pbHandled);
		return (_c->*f)((A1)hEleOrWindow, (A2)wParam, pbHandled);
	}
	template<class H, class A1, class A2, class A3, class A4>
	int CallT(int (C::* f)(A1, A2, A3, A4), H hEleOrWindow, BOOL bHnadle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled)
	{
		if (!bHnadle)
			return (_c->*f)((A1)nEvent, (A2)wParam, (A3)lParam, pbHandled);
		return (_c->*f)((A1)hEleOrWindow, (A2)wParam, (A3)lParam, pbHandled);
	}
	template<class H, class A1, class A2, class A3, class A4, class A5>
	int CallT(int (C::* f)(A1, A2, A3, A4, A5), H hEleOrWindow, BOOL bHnadle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled)
	{
		if (bHnadle)
			return (_c->*f)((A1)hEleOrWindow, (A2)nEvent, (A3)wParam, (A4)lParam, pbHandled);
		MessageBoxA(NULL, "HandleEvent_cpp_Call a5", "error", 0);
		return 0;
	}
	virtual int HandleEvent(HELE hEle, BOOL bHnadle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled)
	{
		return CallT(_f, hEle, bHnadle, nEvent, wParam, lParam, pbHandled);
	}
	virtual int HandleEventWnd(HWINDOW hWindow, BOOL bHnadle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled)
	{
		return CallT(_f, hWindow, bHnadle, nEvent, wParam, lParam, pbHandled);
	}
	C* _c;
	F   _f;
};

struct bind_event_c
{
	enum MyEnum
	{
		event_c_ex,
		event_lua_ex,
		event_js_ex,
	} type;
	virtual ~bind_event_c() {}
	virtual BOOL Equal(bind_event_c* p) { return FALSE; };
	virtual void* GetFunc() { return NULL; };
	virtual int HandleEvent(HELE hEle, BOOL bHandle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled) { return 0; };
	virtual int HandleEventWnd(HWINDOW hWindow, BOOL bHandle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled) { return 0; };
};

struct xc_event
{
	xc_event(int regType, const char* pFunName) {
		m_pBind = 0;
		m_pFunC = 0;
		m_name[0] = 0;
		m_regType = regType;
		if (pFunName) strcpy_s(m_name, pFunName);
	}
	int            m_regType;   //注册类型, 0:CPP,1:CPP1,2:CPP2
	bind_event_cpp* m_pBind;     //C++事件回调
	bind_event_c* m_pFunC;     //C事件回调
	char           m_name[MAX_PATH]; //函数名

	BOOL Equal(xc_event* pEvent) {
		if (m_pBind && pEvent->m_pBind)
			return (m_pBind->Equal(pEvent->m_pBind));
		if (m_pFunC && pEvent->m_pFunC)
			return (m_pFunC->Equal(pEvent->m_pFunC));
		return FALSE;
	}
	BOOL Equal(void* pFunc) {
		if (m_pFunC) {
			if (m_pFunC->GetFunc() == pFunc)
				return TRUE;
		}
		return FALSE;
	}
	int HandleEvent(HELE hEle, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled)
	{
		if (m_pBind)
			return m_pBind->HandleEvent(hEle, m_regType, nEvent, wParam, lParam, pbHandled);
		if (m_pFunC)
			return m_pFunC->HandleEvent(hEle, m_regType, nEvent, wParam, lParam, pbHandled);
		MessageBoxA(NULL, "HandleEvent()", "error", 0);
		return 0;
	}
	int HandleEventWnd(HWINDOW hWindow, UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL* pbHandled)
	{
		if (m_pBind)
			return m_pBind->HandleEventWnd(hWindow, m_regType, nEvent, wParam, lParam, pbHandled);
		if (m_pFunC)
			return m_pFunC->HandleEventWnd(hWindow, m_regType, nEvent, wParam, lParam, pbHandled);
		MessageBoxA(NULL, "HandleEventWnd()", "error", 0);
		return 0;
	}
	char* GetFunName() { return m_name; }
	virtual void Release() {
		if (m_pBind) delete m_pBind;
		if (m_pFunC) delete m_pFunC;
		delete this;
	}
};

XC_API BOOL WINAPI _XWnd_RegEvent(HWINDOW hWindow, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI _XWnd_RemoveEvent(HWINDOW hWindow, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI _XEle_RegEvent(HELE hEle, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI _XEle_RemoveEvent(HELE hEle, UINT nEvent, xc_event* pEvent);

template<class R, class C, class F>
BOOL XEle_RegEventCPP_tt(HXCGUI hXCGUI, UINT nEvent, int regType, BOOL bEle, C* c, F f, const char* pFunName) {
	BOOL bResult = TRUE;
	bind_event_cpp* pBind = new bind_event_cpp_<R, C, F>(c, f);
	xc_event* pEvent = new xc_event(regType, pFunName);
	pEvent->m_pBind = pBind;
	if (-1 == regType) {
		if (bEle)
			bResult = _XEle_RemoveEvent((HELE)hXCGUI, nEvent, pEvent);
		else
			bResult = _XWnd_RemoveEvent((HWINDOW)hXCGUI, nEvent, pEvent);
		pEvent->Release();
	}
	else {
		if (bEle) {
			if (FALSE == _XEle_RegEvent((HELE)hXCGUI, nEvent, pEvent))
			{
				pEvent->Release();
				bResult = FALSE;
			}
		}
		else {
			if (FALSE == _XWnd_RegEvent((HWINDOW)hXCGUI, nEvent, pEvent))
			{
				pEvent->Release();
				bResult = FALSE;
			}
		}
	}
	return bResult;
}

template<class R, class C, class CT, class A1>
BOOL XCGUI_RegEventCPP_t(HXCGUI hXCGUI, UINT nEvent, int type, BOOL bEle, C* c, R(CT::* f)(A1), const char* pFunName) {
	return XEle_RegEventCPP_tt<R>(hXCGUI, nEvent, type, bEle, (CT*)c, f, pFunName);
}

template<class R, class C, class CT, class A1, class A2>
BOOL XCGUI_RegEventCPP_t(HXCGUI hXCGUI, UINT nEvent, int type, BOOL bEle, C* c, R(CT::* f)(A1, A2), const char* pFunName) {
	return XEle_RegEventCPP_tt<R>(hXCGUI, nEvent, type, bEle, (CT*)c, f, pFunName);
}

template<class R, class C, class CT, class A1, class A2, class A3>
BOOL XCGUI_RegEventCPP_t(HXCGUI hXCGUI, UINT nEvent, int type, BOOL bEle, C* c, R(CT::* f)(A1, A2, A3), const char* pFunName) {
	return XEle_RegEventCPP_tt<R>(hXCGUI, nEvent, type, bEle, (CT*)c, f, pFunName);
}

template<class R, class C, class CT, class A1, class A2, class A3, class A4>
BOOL XCGUI_RegEventCPP_t(HXCGUI hXCGUI, UINT nEvent, int type, BOOL bEle, C* c, R(CT::* f)(A1, A2, A3, A4), const char* pFunName) {
	return XEle_RegEventCPP_tt<R>(hXCGUI, nEvent, type, bEle, (CT*)c, f, pFunName);
}

template<class R, class C, class CT, class A1, class A2, class A3, class A4, class A5>
BOOL XCGUI_RegEventCPP_t(HXCGUI hXCGUI, UINT nEvent, int type, BOOL bEle, C* c, R(CT::* f)(A1, A2, A3, A4, A5), const char* pFunName) {
	return XEle_RegEventCPP_tt<R>(hXCGUI, nEvent, type, bEle, (CT*)c, f, pFunName);
}


//@别名 元素_注册事件CPP(句柄, 事件类型, 事件函数)
#define XEle_RegEventCPP(hXCGUI,Event,mFun)  XCGUI_RegEventCPP_t(hXCGUI,Event,FALSE,TRUE,this,mFun,#mFun)
//@别名 元素_注册事件CPP1(句柄, 事件类型, 事件函数)
#define XEle_RegEventCPP1(hXCGUI,Event,mFun)  XCGUI_RegEventCPP_t(hXCGUI,Event,TRUE,TRUE,this,mFun,#mFun)
//@别名 元素_移除事件CPP(句柄, 事件类型, 事件函数)
#define XEle_RemoveEventCPP(hXCGUI,Event,mFun) XCGUI_RegEventCPP_t(hXCGUI,Event,-1,TRUE,this,mFun,#mFun)

//@别名 窗口_注册事件CPP(句柄, 事件类型, 事件函数)
#define XWnd_RegEventCPP(hXCGUI,Event,mFun)  XCGUI_RegEventCPP_t(hXCGUI,Event,FALSE,FALSE,this,mFun,#mFun)
//@别名 窗口_注册事件CPP1(句柄, 事件类型, 事件函数)
#define XWnd_RegEventCPP1(hXCGUI,Event,mFun)  XCGUI_RegEventCPP_t(hXCGUI,Event,TRUE,FALSE,this,mFun,#mFun)
//@别名 窗口_移除事件CPP(句柄, 事件类型, 事件函数)
#define XWnd_RemoveEventCPP(hXCGUI,Event,mFun) XCGUI_RegEventCPP_t(hXCGUI,Event,-1,FALSE,this,mFun,#mFun)


//////////////////////////////////////////////////////////////////////
/////////////////////API//////////////////////////////////////////////


XC_API int WINAPI XC_UnicodeToAnsi(const wchar_t* pIn, int inLen, __out char* pOut, int outLen);
XC_API int WINAPI XC_AnsiToUnicode(const char* pIn, int inLen, __out wchar_t* pOut, int outLen);

XC_API LRESULT WINAPI XC_SendMessage(HWINDOW hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
XC_API BOOL    WINAPI XC_PostMessage(HWINDOW hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
XC_API vint WINAPI XC_CallUiThread(funCallUiThread pCall, vint data);
XC_API void WINAPI XC_DebugToFileInfo(const char* pInfo);//打印调试信息到文件 xcgui_debug.txt
XC_API BOOL WINAPI XC_IsHELE(HXCGUI hEle); //检查句柄
XC_API BOOL WINAPI XC_IsHWINDOW(HXCGUI hWindow); //检查句柄
XC_API BOOL WINAPI XC_IsShape(HXCGUI hShape); //检查句柄
XC_API BOOL WINAPI XC_IsHXCGUI(HXCGUI hXCGUI, XC_OBJECT_TYPE nType);
XC_API HWINDOW WINAPI XC_hWindowFromHWnd(HWND hWnd);
XC_API BOOL    WINAPI XC_SetActivateTopWindow();
XC_API BOOL WINAPI XC_SetProperty(HXCGUI hXCGUI, const wchar_t* pName, const wchar_t* pValue);
XC_API const wchar_t* WINAPI XC_GetProperty(HXCGUI hXCGUI, const wchar_t* pName);
XC_API BOOL WINAPI XC_RegisterWindowClassName(const wchar_t* pClassName); //注册窗口类名
XC_API BOOL WINAPI XC_IsSViewExtend(HELE hEle);  //判断元素是否从滚动视图元素扩展的新元素,包含滚动视图元素
XC_API XC_OBJECT_TYPE WINAPI XC_GetObjectType(HXCGUI hXCGUI);
XC_API HXCGUI WINAPI XC_GetObjectByID(HWINDOW hWindow, int nID); //通过ID获取对象句柄
XC_API HXCGUI WINAPI XC_GetObjectByIDName(HWINDOW hWindow, const wchar_t* pName);
XC_API HXCGUI WINAPI XC_GetObjectByUID(int nUID);
XC_API HXCGUI WINAPI XC_GetObjectByUIDName(const wchar_t* pName);
XC_API HXCGUI WINAPI XC_GetObjectByName(const wchar_t* pName);
XC_API void WINAPI XC_SetPaintFrequency(int nMilliseconds); //设置UI绘制频率
XC_API void WINAPI XC_SetTextRenderingHint(int  nType);   //设置文本渲染质量
XC_API void WINAPI XC_EnableGdiDrawText(BOOL bEnable);
XC_API BOOL WINAPI XC_RectInRect(RECT* pRect1, RECT* pRect2);
XC_API void WINAPI XC_CombineRect(RECT* pDest, RECT* pSrc1, RECT* pSrc2);
XC_API void WINAPI XC_ShowLayoutFrame(BOOL bShow);
XC_API void WINAPI XC_EnableDebugFile(BOOL bEnable);
XC_API void WINAPI XC_EnableResMonitor(BOOL bEnable);
XC_API void WINAPI XC_SetLayoutFrameColor(COLORREF color);
XC_API void WINAPI XC_EnableErrorMessageBox(BOOL bEnabel);
XC_API void WINAPI XC_EnableAutoExitApp(BOOL bEnabel);
XC_API BOOL WINAPI XC_LoadResource(const wchar_t* pFileName);
XC_API BOOL WINAPI XC_LoadResourceZip(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API BOOL WINAPI XC_LoadResourceZipMem(void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API BOOL WINAPI XC_LoadResourceFromString(const char* pStringXML, const wchar_t* pFileName);
XC_API BOOL WINAPI XC_LoadResourceFromStringUtf8(const char* pStringXML, const wchar_t* pFileName);
XC_API BOOL WINAPI XC_LoadStyle(const wchar_t* pFileName);
XC_API BOOL WINAPI XC_LoadStyleZip(const wchar_t* pZipFile, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API BOOL WINAPI XC_LoadStyleZipMem(void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API void WINAPI XC_GetTextSize(const wchar_t* pString, int length, HFONTX hFontX, __out SIZE* pOutSize);
XC_API void WINAPI XC_GetTextShowSize(const wchar_t* pString, int length, HFONTX hFontX, __out SIZE* pOutSize);
XC_API void WINAPI XC_GetTextShowSizeEx(const wchar_t* pString, int length, HFONTX hFontX, int nTextAlign, __out SIZE* pOutSize);
//XC_API void WINAPI XC_GetTextShowRect(const wchar_t* pString, int length, HFONTX hFontX, int width, __out SIZE* pOutSize);
XC_API HFONTX WINAPI XC_GetDefaultFont(); //获取默认字体
XC_API void   WINAPI XC_SetDefaultFont(HFONTX hFontX); //设置默认字体
XC_API void  WINAPI XC_AddFileSearchPath(const wchar_t* pPath);
XC_API void  WINAPI XC_InitFont(LOGFONTW* pFont, wchar_t* pName, int size, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);
XC_API  void* WINAPI XC_Malloc(int size);
XC_API  void  WINAPI XC_Free(void* p);
XC_API void WINAPI _XC_SetType(HXCGUI hXCGUI, XC_OBJECT_TYPE nType);
XC_API void WINAPI _XC_AddType(HXCGUI hXCGUI, XC_OBJECT_TYPE nType);
XC_API void WINAPI _XC_BindData(HXCGUI hXCGUI, vint data);
XC_API vint WINAPI _XC_GetBindData(HXCGUI hXCGUI);
XC_API void WINAPI  XC_Alert(const wchar_t* pTitle, const wchar_t* pText);
XC_API HINSTANCE WINAPI XC_Sys_ShellExecute(HWND hwnd, const wchar_t* lpOperation, const wchar_t* lpFile, const wchar_t* lpParameters, const wchar_t* lpDirectory, int nShowCmd);
XC_API HMODULE WINAPI XC_LoadLibrary(const wchar_t* lpFileName);
XC_API FARPROC WINAPI XC_GetProcAddress(HMODULE hModule, const char* lpProcName);
XC_API BOOL    WINAPI XC_FreeLibrary(HMODULE hModule);
XC_API HMODULE WINAPI XC_LoadDll(const wchar_t* pDllFileName);
XC_API BOOL WINAPI XInitXCGUI(BOOL bD2D);
XC_API void WINAPI XRunXCGUI();
XC_API void WINAPI XExitXCGUI();
XC_API void WINAPI XC_PostQuitMessage(int nExitCode);
XC_API XC_OBJECT_TYPE    WINAPI XObj_GetType(HXCGUI hXCGUI);
XC_API XC_OBJECT_TYPE    WINAPI XObj_GetTypeBase(HXCGUI hXCGUI);
XC_API XC_OBJECT_TYPE_EX WINAPI XObj_GetTypeEx(HXCGUI hXCGUI);
XC_API void              WINAPI XUI_SetStyle(HXCGUI hXCGUI, XC_OBJECT_STYLE nStyle);
XC_API XC_OBJECT_STYLE   WINAPI XUI_GetStyle(HXCGUI hXCGUI);
XC_API void WINAPI XUI_EnableCSS(HXCGUI hXCGUI, BOOL bEnable);
XC_API void WINAPI XUI_SetCssName(HXCGUI hXCGUI, const wchar_t* pName);
XC_API const wchar_t* WINAPI XUI_GetCssName(HXCGUI hXCGUI);
XC_API BOOL   WINAPI XWidget_IsShow(HXCGUI hXCGUI);
XC_API void   WINAPI XWidget_Show(HXCGUI hXCGUI, BOOL bShow);
XC_API void   WINAPI XWidget_EnableLayoutControl(HXCGUI hXCGUI, BOOL bEnable);
XC_API BOOL   WINAPI XWidget_IsLayoutControl(HXCGUI hXCGUI);
XC_API HELE   WINAPI XWidget_GetParentEle(HXCGUI hXCGUI);
XC_API HXCGUI WINAPI XWidget_GetParent(HXCGUI hXCGUI);
XC_API HWND   WINAPI XWidget_GetHWND(HXCGUI hXCGUI);
XC_API HWINDOW WINAPI XWidget_GetHWINDOW(HXCGUI hXCGUI);
XC_API  void WINAPI _XC_RegJsBind(const char* pName, int func);
XC_API  void WINAPI XC_RegFunExit(funExit func);
XC_API HBKM WINAPI XBkM_Create();
XC_API void WINAPI XBkM_Destroy(HBKM hBkInfoM);
XC_API int  WINAPI XBkM_SetBkInfo(HBKM hBkInfoM, const wchar_t* pText);
XC_API int  WINAPI XBkM_AddInfo(HBKM hBkInfoM, const wchar_t* pText);
XC_API void WINAPI XBkM_AddBorder(HBKM hBkInfoM, int nState, COLORREF color, int width, int id);
XC_API void WINAPI XBkM_AddFill(HBKM hBkInfoM, int nState, COLORREF color, int id);
XC_API void WINAPI XBkM_AddImage(HBKM hBkInfoM, int nState, HIMAGE hImage, int id);
XC_API int  WINAPI XBkM_GetCount(HBKM hBkInfoM);
XC_API void WINAPI XBkM_Clear(HBKM hBkInfoM);
XC_API BOOL WINAPI XBkM_Draw(HBKM hBkInfoM, int nState, HDRAW hDraw, RECT* pRect);
XC_API BOOL WINAPI XBkM_DrawEx(HBKM hBkInfoM, int nState, HDRAW hDraw, RECT* pRect, int nStateEx);
XC_API void WINAPI XBkM_EnableAutoDestroy(HBKM hBkInfoM, BOOL bEnable);
XC_API void WINAPI XBkM_AddRef(HBKM hBkInfoM);
XC_API void WINAPI XBkM_Release(HBKM hBkInfoM);
XC_API int  WINAPI XBkM_GetRefCount(HBKM hBkInfoM);
XC_API HELE WINAPI XBtn_Create(int x, int y, int cx, int cy, const wchar_t* pName, HXCGUI hParent = NULL);
XC_API BOOL WINAPI XBtn_IsCheck(HELE hEle); //按钮是否被选中
XC_API BOOL WINAPI XBtn_SetCheck(HELE hEle, BOOL bCheck);
XC_API void WINAPI XBtn_SetState(HELE hEle, common_state3_ nState);
XC_API common_state3_  WINAPI XBtn_GetState(HELE hEle);
XC_API button_state_   WINAPI XBtn_GetStateEx(HELE hEle);

XC_API void WINAPI XBtn_SetTypeEx(HELE hEle, XC_OBJECT_TYPE_EX nType);
XC_API void WINAPI XBtn_SetGroupID(HELE hEle, int nID);
XC_API int  WINAPI XBtn_GetGroupID(HELE hEle);
XC_API void WINAPI XBtn_SetBindEle(HELE hEle, HELE hBindEle);
XC_API HELE WINAPI XBtn_GetBindEle(HELE hEle);
XC_API void WINAPI XBtn_SetTextAlign(HELE hEle, int nFlags);
XC_API int  WINAPI XBtn_GetTextAlign(HELE hEle);
XC_API void WINAPI XBtn_SetIconAlign(HELE hEle, button_icon_align_ align);
XC_API void WINAPI XBtn_SetOffset(HELE hEle, int x, int y);
XC_API void WINAPI XBtn_SetOffsetIcon(HELE hEle, int x, int y);
XC_API void WINAPI XBtn_SetIconSpace(HELE hEle, int size);
XC_API void WINAPI XBtn_SetText(HELE hEle, const wchar_t* pName);
XC_API const wchar_t* WINAPI XBtn_GetText(HELE hEle);
XC_API void WINAPI XBtn_SetIcon(HELE hEle, HIMAGE hImage);
XC_API void WINAPI XBtn_SetIconDisable(HELE hEle, HIMAGE hImage);
XC_API HIMAGE WINAPI XBtn_GetIcon(HELE hEle, int nType);
XC_API void WINAPI XBtn_AddAnimationFrame(HELE hEle, HIMAGE hImage, UINT uElapse);
XC_API void WINAPI XBtn_EnableAnimation(HELE hEle, BOOL bEnable, BOOL bLoopPlay = FALSE);


XC_API HELE WINAPI XComboBox_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API BOOL  WINAPI XComboBox_SetSelItem(HELE hEle, int iIndex);
XC_API void WINAPI XComboBox_GetButtonRect(HELE hEle, __out RECT* pRect);
XC_API void WINAPI XComboBox_SetButtonSize(HELE hEle, int size);
XC_API void WINAPI XComboBox_SetDropHeight(HELE hEle, int height); //设置下拉列表高度
XC_API int  WINAPI XComboBox_GetDropHeight(HELE hEle);
XC_API HXCGUI WINAPI XComboBox_CreateAdapter(HELE hEle);
XC_API void WINAPI XComboBox_BindAdapter(HELE hEle, HXCGUI hAdapter);
XC_API HXCGUI WINAPI XComboBox_GetAdapter(HELE hEle);
XC_API void WINAPI XComboBox_SetBindName(HELE hEle, const wchar_t* pName);
XC_API void WINAPI XComboBox_SetItemTemplateXML(HELE hEle, const wchar_t* pXmlFile);
XC_API void WINAPI XComboBox_SetItemTemplateXMLFromString(HELE hEle, const char* pStringXML);
XC_API void WINAPI XComboBox_EnableDrawButton(HELE hEle, BOOL bEnable);
XC_API void WINAPI XComboBox_EnableEdit(HELE hEle, BOOL bEdit);  //启动编辑内容
XC_API void WINAPI XComboBox_EnableDropHeightFixed(HELE hEle, BOOL bEnable);

XC_API int WINAPI XComboBox_GetSelItem(HELE hEle);
XC_API comboBox_state_ WINAPI XComboBox_GetState(HELE hEle);
XC_API int WINAPI XComboBox_AddItemText(HELE hEle, const wchar_t* pText);
XC_API int WINAPI XComboBox_AddItemTextEx(HELE hEle, const wchar_t* pName, const wchar_t* pText);
XC_API int WINAPI XComboBox_AddItemImage(HELE hEle, HIMAGE hImage);
XC_API int WINAPI XComboBox_AddItemImageEx(HELE hEle, const wchar_t* pName, HIMAGE hImage);
XC_API int WINAPI XComboBox_InsertItemText(HELE hEle, int iItem, const wchar_t* pValue);
XC_API int WINAPI XComboBox_InsertItemTextEx(HELE hEle, int iItem, const wchar_t* pName, const wchar_t* pValue);
XC_API int WINAPI XComboBox_InsertItemImage(HELE hEle, int iItem, HIMAGE hImage);
XC_API int WINAPI XComboBox_InsertItemImageEx(HELE hEle, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XComboBox_SetItemText(HELE hEle, int iItem, int iColumn, const wchar_t* pText);
XC_API BOOL WINAPI XComboBox_SetItemTextEx(HELE hEle, int iItem, const wchar_t* pName, const wchar_t* pText);
XC_API BOOL WINAPI XComboBox_SetItemImage(HELE hEle, int iItem, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XComboBox_SetItemImageEx(HELE hEle, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XComboBox_SetItemInt(HELE hEle, int iItem, int iColumn, int nValue);
XC_API BOOL WINAPI XComboBox_SetItemIntEx(HELE hEle, int iItem, const wchar_t* pName, int nValue);
XC_API BOOL WINAPI XComboBox_SetItemFloat(HELE hEle, int iItem, int iColumn, float fFloat);
XC_API BOOL WINAPI XComboBox_SetItemFloatEx(HELE hEle, int iItem, const wchar_t* pName, float fFloat);
XC_API const wchar_t* WINAPI XComboBox_GetItemText(HELE hEle, int iItem, int iColumn);
XC_API const wchar_t* WINAPI XComboBox_GetItemTextEx(HELE hEle, int iItem, const wchar_t* pName);
XC_API HIMAGE WINAPI XComboBox_GetItemImage(HELE hEle, int iItem, int iColumn);
XC_API HIMAGE WINAPI XComboBox_GetItemImageEx(HELE hEle, int iItem, const wchar_t* pName);
XC_API BOOL WINAPI XComboBox_GetItemInt(HELE hEle, int iItem, int iColumn, __out int* pOutValue);
XC_API BOOL WINAPI XComboBox_GetItemIntEx(HELE hEle, int iItem, const wchar_t* pName, __out int* pOutValue);
XC_API BOOL WINAPI XComboBox_GetItemFloat(HELE hEle, int iItem, int iColumn, __out float* pOutValue);
XC_API BOOL WINAPI XComboBox_GetItemFloatEx(HELE hEle, int iItem, const wchar_t* pName, __out float* pOutValue);
XC_API BOOL WINAPI XComboBox_DeleteItem(HELE hEle, int iItem);
XC_API BOOL WINAPI XComboBox_DeleteItemEx(HELE hEle, int iItem, int nCount);
XC_API void WINAPI XComboBox_DeleteItemAll(HELE hEle);
XC_API void WINAPI XComboBox_DeleteColumnAll(HELE hEle);
XC_API int WINAPI XComboBox_GetCount(HELE hEle);
XC_API int WINAPI XComboBox_GetCountColumn(HELE hEle);
XC_API HELE WINAPI XDateTime_Create(int x, int y, int cx, int cy, HXCGUI hParent);
XC_API void WINAPI XDateTime_SetStyle(HELE hEle, int nStyle);
XC_API int WINAPI XDateTime_GetStyle(HELE hEle);
XC_API void WINAPI XDateTime_EnableSplitSlash(HELE hEle, BOOL bSlash);
XC_API void WINAPI XDateTime_GetTime(HELE hEle, __out int* pnHour, __out int* pnMinute, __out int* pnSecond);
XC_API void WINAPI XDateTime_SetTime(HELE hEle, int nHour, int nMinute, int nSecond);
XC_API void WINAPI XDateTime_GetDate(HELE hEle, __out int* pnYear, __out int* pnMonth, __out int* pnDay);
XC_API void WINAPI XDateTime_SetDate(HELE hEle, int nYear, int nMonth, int nDay);
XC_API COLORREF WINAPI XDateTime_GetSelBkColor(HELE hEle);
XC_API void WINAPI XDateTime_SetSelBkColor(HELE hEle, COLORREF crSelectBk);
XC_API HELE WINAPI XDateTime_GetButton(HELE hEle, int nType);
XC_API HELE WINAPI XMonthCal_Create(int x, int y, int cx, int cy, HXCGUI hParent);
XC_API void WINAPI XMonthCal_SetToday(HELE hEle, int nYear, int nMonth, int nDay);
XC_API void WINAPI XMonthCal_GetToday(HELE hEle, __out int* pnYear, __out int* pnMonth, __out int* pnDay);
XC_API void WINAPI XMonthCal_SeSelDate(HELE hEle, int nYear, int nMonth, int nDay);
XC_API void WINAPI XMonthCal_GetSelDate(HELE hEle, __out int* pnYear, __out int* pnMonth, __out int* pnDay);
XC_API HELE WINAPI XMonthCal_GetButton(HELE hEle, monthCal_button_type_ nType);
XC_API int  WINAPI XAd_AddRef(HXCGUI hAdapter);
XC_API int  WINAPI XAd_Release(HXCGUI hAdapter);
XC_API int  WINAPI XAd_GetRefCount(HXCGUI hAdapter);
XC_API void WINAPI XAd_Destroy(HXCGUI hAdapter);
XC_API void WINAPI XAd_EnableAutoDestroy(HXCGUI hAdapter, BOOL bEnable);
XC_API HXCGUI WINAPI XAdListView_Create();
XC_API int  WINAPI XAdListView_Group_AddColumn(HXCGUI hAdapter, const wchar_t* pName);
XC_API int  WINAPI XAdListView_Group_AddItemText(HXCGUI hAdapter, const wchar_t* pValue, int iPos = -1);
XC_API int  WINAPI XAdListView_Group_AddItemTextEx(HXCGUI hAdapter, const wchar_t* pName, const wchar_t* pValue, int iPos = -1);
XC_API int  WINAPI XAdListView_Group_AddItemImage(HXCGUI hAdapter, HIMAGE hImage, int iPos = -1);
XC_API int  WINAPI XAdListView_Group_AddItemImageEx(HXCGUI hAdapter, const wchar_t* pName, HIMAGE hImage, int iPos = -1);
XC_API BOOL WINAPI XAdListView_Group_SetText(HXCGUI hAdapter, int iGroup, int iColumn, const wchar_t* pValue);
XC_API BOOL WINAPI XAdListView_Group_SetTextEx(HXCGUI hAdapter, int iGroup, const wchar_t* pName, const wchar_t* pValue);
XC_API BOOL WINAPI XAdListView_Group_SetImage(HXCGUI hAdapter, int iGroup, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XAdListView_Group_SetImageEx(HXCGUI hAdapter, int iGroup, const wchar_t* pName, HIMAGE hImage);
XC_API int  WINAPI XAdListView_Group_GetCount(HXCGUI hAdapter);
XC_API int  WINAPI XAdListView_Item_GetCount(HXCGUI hAdapter, int iGroup);
XC_API int  WINAPI XAdListView_Item_AddColumn(HXCGUI hAdapter, const wchar_t* pName);  //增加列
XC_API int  WINAPI XAdListView_Item_AddItemText(HXCGUI hAdapter, int iGroup, const wchar_t* pValue, int iPos = -1);
XC_API int  WINAPI XAdListView_Item_AddItemTextEx(HXCGUI hAdapter, int iGroup, const wchar_t* pName, const wchar_t* pValue, int iPos = -1);
XC_API int  WINAPI XAdListView_Item_AddItemImage(HXCGUI hAdapter, int iGroup, HIMAGE hImage, int iPos = -1);
XC_API int  WINAPI XAdListView_Item_AddItemImageEx(HXCGUI hAdapter, int iGroup, const wchar_t* pName, HIMAGE hImage, int iPos = -1);
XC_API BOOL WINAPI XAdListView_Item_SetText(HXCGUI hAdapter, int iGroup, int iItem, int iColumn, const wchar_t* pValue);
XC_API BOOL WINAPI XAdListView_Item_SetTextEx(HXCGUI hAdapter, int iGroup, int iItem, const wchar_t* pName, const wchar_t* pValue);
XC_API BOOL WINAPI XAdListView_Item_SetImage(HXCGUI hAdapter, int iGroup, int iItem, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XAdListView_Item_SetImageEx(HXCGUI hAdapter, int iGroup, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XAdListView_Group_DeleteItem(HXCGUI hAdapter, int iGroup);
XC_API void WINAPI XAdListView_Group_DeleteAllChildItem(HXCGUI hAdapter, int iGroup);
XC_API BOOL WINAPI XAdListView_Item_DeleteItem(HXCGUI hAdapter, int iGroup, int iItem);
XC_API void WINAPI XAdListView_DeleteAll(HXCGUI hAdapter);
XC_API void WINAPI XAdListView_DeleteAllGroup(HXCGUI hAdapter);
XC_API void WINAPI XAdListView_DeleteAllItem(HXCGUI hAdapter);
XC_API void WINAPI XAdListView_DeleteColumnGroup(HXCGUI hAdapter, int iColumn);
XC_API void WINAPI XAdListView_DeleteColumnItem(HXCGUI hAdapter, int iColumn);
XC_API const wchar_t* WINAPI XAdListView_Item_GetTextEx(HXCGUI hAdapter, int iGroup, int iItem, const wchar_t* pName);
XC_API HIMAGE WINAPI XAdListView_Item_GetImageEx(HXCGUI hAdapter, int iGroup, int iItem, const wchar_t* pName);
XC_API HXCGUI WINAPI XAdTable_Create();
XC_API void   WINAPI XAdTable_Sort(HXCGUI hAdapter, int iColumn, BOOL bAscending);  //排序
XC_API adapter_date_type_  WINAPI XAdTable_GetItemDataType(HXCGUI hAdapter, int iItem, int iColumn);
XC_API adapter_date_type_  WINAPI XAdTable_GetItemDataTypeEx(HXCGUI hAdapter, int iItem, const wchar_t* pName);
XC_API int WINAPI XAdTable_AddColumn(HXCGUI hAdapter, const wchar_t* pName);
XC_API int WINAPI XAdTable_SetColumn(HXCGUI hAdapter, const wchar_t* pColName);
XC_API int WINAPI XAdTable_AddItemText(HXCGUI hAdapter, const wchar_t* pValue);
XC_API int WINAPI XAdTable_AddItemTextEx(HXCGUI hAdapter, const wchar_t* pName, const wchar_t* pValue);
XC_API int WINAPI XAdTable_AddItemImage(HXCGUI hAdapter, HIMAGE hImage);
XC_API int WINAPI XAdTable_AddItemImageEx(HXCGUI hAdapter, const wchar_t* pName, HIMAGE hImage);
XC_API int WINAPI XAdTable_InsertItemText(HXCGUI hAdapter, int iItem, const wchar_t* pValue);
XC_API int WINAPI XAdTable_InsertItemTextEx(HXCGUI hAdapter, int iItem, const wchar_t* pName, const wchar_t* pValue);
XC_API int WINAPI XAdTable_InsertItemImage(HXCGUI hAdapter, int iItem, HIMAGE hImage);
XC_API int WINAPI XAdTable_InsertItemImageEx(HXCGUI hAdapter, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XAdTable_SetItemText(HXCGUI hAdapter, int iItem, int iColumn, const wchar_t* pValue);
XC_API BOOL WINAPI XAdTable_SetItemTextEx(HXCGUI hAdapter, int iItem, const wchar_t* pName, const wchar_t* pValue);
XC_API BOOL WINAPI XAdTable_SetItemInt(HXCGUI hAdapter, int iItem, int iColumn, int nValue);
XC_API BOOL WINAPI XAdTable_SetItemIntEx(HXCGUI hAdapter, int iItem, const wchar_t* pName, int nValue);
XC_API BOOL WINAPI XAdTable_SetItemFloat(HXCGUI hAdapter, int iItem, int iColumn, float nValue);
XC_API BOOL WINAPI XAdTable_SetItemFloatEx(HXCGUI hAdapter, int iItem, const wchar_t* pName, float nValue);
XC_API BOOL WINAPI XAdTable_SetItemImage(HXCGUI hAdapter, int iItem, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XAdTable_SetItemImageEx(HXCGUI hAdapter, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XAdTable_DeleteItem(HXCGUI hAdapter, int iItem);
XC_API BOOL WINAPI XAdTable_DeleteItemEx(HXCGUI hAdapter, int iItem, int nCount);
XC_API void WINAPI XAdTable_DeleteItemAll(HXCGUI hAdapter);
XC_API void WINAPI XAdTable_DeleteColumnAll(HXCGUI hAdapter);
XC_API int WINAPI XAdTable_GetCount(HXCGUI hAdapter);
XC_API int WINAPI XAdTable_GetCountColumn(HXCGUI hAdapter);
XC_API const wchar_t* WINAPI XAdTable_GetItemText(HXCGUI hAdapter, int iItem, int iColumn);
XC_API const wchar_t* WINAPI XAdTable_GetItemTextEx(HXCGUI hAdapter, int iItem, const wchar_t* pName);
XC_API HIMAGE WINAPI XAdTable_GetItemImage(HXCGUI hAdapter, int iItem, int iColumn);
XC_API HIMAGE WINAPI XAdTable_GetItemImageEx(HXCGUI hAdapter, int iItem, const wchar_t* pName);
XC_API BOOL WINAPI XAdTable_GetItemInt(HXCGUI hAdapter, int iItem, int iColumn, __out int* pOutValue);
XC_API BOOL WINAPI XAdTable_GetItemIntEx(HXCGUI hAdapter, int iItem, const wchar_t* pName, __out int* pOutValue);
XC_API BOOL WINAPI XAdTable_GetItemFloat(HXCGUI hAdapter, int iItem, int iColumn, __out float* pOutValue);
XC_API BOOL WINAPI XAdTable_GetItemFloatEx(HXCGUI hAdapter, int iItem, const wchar_t* pName, __out float* pOutValue);
XC_API HXCGUI WINAPI XAdTree_Create();
XC_API int WINAPI XAdTree_AddColumn(HXCGUI hAdapter, const wchar_t* pName);
XC_API int WINAPI XAdTree_SetColumn(HXCGUI hAdapter, const wchar_t* pColName);
XC_API int WINAPI XAdTree_InsertItemText(HXCGUI hAdapter, const wchar_t* pValue, int nParentID = XC_ID_ROOT, int insertID = XC_ID_LAST);
XC_API int WINAPI XAdTree_InsertItemTextEx(HXCGUI hAdapter, const wchar_t* pName, const wchar_t* pValue, int nParentID = XC_ID_ROOT, int insertID = XC_ID_LAST);
XC_API int WINAPI XAdTree_InsertItemImage(HXCGUI hAdapter, HIMAGE hImage, int nParentID = XC_ID_ROOT, int insertID = XC_ID_LAST);
XC_API int WINAPI XAdTree_InsertItemImageEx(HXCGUI hAdapter, const wchar_t* pName, HIMAGE hImage, int nParentID = XC_ID_ROOT, int insertID = XC_ID_LAST);
XC_API int WINAPI XAdTree_GetCount(HXCGUI hAdapter);
XC_API int WINAPI XAdTree_GetCountColumn(HXCGUI hAdapter);
XC_API BOOL WINAPI XAdTree_SetItemText(HXCGUI hAdapter, int nID, int iColumn, const wchar_t* pValue);
XC_API BOOL WINAPI XAdTree_SetItemTextEx(HXCGUI hAdapter, int nID, const wchar_t* pName, const wchar_t* pValue);
XC_API BOOL WINAPI XAdTree_SetItemImage(HXCGUI hAdapter, int nID, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XAdTree_SetItemImageEx(HXCGUI hAdapter, int nID, const wchar_t* pName, HIMAGE hImage);
XC_API const wchar_t* WINAPI XAdTree_GetItemText(HXCGUI hAdapter, int nID, int iColumn);
XC_API const wchar_t* WINAPI XAdTree_GetItemTextEx(HXCGUI hAdapter, int nID, const wchar_t* pName);
XC_API HIMAGE WINAPI XAdTree_GetItemImage(HXCGUI hAdapter, int nID, int iColumn);
XC_API HIMAGE WINAPI XAdTree_GetItemImageEx(HXCGUI hAdapter, int nID, const wchar_t* pName);
XC_API BOOL WINAPI XAdTree_DeleteItem(HXCGUI hAdapter, int nID);
XC_API void WINAPI XAdTree_DeleteItemAll(HXCGUI hAdapter);
XC_API void WINAPI XAdTree_DeleteColumnAll(HXCGUI hAdapter);
XC_API HXCGUI WINAPI XAdMap_Create();
XC_API BOOL WINAPI XAdMap_AddItemText(HXCGUI hAdapter, const wchar_t* pName, const wchar_t* pValue);
XC_API BOOL WINAPI XAdMap_AddItemImage(HXCGUI hAdapter, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XAdMap_DeleteItem(HXCGUI hAdapter, const wchar_t* pName);
XC_API int  WINAPI XAdMap_GetCount(HXCGUI hAdapter);
XC_API const wchar_t* WINAPI XAdMap_GetItemText(HXCGUI hAdapter, const wchar_t* pName);
XC_API HIMAGE WINAPI XAdMap_GetItemImage(HXCGUI hAdapter, const wchar_t* pName);
XC_API BOOL WINAPI XAdMap_SetItemText(HXCGUI hAdapter, const wchar_t* pName, const wchar_t* pValue);
XC_API BOOL WINAPI XAdMap_SetItemImage(HXCGUI hAdapter, const wchar_t* pName, HIMAGE hImage);
XC_API void WINAPI XDebug_Print(int  level, const char* pInfo);
XC_API void WINAPI _xtrace(const char* pFormat, ...); //支持多线程
XC_API void WINAPI _xtracew(const wchar_t* pFormat, ...); //支持多线程
XC_API void WINAPI XDebug_OutputDebugStringA(const char* pString); //OutputDebugStringA
XC_API void WINAPI XDebug_OutputDebugStringW(const wchar_t* pString); //OutputDebugStringW
XC_API void WINAPI XDebug_Set_OutputDebugString_UTF8(BOOL bUTF8); //设置debug输出编码方式 encoding_utf8

XC_API float WINAPI XEase_Linear(float p);
XC_API float WINAPI XEase_Quad(float p, ease_type_ flag);
XC_API float WINAPI XEase_Cubic(float p, ease_type_ flag);
XC_API float WINAPI XEase_Quart(float p, ease_type_ flag);
XC_API float WINAPI XEase_Quint(float p, ease_type_ flag);
XC_API float WINAPI XEase_Sine(float p, ease_type_ flag);
XC_API float WINAPI XEase_Expo(float p, ease_type_ flag);
XC_API float WINAPI XEase_Circ(float p, ease_type_ flag);
XC_API float WINAPI XEase_Elastic(float p, ease_type_ flag);
XC_API float WINAPI XEase_Back(float p, ease_type_ flag);
XC_API float WINAPI XEase_Bounce(float p, ease_type_ flag);
XC_API HELE WINAPI XEditor_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XEidtor_EnableAutoMatchSpaseSelect(HELE hEle, BOOL bEnable);
XC_API BOOL WINAPI XEditor_IsBreakpoint(HELE hEle, int iRow);
XC_API BOOL WINAPI XEditor_SetBreakpoint(HELE hEle, int iRow, BOOL bActivate = TRUE);
XC_API int  WINAPI XEditor_GetBreakpointCount(HELE hEle);
XC_API int  WINAPI XEditor_GetBreakpoints(HELE hEle, out_buffer_ int* aPoints, int nCount);
XC_API BOOL WINAPI XEditor_RemoveBreakpoint(HELE hEle, int iRow);
XC_API void WINAPI XEditor_ClearBreakpoint(HELE hEle);
XC_API BOOL WINAPI XEditor_SetRunRow(HELE hEle, int iRow);
XC_API void WINAPI XEditor_GetColor(HELE hEle, __out editor_color_* pInfo);
XC_API void WINAPI XEditor_SetColor(HELE hEle, editor_color_* pInfo);
XC_API void WINAPI XEditor_SetStyleKeyword(HELE hEle, int iStyle);
XC_API void WINAPI XEditor_SetStyleFunction(HELE hEle, int iStyle);
XC_API void WINAPI XEditor_SetStyleVar(HELE hEle, int iStyle);
XC_API void WINAPI XEditor_SetStyleDataType(HELE hEle, int iStyle);
XC_API void WINAPI XEditor_SetStyleClass(HELE hEle, int iStyle);
XC_API void WINAPI XEditor_SetStyleMacro(HELE hEle, int iStyle);
XC_API void WINAPI XEditor_SetStyleString(HELE hEle, int iStyle);
XC_API void WINAPI XEditor_SetStyleComment(HELE hEle, int iStyle);
XC_API void WINAPI XEditor_SetStyleNumber(HELE hEle, int iStyle);
XC_API void WINAPI XEditor_SetCurRow(HELE hEle, int iRow);
XC_API int  WINAPI XEditor_GetDepth(HELE hEle, int iRow);
XC_API int  WINAPI XEditor_ToExpandRow(HELE hEle, int iRow);
XC_API void WINAPI XEditor_ExpandAll(HELE hEle, BOOL bExpand);
XC_API void WINAPI XEditor_Expand(HELE hEle, int iRow, BOOL bExpand);
XC_API void WINAPI XEditor_ExpandEx(HELE hEle, int iRow);
XC_API void WINAPI XEditor_AddKeyword(HELE hEle, const wchar_t* pKey, int iStyle);
XC_API void WINAPI XEditor_AddConst(HELE hEle, const wchar_t* pKey);
XC_API void WINAPI XEditor_AddFunction(HELE hEle, const wchar_t* pKey);
XC_API void WINAPI XEditor_AddExcludeDefVarKeyword(HELE hEle, const wchar_t* pKeyword);
XC_API void WINAPI XEditor_FunArgsExpand_AddArg(HELE hEle, const wchar_t* pTypeName, const wchar_t* pArgName, const wchar_t* pText);
XC_API void WINAPI XEditor_FunArgsExpand_Expand(HELE hEle, const wchar_t* pFunName, int iRow, int iCol, int iCol2, int nDepth);
XC_API HELE WINAPI XEdit_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API HELE WINAPI XEdit_CreateEx(int x, int y, int cx, int cy, edit_type_ type, HXCGUI hParent = NULL);
XC_API void WINAPI XEdit_EnableAutoWrap(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEdit_EnableReadOnly(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEdit_EnableMultiLine(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEdit_EnablePassword(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEdit_EnableAutoSelAll(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEdit_EnableAutoCancelSel(HELE hEle, BOOL bEnable);
XC_API BOOL WINAPI XEdit_IsReadOnly(HELE hEle);
XC_API BOOL WINAPI XEdit_IsMultiLine(HELE hEle);
XC_API BOOL WINAPI XEdit_IsPassword(HELE hEle);
XC_API BOOL WINAPI XEdit_IsAutoWrap(HELE hEle);
XC_API BOOL WINAPI XEdit_IsEmpty(HELE hEle);
XC_API BOOL WINAPI XEdit_IsInSelect(HELE hEle, int iRow, int iCol);
XC_API int  WINAPI XEdit_GetRowCount(HELE hEle);
XC_API edit_data_copy_* WINAPI XEdit_GetData(HELE hEle);
XC_API void WINAPI XEdit_AddData(HELE hEle, edit_data_copy_* pData, in_buffer_ USHORT* styleTable, int nStyleCount);
XC_API void WINAPI XEdit_FreeData(edit_data_copy_* pData);
XC_API void WINAPI XEdit_SetDefaultText(HELE hEle, const wchar_t* pString);
XC_API void WINAPI XEdit_SetDefaultTextColor(HELE hEle, COLORREF color);
XC_API void WINAPI XEdit_SetPasswordCharacter(HELE hEle, wchar_t  ch);
XC_API void WINAPI XEdit_SetTextAlign(HELE hEle, int  align);
XC_API void WINAPI XEdit_SetTabSpace(HELE hEle, int  nSpace);
XC_API void WINAPI XEdit_SetText(HELE hEle, const wchar_t* pString);
XC_API void WINAPI XEdit_SetTextInt(HELE hEle, int nValue);
XC_API int  WINAPI XEdit_GetText(HELE hEle, __out wchar_t* pOut, int nOutlen);
XC_API int  WINAPI XEdit_GetTextRow(HELE hEle, int iRow, __out wchar_t* pOut, int nOutlen);
XC_API int  WINAPI XEdit_GetLength(HELE hEle);
XC_API int  WINAPI XEdit_GetLengthRow(HELE hEle, int iRow);
XC_API wchar_t WINAPI XEdit_GetAt(HELE hEle, int iRow, int iCol);
XC_API void WINAPI XEdit_InsertText(HELE hEle, int iRow, int iCol, const wchar_t* pString);

//XC_API void WINAPI XEdit_InsertTextUser(HELE hEle, const wchar_t* pString);
XC_API void WINAPI XEdit_AddText(HELE hEle, const wchar_t* pString);
XC_API void WINAPI XEdit_AddTextEx(HELE hEle, const wchar_t* pString, int iStyle);
XC_API int  WINAPI XEdit_AddObject(HELE hEle, HXCGUI hObj);
XC_API void WINAPI XEdit_AddByStyle(HELE hEle, int iStyle);
XC_API int  WINAPI XEdit_AddStyle(HELE hEle, HXCGUI hFont_image_Obj, COLORREF color, BOOL bColor);
XC_API int  WINAPI XEdit_AddStyleEx(HELE hEle, const wchar_t* fontName, int fontSize, int fontStyle, COLORREF color, BOOL bColor);
XC_API BOOL WINAPI XEdit_GetStyleInfo(HELE hEle, int iStyle, __out edit_style_info_* info);
XC_API void WINAPI XEdit_SetCurStyle(HELE hEle, int iStyle);
XC_API void WINAPI XEdit_SetCaretColor(HELE hEle, COLORREF  color);
XC_API void WINAPI XEdit_SetCaretWidth(HELE hEle, int nWidth);
XC_API void WINAPI XEdit_SetSelectBkColor(HELE hEle, COLORREF color);

XC_API void WINAPI XEdit_SetRowHeight(HELE hEle, int nHeight);
XC_API void WINAPI XEdit_SetRowHeightEx(HELE hEle, int iRow, int nHeight);
//XC_API void WINAPI XEdit_SetCurPos(HELE hEle, int iRow, int iCol);
XC_API int  WINAPI XEdit_GetCurPos(HELE hEle);
XC_API int  WINAPI XEdit_GetCurRow(HELE hEle);
XC_API int  WINAPI XEdit_GetCurCol(HELE hEle);
XC_API void WINAPI XEdit_GetPoint(HELE hEle, int iRow, int iCol, __out POINT* pOut);
XC_API BOOL WINAPI XEdit_AutoScroll(HELE hEle);
XC_API BOOL WINAPI XEdit_AutoScrollEx(HELE hEle, int iRow, int iCol);
//XC_API void WINAPI XEdit_PositionToInfo(HELE hEle, int iPos, position_* pInfo);
XC_API BOOL WINAPI XEdit_SelectAll(HELE hEle);
XC_API BOOL WINAPI XEdit_CancelSelect(HELE hEle);
XC_API BOOL WINAPI XEdit_DeleteSelect(HELE hEle);
XC_API BOOL WINAPI XEdit_SetSelect(HELE hEle, int iStartRow, int iStartCol, int iEndRow, int iEndCol);
XC_API int  WINAPI XEdit_GetSelectText(HELE hEle, __out wchar_t* pOut, int nOutLen);
XC_API BOOL WINAPI XEdit_GetSelectRange(HELE hEle, __out position_* pBegin, __out position_* pEnd);
XC_API void WINAPI XEdit_GetVisibleRowRange(HELE hEle, __out int* piStart, __out int* piEnd);
XC_API BOOL WINAPI XEdit_Delete(HELE hEle, int iStartRow, int iStartCol, int iEndRow, int iEndCol);
XC_API BOOL WINAPI XEdit_DeleteRow(HELE hEle, int iRow);
XC_API BOOL WINAPI XEdit_ClipboardCut(HELE hEle);
XC_API BOOL WINAPI XEdit_ClipboardCopy(HELE hEle);
XC_API BOOL WINAPI XEdit_ClipboardPaste(HELE hEle);
XC_API BOOL WINAPI XEdit_Undo(HELE hEle);
XC_API BOOL WINAPI XEdit_Redo(HELE hEle);
XC_API void WINAPI XEdit_AddChatBegin(HELE hEle, HIMAGE hImageAvatar, HIMAGE hImageBubble, int nFlag);
XC_API void WINAPI XEdit_AddChatEnd(HELE hEle);
XC_API void WINAPI XEdit_SetChatIndentation(HELE hEle, int nIndentation);
XC_API BOOL WINAPI XEdit_CommentSelect(HELE hEle);
XC_API BOOL WINAPI XEdit_IndentationSelect(HELE hEle, int bAdd);
XC_API HELE WINAPI XEle_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API BOOL WINAPI _XEle_RegEvent(HELE hEle, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI _XEle_RemoveEvent(HELE hEle, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI XEle_RegEventC(HELE hEle, int nEvent, void* pFun); //注册事件C方式
XC_API BOOL WINAPI XEle_RegEventC1(HELE hEle, int nEvent, void* pFun);
XC_API BOOL WINAPI XEle_RegEventC2(HELE hEle, int nEvent, void* pFun);
XC_API BOOL WINAPI XEle_RemoveEventC(HELE hEle, int nEvent, void* pFun); //移除事件函数C方式
XC_API int  WINAPI XEle_SendEvent(HELE hEle, int nEvent, WPARAM wParam, LPARAM lParam);
XC_API BOOL WINAPI XEle_PostEvent(HELE hEle, int nEvent, WPARAM wParam, LPARAM lParam);
XC_API BOOL WINAPI XEle_IsShow(HELE hEle);
XC_API BOOL WINAPI XEle_IsEnable(HELE hEle);
XC_API BOOL WINAPI XEle_IsEnableFocus(HELE hEle);
XC_API BOOL WINAPI XEle_IsDrawFocus(HELE hEle);
XC_API BOOL WINAPI XEle_IsEnableEvent_XE_PAINT_END(HELE hEle);
XC_API BOOL WINAPI XEle_IsMouseThrough(HELE hEle);
XC_API BOOL WINAPI XEle_IsBkTransparent(HELE hEle);
XC_API BOOL WINAPI XEle_IsKeyTab(HELE hEle);
XC_API BOOL WINAPI XEle_IsSwitchFocus(HELE hEle);
XC_API BOOL WINAPI XEle_IsEnable_XE_MOUSEWHEEL(HELE hEle);
XC_API BOOL WINAPI XEle_IsChildEle(HELE hEle, HELE hChildEle);
XC_API BOOL WINAPI XEle_IsEnableCanvas(HELE hEle);
XC_API BOOL WINAPI XEle_IsFocus(HELE hEle);
XC_API BOOL WINAPI XEle_IsFocusEx(HELE hEle);
XC_API void WINAPI XEle_Enable(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableFocus(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableDrawFocus(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableDrawBorder(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableCanvas(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableBkTransparent(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableMouseThrough(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableKeyTab(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableSwitchFocus(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableEvent_XE_PAINT_END(HELE hEle, BOOL bEnable);
XC_API void WINAPI XEle_EnableEvent_XE_MOUSEWHEEL(HELE hEle, BOOL bEnable);
XC_API int  WINAPI XEle_SetRect(HELE hEle, RECT* pRect, BOOL bRedraw = FALSE, int nFlags = adjustLayout_all, UINT nAdjustNo = 0);
XC_API int  WINAPI XEle_SetRectEx(HELE hEle, int x, int y, int cx, int cy, BOOL bRedraw = FALSE, int nFlags = adjustLayout_all, UINT nAdjustNo = 0);
XC_API int  WINAPI XEle_SetRectLogic(HELE hEle, RECT* pRect, BOOL bRedraw = FALSE, int nFlags = adjustLayout_all, UINT nAdjustNo = 0); //逻辑模式坐标
XC_API void WINAPI XEle_GetRect(HELE hEle, __out RECT* pRect);   //相对与父坐标,人眼观察模式
XC_API void WINAPI XEle_GetRectLogic(HELE hEle, __out RECT* pRect); //相对与父坐标,逻辑模式
XC_API void WINAPI XEle_GetClientRect(HELE hEle, __out RECT* pRect);  //左上角为0，0坐标
XC_API void WINAPI XEle_GetWndClientRect(HELE hEle, __out RECT* pRect);
XC_API void WINAPI XEle_SetWidth(HELE hEle, int nWidth);
XC_API void WINAPI XEle_SetHeight(HELE hEle, int nHeight);
XC_API int  WINAPI XEle_GetWidth(HELE hEle);
XC_API int  WINAPI XEle_GetHeight(HELE hEle);
XC_API void WINAPI XEle_RectWndClientToEleClient(HELE hEle, __in_out RECT* pRect);
XC_API void WINAPI XEle_PointWndClientToEleClient(HELE hEle, __in_out POINT* pPt);
XC_API void WINAPI XEle_RectClientToWndClient(HELE hEle, __in_out RECT* pRect);
XC_API void WINAPI XEle_PointClientToWndClient(HELE hEle, __in_out POINT* pPt);
XC_API BOOL WINAPI XEle_AddChild(HELE hEle, HXCGUI hChild);
XC_API BOOL WINAPI XEle_InsertChild(HELE hEle, HXCGUI hChild, int index);  //插入到指定位置
XC_API void WINAPI XEle_Remove(HELE hEle);
XC_API BOOL WINAPI XEle_SetZOrder(HELE hEle, int index);
XC_API BOOL WINAPI XEle_SetZOrderEx(HELE hEle, HELE hDestEle, zorder_ nType);
XC_API int  WINAPI XEle_GetZOrder(HELE hEle);
XC_API BOOL WINAPI XEle_EnableTopmost(HELE hEle, BOOL bTopmost);


XC_API void WINAPI XEle_SetCursor(HELE hEle, HCURSOR hCursor);
XC_API HCURSOR WINAPI XEle_GetCursor(HELE hEle);

XC_API void WINAPI XEle_SetTextColor(HELE hEle, COLORREF color);
XC_API COLORREF WINAPI XEle_GetTextColor(HELE hEle);
XC_API COLORREF WINAPI XEle_GetTextColorEx(HELE hEle);
XC_API void WINAPI XEle_SetFocusBorderColor(HELE hEle, COLORREF color);
XC_API COLORREF WINAPI XEle_GetFocusBorderColor(HELE hEle);
XC_API void WINAPI XEle_SetFont(HELE hEle, HFONTX hFontx);
XC_API HFONTX WINAPI XEle_GetFont(HELE hEle);
XC_API HFONTX WINAPI XEle_GetFontEx(HELE hEle);
XC_API void WINAPI XEle_SetAlpha(HELE hEle, BYTE alpha);
XC_API int  WINAPI XEle_GetChildCount(HELE hEle);
XC_API HXCGUI WINAPI XEle_GetChildByIndex(HELE hEle, int index);
XC_API HXCGUI WINAPI XEle_GetChildByID(HELE hEle, int nID);
XC_API void WINAPI XEle_SetBorderSize(HELE hEle, int left, int top, int right, int bottom);
XC_API void WINAPI XEle_GetBorderSize(HELE hEle, __out borderSize_* pBorder);
XC_API void WINAPI XEle_SetPadding(HELE hEle, int left, int top, int right, int bottom);
XC_API void WINAPI XEle_GetPadding(HELE hEle, __out paddingSize_* pPadding);
XC_API void WINAPI XEle_SetDragBorder(HELE hEle, int nFlags);
XC_API void WINAPI XEle_SetDragBorderBindEle(HELE hEle, int nFlags, HELE hBindEle, int nSpace);
XC_API void WINAPI XEle_SetMinSize(HELE hEle, int nWidth, int nHeight);
XC_API void WINAPI XEle_SetMaxSize(HELE hEle, int nWidth, int nHeight);
XC_API void WINAPI XEle_SetLockScroll(HELE hEle, BOOL bHorizon, BOOL bVertical);
XC_API HELE WINAPI XEle_HitChildEle(HELE hEle, __in POINT* pPt);
XC_API void WINAPI XEle_SetUserData(HELE hEle, vint nData);
XC_API vint WINAPI XEle_GetUserData(HELE hEle);
XC_API void WINAPI XEle_GetContentSize(HELE hEle, BOOL bHorizon, int cx, int cy, __out SIZE* pSize);
XC_API void WINAPI XEle_SetCapture(HELE hEle, BOOL b);
XC_API void WINAPI XEle_Redraw(HELE hEle, BOOL bImmediate = FALSE);
XC_API void WINAPI XEle_RedrawRect(HELE hEle, RECT* pRect, BOOL bImmediate = FALSE);
XC_API void WINAPI XEle_Destroy(HELE hEle);  //销毁
XC_API void WINAPI XEle_AddBkBorder(HELE hEle, int nState, COLORREF color, int width);
XC_API void WINAPI XEle_AddBkFill(HELE hEle, int nState, COLORREF color);
XC_API void WINAPI XEle_AddBkImage(HELE hEle, int nState, HIMAGE hImage);
XC_API int  WINAPI XEle_GetBkInfoCount(HELE hEle);
XC_API void WINAPI XEle_ClearBkInfo(HELE hEle);
XC_API HBKM WINAPI XEle_GetBkManager(HELE hEle);
XC_API HBKM WINAPI XEle_GetBkManagerEx(HELE hEle);
XC_API void WINAPI XEle_SetBkManager(HELE hEle, HBKM hBkInfoM);
XC_API int  WINAPI XEle_GetStateFlags(HELE hEle); //获取组合状态
XC_API BOOL WINAPI XEle_DrawFocus(HELE hEle, HDRAW hDraw, RECT* pRect);
XC_API void WINAPI XEle_DrawEle(HELE hEle, HDRAW hDraw);
XC_API void WINAPI XEle_EnableTransparentChannel(HELE hEle, BOOL bEnable);
XC_API BOOL WINAPI XEle_SetXCTimer(HELE hEle, UINT nIDEvent, UINT uElapse);
XC_API BOOL WINAPI XEle_KillXCTimer(HELE hEle, UINT nIDEvent);
XC_API void WINAPI XEle_SetToolTip(HELE hEle, const wchar_t* pText);
XC_API void WINAPI XEle_SetToolTipEx(HELE hEle, const wchar_t* pText, int nTextAlign);
XC_API const wchar_t* WINAPI XEle_GetToolTip(HELE hEle);
XC_API void WINAPI XEle_PopupToolTip(HELE hEle, int x, int y);
XC_API void WINAPI XEle_AdjustLayout(HELE hEle, UINT nAdjustNo = 0);
XC_API void WINAPI XEle_AdjustLayoutEx(HELE hEle, int nFlags = adjustLayout_self, UINT nAdjustNo = 0);

XC_API HFONTX WINAPI XFont_Create(int size);//创建字体
XC_API HFONTX WINAPI XFont_CreateEx(const wchar_t* pName = L"宋体", int size = 12, int style = fontStyle_regular);
XC_API HFONTX WINAPI XFont_CreateFromLOGFONTW(LOGFONTW* pFontInfo);
XC_API HFONTX WINAPI XFont_CreateFromHFONT(HFONT hFont);
XC_API HFONTX WINAPI XFont_CreateFromFont(void* pFont);
XC_API HFONTX WINAPI XFont_CreateFromFile(const wchar_t* pFontFile, int size = 12, int style = fontStyle_regular);
XC_API void   WINAPI XFont_EnableAutoDestroy(HFONTX hFontX, BOOL bEnable);
XC_API void* WINAPI XFont_GetFont(HFONTX hFontX);
XC_API void  WINAPI XFont_GetFontInfo(HFONTX hFontX, __out font_info_* pInfo);
XC_API BOOL  WINAPI XFont_GetLOGFONTW(HFONTX hFontX, HDC hdc, __out LOGFONTW* pOut);
XC_API void  WINAPI XFont_AddRef(HFONTX hFontX);   //增加引用计数
XC_API void  WINAPI XFont_Release(HFONTX hFontX);  //释放引用计数
XC_API int   WINAPI XFont_GetRefCount(HFONTX hFontX);
XC_API void  WINAPI XFont_Destroy(HFONTX hFontX);  //销毁字体
XC_API HWINDOW WINAPI XFrameWnd_Create(int x, int y, int cx, int cy, const wchar_t* pTitle, HWND hWndParent, int XCStyle);  //创建窗口
XC_API void WINAPI XFrameWnd_GetLayoutAreaRect(HWINDOW hWindow, __out RECT* pRect); //获取客户区布局区域坐标
XC_API void WINAPI XFrameWnd_SetView(HWINDOW hWindow, HELE hEle);
XC_API void WINAPI XFrameWnd_SetPaneSplitBarColor(HWINDOW hWindow, COLORREF color);
XC_API void WINAPI XFrameWnd_SetTabBarHeight(HWINDOW hWindow, int nHeight);
XC_API BOOL WINAPI XFrameWnd_SaveLayoutToFile(HWINDOW hWindow, const wchar_t* pFileName);
XC_API BOOL WINAPI XFrameWnd_LoadLayoutFile(HWINDOW hWindow, in_buffer_ HELE* aPaneList, int nEleCount, const wchar_t* pFileName);
XC_API BOOL WINAPI XFrameWnd_AddPane(HWINDOW hWindow, HELE hPaneDest, HELE hPaneNew, pane_align_ align);
XC_API BOOL WINAPI XFrameWnd_MergePane(HWINDOW hWindow, HELE hPaneDest, HELE hPaneNew);
XC_API HIMAGE WINAPI XImgSrc_LoadFile(const wchar_t* pFileName);//从文件中加载图片
XC_API HIMAGE WINAPI XImgSrc_LoadFileRect(const wchar_t* pFileName, int x, int y, int cx, int cy);  //加载图片,指定区域
XC_API HIMAGE WINAPI XImgSrc_LoadRes(int id, const wchar_t* pType);//从资源中加载图片
XC_API HIMAGE WINAPI XImgSrc_LoadZip(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword = NULL);//从ZIP中加载图片
XC_API HIMAGE WINAPI XImgSrc_LoadZipRect(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword, int x, int y, int cx, int cy);
XC_API HIMAGE WINAPI XImgSrc_LoadZipMem(void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API HIMAGE WINAPI XImgSrc_LoadMemory(void* pBuffer, int nSize);
XC_API HIMAGE WINAPI XImgSrc_LoadMemoryRect(void* pBuffer, int nSize, int x, int y, int cx, int cy);
XC_API HIMAGE WINAPI XImgSrc_LoadFromImage(void* pImage);
XC_API HIMAGE WINAPI XImgSrc_LoadFromExtractIcon(const wchar_t* pFileName);
XC_API HIMAGE WINAPI XImgSrc_LoadFromHICON(HICON hIcon);
XC_API HIMAGE WINAPI XImgSrc_LoadFromHBITMAP(HBITMAP hBitmap);
XC_API void WINAPI XImgSrc_EnableAutoDestroy(HIMAGE hImage, BOOL bEnable); //启用或关闭自动销毁,当与UI元素关联时有效
XC_API int WINAPI XImgSrc_GetWidth(HIMAGE hImage);
XC_API int WINAPI XImgSrc_GetHeight(HIMAGE hImage);
XC_API const wchar_t* WINAPI XImgSrc_GetFile(HIMAGE hImage);
XC_API void WINAPI XImgSrc_AddRef(HIMAGE hImage);
XC_API void WINAPI XImgSrc_Release(HIMAGE hImage);
XC_API int  WINAPI XImgSrc_GetRefCount(HIMAGE hImage);
XC_API void WINAPI XImgSrc_Destroy(HIMAGE hImage);
XC_API HIMAGE WINAPI XImage_LoadSrc(HIMAGE hImageSrc);
XC_API HIMAGE WINAPI XImage_LoadFile(const wchar_t* pFileName);
XC_API HIMAGE WINAPI XImage_LoadFileAdaptive(const wchar_t* pFileName, int leftSize, int topSize, int rightSize, int bottomSize);
XC_API HIMAGE WINAPI XImage_LoadFileRect(const wchar_t* pFileName, int x, int y, int cx, int cy);
XC_API HIMAGE WINAPI XImage_LoadResAdaptive(int id, const wchar_t* pType, int leftSize, int topSize, int rightSize, int bottomSize, HMODULE hInst = NULL);
XC_API HIMAGE WINAPI XImage_LoadRes(int id, const wchar_t* pType, HMODULE hInst = NULL);
XC_API HIMAGE WINAPI XImage_LoadZip(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API HIMAGE WINAPI XImage_LoadZipAdaptive(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword, int x1, int x2, int y1, int y2);
XC_API HIMAGE WINAPI XImage_LoadZipRect(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword, int x, int y, int cx, int cy);
XC_API HIMAGE WINAPI XImage_LoadZipMem(void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API HIMAGE WINAPI XImage_LoadMemory(void* pBuffer, int nSize);
XC_API HIMAGE WINAPI XImage_LoadMemoryRect(void* pBuffer, int nSize, int x, int y, int cx, int cy);
XC_API HIMAGE WINAPI XImage_LoadMemoryAdaptive(void* pBuffer, int nSize, int leftSize, int topSize, int rightSize, int bottomSize);
XC_API HIMAGE WINAPI XImage_LoadFromImage(void* pImage);
XC_API HIMAGE WINAPI XImage_LoadFromExtractIcon(const wchar_t* pFileName);
XC_API HIMAGE WINAPI XImage_LoadFromHICON(HICON hIcon);
XC_API HIMAGE WINAPI XImage_LoadFromHBITMAP(HBITMAP hBitmap);
XC_API BOOL WINAPI XImage_IsStretch(HIMAGE hImage);   //是否拉伸图片
XC_API BOOL WINAPI XImage_IsAdaptive(HIMAGE hImage);  //是否为自适应图片
XC_API BOOL WINAPI XImage_IsTile(HIMAGE hImage);      //是否为平铺图片
XC_API BOOL WINAPI XImage_SetDrawType(HIMAGE hImage, image_draw_type_ nType);//设置图片绘制类型
XC_API BOOL WINAPI XImage_SetDrawTypeAdaptive(HIMAGE hImage, int leftSize, int topSize, int rightSize, int bottomSize);//设置图片自适应
XC_API void WINAPI XImage_SetTranColor(HIMAGE hImage, COLORREF color); //设置透明色
XC_API void WINAPI XImage_SetTranColorEx(HIMAGE hImage, COLORREF color, BYTE tranColor); //设置透明色
XC_API float WINAPI XImage_SetRotateAngle(HIMAGE hImage, float  fAngle);
XC_API void WINAPI XImage_SetSplitEqual(HIMAGE hImage, int nCount, int iIndex);
XC_API void WINAPI XImage_EnableTranColor(HIMAGE hImage, BOOL bEnable); //启用透明色
XC_API void WINAPI XImage_EnableAutoDestroy(HIMAGE hImage, BOOL bEnable); //启用或关闭自动销毁,当与UI元素关联时有效
XC_API void WINAPI XImage_EnableCenter(HIMAGE hImage, BOOL bCenter); //bCenter
XC_API BOOL WINAPI XImage_IsCenter(HIMAGE hImage);
XC_API image_draw_type_ WINAPI XImage_GetDrawType(HIMAGE hImage); //获取图片绘制类型
XC_API int WINAPI XImage_GetWidth(HIMAGE hImage);
XC_API int WINAPI XImage_GetHeight(HIMAGE hImage);
XC_API HIMAGE WINAPI XImage_GetImageSrc(HIMAGE hImage);
XC_API void WINAPI XImage_AddRef(HIMAGE hImage);
XC_API void WINAPI XImage_Release(HIMAGE hImage);
XC_API int  WINAPI XImage_GetRefCount(HIMAGE hImage);
XC_API void WINAPI XImage_Destroy(HIMAGE hImage);
XC_API HELE WINAPI XLayout_Create(int x, int y, int cx, int cy, HXCGUI hParent);
XC_API HELE WINAPI XLayout_CreateEx(HXCGUI hParent);
XC_API BOOL WINAPI XLayout_IsEnableLayout(HELE hEle);
XC_API void WINAPI XLayout_EnableLayout(HELE hEle, BOOL bEnable);
XC_API void WINAPI XLayout_ShowLayoutFrame(HELE hEle, BOOL bEnable);
XC_API int  WINAPI XLayout_GetWidthIn(HELE hEle);
XC_API int  WINAPI XLayout_GetHeightIn(HELE hEle);
XC_API void WINAPI XLayoutBox_EnableHorizon(HXCGUI hLayoutBox, BOOL bEnable);
XC_API void WINAPI XLayoutBox_EnableAutoWrap(HXCGUI hLayoutBox, BOOL bEnable);
XC_API void WINAPI XLayoutBox_EnableOverflowHide(HXCGUI hLayoutBox, BOOL bEnable);
XC_API void WINAPI XLayoutBox_SetAlignH(HXCGUI hLayoutBox, layout_align_ nAlign);
XC_API void WINAPI XLayoutBox_SetAlignV(HXCGUI hLayoutBox, layout_align_ nAlign);
XC_API void WINAPI XLayoutBox_SetAlignBaseline(HXCGUI hLayoutBox, layout_align_axis_ nAlign);
XC_API void WINAPI XLayoutBox_SetSpace(HXCGUI hLayoutBox, int nSpace);
XC_API void WINAPI XLayoutBox_SetSpaceRow(HXCGUI hLayoutBox, int nSpace);

XC_API HELE WINAPI XLayoutFrame_Create(int x, int y, int cx, int cy, HXCGUI hParent);
XC_API void WINAPI XLayoutFrame_ShowLayoutFrame(HELE hEle, BOOL bEnable);
XC_API HELE WINAPI XListBox_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XListBox_EnableFixedRowHeight(HELE hEle, BOOL bEnable);
XC_API void WINAPI XListBox_EnableTemplateReuse(HELE hEle, BOOL bEnable);
XC_API void WINAPI XListBox_EnableVirtualTable(HELE hEle, BOOL bEnable);
XC_API void WINAPI XListBox_SetVirtualRowCount(HELE hEle, int nRowCount);
XC_API void WINAPI XListBox_SetDrawItemBkFlags(HELE hEle, int nFlags);
XC_API BOOL WINAPI XListBox_SetItemData(HELE hEle, int iItem, vint nUserData);
XC_API vint  WINAPI XListBox_GetItemData(HELE hEle, int iItem);
XC_API BOOL WINAPI XListBox_SetItemInfo(HELE hEle, int iItem, __in listBox_item_info_* pItem);
XC_API BOOL WINAPI XListBox_GetItemInfo(HELE hEle, int iItem, __out listBox_item_info_* pItem);

XC_API BOOL WINAPI XListBox_SetSelectItem(HELE hEle, int iItem);
XC_API int  WINAPI XListBox_GetSelectItem(HELE hEle);
XC_API BOOL WINAPI XListBox_AddSelectItem(HELE hEle, int iItem);
XC_API BOOL WINAPI XListBox_CancelSelectItem(HELE hEle, int iItem);
XC_API BOOL WINAPI XListBox_CancelSelectAll(HELE hEle);
XC_API int  WINAPI XListBox_GetSelectAll(HELE hEle, out_buffer_ int* pArray, int nArraySize);
XC_API int  WINAPI XListBox_GetSelectCount(HELE hEle);
XC_API int  WINAPI XListBox_GetItemMouseStay(HELE hEle);
XC_API BOOL WINAPI XListBox_SelectAll(HELE hEle);
XC_API void WINAPI XListBox_VisibleItem(HELE hEle, int iItem);
XC_API void WINAPI XListBox_GetVisibleRowRange(HELE hEle, __out int* piStart, __out int* piEnd);
XC_API void WINAPI XListBox_SetItemHeightDefault(HELE hEle, int nHeight, int nSelHeight);
XC_API void WINAPI XListBox_GetItemHeightDefault(HELE hEle, __out int* pHeight, __out int* pSelHeight);
XC_API int  WINAPI XListBox_GetItemIndexFromHXCGUI(HELE hEle, HXCGUI hXCGUI);
XC_API void WINAPI XListBox_SetRowSpace(HELE hEle, int nSpace);
XC_API int WINAPI  XListBox_GetRowSpace(HELE hEle);
XC_API int  WINAPI XListBox_HitTest(HELE hEle, POINT* pPt);
XC_API int  WINAPI XListBox_HitTestOffset(HELE hEle, POINT* pPt); //自动添加滚动视图偏移量
XC_API BOOL WINAPI XListBox_SetItemTemplateXML(HELE hEle, const wchar_t* pXmlFile);
XC_API BOOL WINAPI XListBox_SetItemTemplateXMLFromString(HELE hEle, const char* pStringXML);
XC_API BOOL WINAPI XListBox_SetItemTemplate(HELE hEle, HTEMP hTemp);
XC_API HXCGUI WINAPI XListBox_GetTemplateObject(HELE hEle, int iItem, int nTempItemID);
XC_API void WINAPI XListBox_EnableMultiSel(HELE hEle, BOOL bEnable);
XC_API HXCGUI WINAPI XListBox_CreateAdapter(HELE hEle);
XC_API void   WINAPI XListBox_BindAdapter(HELE hEle, HXCGUI hAdapter);
XC_API HXCGUI WINAPI XListBox_GetAdapter(HELE hEle);
XC_API void WINAPI XListBox_Sort(HELE hEle, int iColumnAdapter, BOOL bAscending);  //设置排序
XC_API void WINAPI XListBox_RefreshData(HELE hEle);
XC_API void WINAPI XListBox_RefreshItem(HELE hEle, int iItem);
XC_API int WINAPI XListBox_AddItemText(HELE hEle, const wchar_t* pText);
XC_API int WINAPI XListBox_AddItemTextEx(HELE hEle, const wchar_t* pName, const wchar_t* pText);
XC_API int WINAPI XListBox_AddItemImage(HELE hEle, HIMAGE hImage);
XC_API int WINAPI XListBox_AddItemImageEx(HELE hEle, const wchar_t* pName, HIMAGE hImage);
XC_API int WINAPI XListBox_InsertItemText(HELE hEle, int iItem, const wchar_t* pValue);
XC_API int WINAPI XListBox_InsertItemTextEx(HELE hEle, int iItem, const wchar_t* pName, const wchar_t* pValue);
XC_API int WINAPI XListBox_InsertItemImage(HELE hEle, int iItem, HIMAGE hImage);
XC_API int WINAPI XListBox_InsertItemImageEx(HELE hEle, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XListBox_SetItemText(HELE hEle, int iItem, int iColumn, const wchar_t* pText);
XC_API BOOL WINAPI XListBox_SetItemTextEx(HELE hEle, int iItem, const wchar_t* pName, const wchar_t* pText);
XC_API BOOL WINAPI XListBox_SetItemImage(HELE hEle, int iItem, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XListBox_SetItemImageEx(HELE hEle, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XListBox_SetItemInt(HELE hEle, int iItem, int iColumn, int nValue);
XC_API BOOL WINAPI XListBox_SetItemIntEx(HELE hEle, int iItem, const wchar_t* pName, int nValue);
XC_API BOOL WINAPI XListBox_SetItemFloat(HELE hEle, int iItem, int iColumn, float fFloat);
XC_API BOOL WINAPI XListBox_SetItemFloatEx(HELE hEle, int iItem, const wchar_t* pName, float fFloat);
XC_API const wchar_t* WINAPI XListBox_GetItemText(HELE hEle, int iItem, int iColumn);
XC_API const wchar_t* WINAPI XListBox_GetItemTextEx(HELE hEle, int iItem, const wchar_t* pName);
XC_API HIMAGE WINAPI XListBox_GetItemImage(HELE hEle, int iItem, int iColumn);
XC_API HIMAGE WINAPI XListBox_GetItemImageEx(HELE hEle, int iItem, const wchar_t* pName);
XC_API BOOL WINAPI XListBox_GetItemInt(HELE hEle, int iItem, int iColumn, __out int* pOutValue);
XC_API BOOL WINAPI XListBox_GetItemIntEx(HELE hEle, int iItem, const wchar_t* pName, __out int* pOutValue);
XC_API BOOL WINAPI XListBox_GetItemFloat(HELE hEle, int iItem, int iColumn, __out float* pOutValue);
XC_API BOOL WINAPI XListBox_GetItemFloatEx(HELE hEle, int iItem, const wchar_t* pName, __out float* pOutValue);
XC_API BOOL WINAPI XListBox_DeleteItem(HELE hEle, int iItem);
XC_API BOOL WINAPI XListBox_DeleteItemEx(HELE hEle, int iItem, int nCount);
XC_API void WINAPI XListBox_DeleteItemAll(HELE hEle);
XC_API void WINAPI XListBox_DeleteColumnAll(HELE hEle);
XC_API int WINAPI XListBox_GetCount_AD(HELE hEle);
XC_API int WINAPI XListBox_GetCountColumn_AD(HELE hEle);
XC_API HTEMP WINAPI XTemp_Load(listItemTemp_type_ nType, const wchar_t* pFileName);  //加载模板 返回模板对象
XC_API HTEMP WINAPI XTemp_LoadZip(listItemTemp_type_ nType, const wchar_t* pZipFile, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API HTEMP WINAPI XTemp_LoadZipMem(listItemTemp_type_ nType, void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API BOOL  WINAPI XTemp_LoadEx(listItemTemp_type_ nType, const wchar_t* pFileName, __out HTEMP* pOutTemp1, __out HTEMP* pOutTemp2);
XC_API BOOL  WINAPI XTemp_LoadZipEx(listItemTemp_type_ nType, const wchar_t* pZipFile, const wchar_t* pFileName, const wchar_t* pPassword, __out HTEMP* pOutTemp1, __out HTEMP* pOutTemp2);
XC_API BOOL  WINAPI XTemp_LoadZipMemEx(listItemTemp_type_ nType, void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword, __out HTEMP* pOutTemp1, __out HTEMP* pOutTemp2);
XC_API HTEMP WINAPI XTemp_LoadFromString(listItemTemp_type_ nType, const char* pStringXML);  //加载模板,从内存, 返回模板对象
XC_API BOOL  WINAPI XTemp_LoadFromStringEx(listItemTemp_type_ nType, const char* pStringXML, __out HTEMP* pOutTemp1, __out HTEMP* pOutTemp2);
XC_API listItemTemp_type_ WINAPI XTemp_GetType(HTEMP hTemp);
XC_API BOOL  WINAPI XTemp_Destroy(HTEMP hTemp);
XC_API HTEMP WINAPI XTemp_Create(listItemTemp_type_ nType);
XC_API BOOL  WINAPI XTemp_AddNodeRoot(HTEMP hTemp, void* pNode);
XC_API BOOL  WINAPI XTemp_AddNode(void* pParentNode, void* pNode);
XC_API void* WINAPI XTemp_CreateNode(XC_OBJECT_TYPE nType);
XC_API BOOL  WINAPI XTemp_SetNodeAttribute(void* pNode, const wchar_t* pName, const wchar_t* pAttr);
XC_API BOOL  WINAPI XTemp_SetNodeAttributeEx(void* pNode, int itemID, const wchar_t* pName, const wchar_t* pAttr);
XC_API void* WINAPI XTemp_List_GetNode(HTEMP hTemp, int index);
XC_API void* WINAPI XTemp_GetNode(void* pNode, int itemID);
XC_API void* WINAPI XTemp_CloneNode(void* pNode);
XC_API HELE WINAPI XList_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int WINAPI XList_AddColumn(HELE hEle, int width); //增加列
XC_API int WINAPI XList_InsertColumn(HELE hEle, int width, int iItem);
XC_API void WINAPI XList_EnableMultiSel(HELE hEle, BOOL bEnable);
XC_API void WINAPI XList_EnableDragChangeColumnWidth(HELE hEle, BOOL bEnable);
XC_API void WINAPI XList_EnableVScrollBarTop(HELE hEle, BOOL bTop);
XC_API void WINAPI XList_EnableItemBkFullRow(HELE hEle, BOOL bFull);
XC_API void WINAPI XList_EnableFixedRowHeight(HELE hEle, BOOL bEnable);
XC_API void WINAPI XList_EnableTemplateReuse(HELE hEle, BOOL bEnable);
XC_API void WINAPI XList_EnableVirtualTable(HELE hEle, BOOL bEnable);
XC_API void WINAPI XList_SetVirtualRowCount(HELE hEle, int nRowCount);
XC_API void WINAPI XList_SetSort(HELE hEle, int iColumn, int iColumnAdapter, BOOL bEnable);//设置排序
XC_API void WINAPI XList_SetDrawItemBkFlags(HELE hEle, int style);
XC_API void WINAPI XList_SetColumnWidth(HELE hEle, int iItem, int width);
XC_API void WINAPI XList_SetColumnMinWidth(HELE hEle, int iItem, int width);
XC_API void WINAPI XList_SetColumnWidthFixed(HELE hEle, int iColumn, BOOL bFixed);
XC_API int  WINAPI XList_GetColumnWidth(HELE hEle, int iColumn);  //获取列宽
XC_API int  WINAPI XList_GetColumnCount(HELE hEle);  //获取列数量
XC_API BOOL WINAPI XList_DeleteColumn(HELE hEle, int iItem);
XC_API void WINAPI XList_DeleteColumnAll(HELE hEle);
XC_API BOOL WINAPI XList_SetItemData(HELE hEle, int iItem, int iSubItem, vint data);
XC_API vint WINAPI XList_GetItemData(HELE hEle, int iItem, int iSubItem);
XC_API BOOL WINAPI XList_SetSelectItem(HELE hEle, int iItem);
XC_API int  WINAPI XList_GetSelectItem(HELE hEle);
XC_API int  WINAPI XList_GetSelectItemCount(HELE hEle);
XC_API BOOL WINAPI XList_AddSelectItem(HELE hEle, int iItem);
XC_API void WINAPI XList_SetSelectAll(HELE hEle);
XC_API int  WINAPI XList_GetSelectAll(HELE hEle, out_buffer_ int* pArray, int nArraySize);
XC_API void WINAPI XList_VisibleItem(HELE hEle, int iItem);
XC_API BOOL WINAPI XList_CancelSelectItem(HELE hEle, int iItem);
XC_API void WINAPI XList_CancelSelectAll(HELE hEle);
XC_API HELE WINAPI XList_GetHeaderHELE(HELE hEle);
XC_API void WINAPI XList_BindAdapter(HELE hEle, HXCGUI hAdapter);
XC_API void WINAPI XList_BindAdapterHeader(HELE hEle, HXCGUI hAdapter);
XC_API HXCGUI WINAPI XList_CreateAdapter(HELE hEle, int col_extend_count = 0);
XC_API HXCGUI WINAPI XList_CreateAdapterHeader(HELE hEle);
XC_API HXCGUI WINAPI XList_GetAdapter(HELE hEle);
XC_API HXCGUI WINAPI XList_GetAdapterHeader(HELE hEle);
XC_API BOOL WINAPI XList_SetItemTemplateXML(HELE hEle, const wchar_t* pXmlFile);
XC_API BOOL WINAPI XList_SetItemTemplateXMLFromString(HELE hEle, const char* pStringXML);
XC_API BOOL WINAPI XList_SetItemTemplate(HELE hEle, HTEMP hTemp);
XC_API HXCGUI WINAPI XList_GetTemplateObject(HELE hEle, int iItem, int iSubItem, int nTempItemID); //通过模板项ID,获取实例化模板项ID对应的对象.
XC_API int    WINAPI XList_GetItemIndexFromHXCGUI(HELE hEle, HXCGUI hXCGUI);
XC_API HXCGUI WINAPI XList_GetHeaderTemplateObject(HELE hEle, int iItem, int nTempItemID);
XC_API int    WINAPI XList_GetHeaderItemIndexFromHXCGUI(HELE hEle, HXCGUI hXCGUI);
XC_API void WINAPI XList_SetHeaderHeight(HELE hEle, int height);
XC_API int  WINAPI XList_GetHeaderHeight(HELE hEle);
XC_API void WINAPI XList_GetVisibleRowRange(HELE hEle, __out int* piStart, __out int* piEnd);

XC_API void WINAPI XList_SetItemHeightDefault(HELE hEle, int nHeight, int nSelHeight);
XC_API void WINAPI XList_GetItemHeightDefault(HELE hEle, __out int* pHeight, __out int* pSelHeight);
XC_API void WINAPI XList_SetRowSpace(HELE hEle, int nSpace);
XC_API int  WINAPI XList_GetRowSpace(HELE hEle);
XC_API void WINAPI XList_SetLockColumnLeft(HELE hEle, int iColumn);
XC_API void WINAPI XList_SetLockColumnRight(HELE hEle, int iColumn);
XC_API void WINAPI XList_SetLockRowBottom(HELE hEle, BOOL bLock);
XC_API void WINAPI XList_SetLockRowBottomOverlap(HELE hEle, BOOL bOverlap); //设置锁定行可重叠
XC_API BOOL WINAPI XList_HitTest(HELE hEle, POINT* pPt, __out int* piItem, __out int* piSubItem);
XC_API BOOL WINAPI XList_HitTestOffset(HELE hEle, POINT* pPt, __out int* piItem, __out int* piSubItem);
XC_API void WINAPI XList_RefreshData(HELE hEle);
XC_API void WINAPI XList_RefreshItem(HELE hEle, int iItem);
XC_API int WINAPI XList_AddColumnText(HELE hEle, int nWidth, const wchar_t* pName, const wchar_t* pText);
XC_API int WINAPI XList_AddColumnImage(HELE hEle, int nWidth, const wchar_t* pName, HIMAGE hImage);
XC_API int WINAPI XList_AddItemText(HELE hEle, const wchar_t* pText);
XC_API int WINAPI XList_AddItemTextEx(HELE hEle, const wchar_t* pName, const wchar_t* pText);
XC_API int WINAPI XList_AddItemImage(HELE hEle, HIMAGE hImage);
XC_API int WINAPI XList_AddItemImageEx(HELE hEle, const wchar_t* pName, HIMAGE hImage);
XC_API int WINAPI XList_InsertItemText(HELE hEle, int iItem, const wchar_t* pValue);
XC_API int WINAPI XList_InsertItemTextEx(HELE hEle, int iItem, const wchar_t* pName, const wchar_t* pValue);
XC_API int WINAPI XList_InsertItemImage(HELE hEle, int iItem, HIMAGE hImage);
XC_API int WINAPI XList_InsertItemImageEx(HELE hEle, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XList_SetItemText(HELE hEle, int iItem, int iColumn, const wchar_t* pText);
XC_API BOOL WINAPI XList_SetItemTextEx(HELE hEle, int iItem, const wchar_t* pName, const wchar_t* pText);
XC_API BOOL WINAPI XList_SetItemImage(HELE hEle, int iItem, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XList_SetItemImageEx(HELE hEle, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XList_SetItemInt(HELE hEle, int iItem, int iColumn, int nValue);
XC_API BOOL WINAPI XList_SetItemIntEx(HELE hEle, int iItem, const wchar_t* pName, int nValue);
XC_API BOOL WINAPI XList_SetItemFloat(HELE hEle, int iItem, int iColumn, float fFloat);
XC_API BOOL WINAPI XList_SetItemFloatEx(HELE hEle, int iItem, const wchar_t* pName, float fFloat);
XC_API const wchar_t* WINAPI XList_GetItemText(HELE hEle, int iItem, int iColumn);
XC_API const wchar_t* WINAPI XList_GetItemTextEx(HELE hEle, int iItem, const wchar_t* pName);
XC_API HIMAGE WINAPI XList_GetItemImage(HELE hEle, int iItem, int iColumn);
XC_API HIMAGE WINAPI XList_GetItemImageEx(HELE hEle, int iItem, const wchar_t* pName);
XC_API BOOL WINAPI XList_GetItemInt(HELE hEle, int iItem, int iColumn, __out int* pOutValue);
XC_API BOOL WINAPI XList_GetItemIntEx(HELE hEle, int iItem, const wchar_t* pName, __out int* pOutValue);
XC_API BOOL WINAPI XList_GetItemFloat(HELE hEle, int iItem, int iColumn, __out float* pOutValue);
XC_API BOOL WINAPI XList_GetItemFloatEx(HELE hEle, int iItem, const wchar_t* pName, __out float* pOutValue);
XC_API BOOL WINAPI XList_DeleteItem(HELE hEle, int iItem);
XC_API BOOL WINAPI XList_DeleteItemEx(HELE hEle, int iItem, int nCount);
XC_API void WINAPI XList_DeleteItemAll(HELE hEle);
XC_API void WINAPI XList_DeleteColumnAll_AD(HELE hEle);
XC_API int  WINAPI XList_GetCount_AD(HELE hEle);
XC_API int  WINAPI XList_GetCountColumn_AD(HELE hEle);
XC_API HELE WINAPI XListView_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API HXCGUI WINAPI XListView_CreateAdapter(HELE hEle);
XC_API void   WINAPI XListView_BindAdapter(HELE hEle, HXCGUI hAdapter);
XC_API HXCGUI WINAPI XListView_GetAdapter(HELE hEle);
XC_API BOOL WINAPI XListView_SetItemTemplateXML(HELE hEle, const wchar_t* pXmlFile);
XC_API BOOL WINAPI XListView_SetItemTemplateXMLFromString(HELE hEle, const char* pStringXML);
XC_API BOOL WINAPI XListView_SetItemTemplate(HELE hEle, HTEMP hTemp);
XC_API HXCGUI WINAPI XListView_GetTemplateObject(HELE hEle, int iGroup, int iItem, int nTempItemID);
XC_API HXCGUI WINAPI XListView_GetTemplateObjectGroup(HELE hEle, int iGroup, int nTempItemID);
XC_API BOOL  WINAPI XListView_GetItemIDFromHXCGUI(HELE hEle, HXCGUI hXCGUI, __out int* piGroup, __out int* piItem);
XC_API BOOL WINAPI XListView_HitTest(HELE hEle, __in POINT* pPt, __out int* pOutGroup, __out int* pOutItem);
XC_API BOOL WINAPI XListView_HitTestOffset(HELE hEle, __in POINT* pPt, __out int* pOutGroup, __out int* pOutItem); //自动添加滚动视图偏移量
XC_API void WINAPI XListView_EnableMultiSel(HELE hEle, BOOL bEnable);
XC_API void WINAPI XListView_EnableTemplateReuse(HELE hEle, BOOL bEnable);
XC_API void WINAPI XListView_EnableVirtualTable(HELE hEle, BOOL bEnable);
XC_API BOOL WINAPI XListView_SetVirtualItemCount(HELE hEle, int iGroup, int nCount);
XC_API void WINAPI XListView_SetDrawItemBkFlags(HELE hEle, int nFlags);
XC_API BOOL WINAPI XListView_SetSelectItem(HELE hEle, int iGroup, int iItem);
XC_API BOOL WINAPI XListView_GetSelectItem(HELE hEle, __out int* piGroup, __out int* piItem);
XC_API BOOL WINAPI XListView_AddSelectItem(HELE hEle, int iGroup, int iItem);
XC_API void WINAPI XListView_VisibleItem(HELE hEle, int iGroup, int iItem);
XC_API void WINAPI XListView_GetVisibleItemRange(HELE hEle, __out int* piGroup1, __out int* piGroup2, __out int* piStartGroup, __out int* piStartItem, __out int* piEndGroup, __out int* piEndItem);
XC_API int  WINAPI XListView_GetSelectItemCount(HELE hEle);
XC_API int  WINAPI XListView_GetSelectAll(HELE hEle, out_buffer_ listView_item_id_* pArray, int nArraySize);
XC_API void WINAPI XListView_SetSelectAll(HELE hEle);
XC_API void WINAPI XListView_CancelSelectAll(HELE hEle);
XC_API void WINAPI XListView_SetColumnSpace(HELE hEle, int space); //设置列间隔
XC_API void WINAPI XListView_SetRowSpace(HELE hEle, int space); //设置行间隔
XC_API void WINAPI XListView_SetItemSize(HELE hEle, int width, int height);
XC_API void WINAPI XListView_GetItemSize(HELE hEle, SIZE* pSize);
XC_API void WINAPI XListView_SetGroupHeight(HELE hEle, int height);
XC_API int  WINAPI XListView_GetGroupHeight(HELE hEle);
XC_API void WINAPI XListView_SetGroupUserData(HELE hEle, int iGroup, vint nData);
XC_API void WINAPI XListView_SetItemUserData(HELE hEle, int iGroup, int iItem, vint nData);
XC_API vint WINAPI XListView_GetGroupUserData(HELE hEle, int iGroup);
XC_API vint WINAPI XListView_GetItemUserData(HELE hEle, int iGroup, int iItem);

XC_API void WINAPI XListView_RefreshData(HELE hEle);
XC_API void WINAPI XListView_RefreshItem(HELE hEle, int iGroup, int iItem);
XC_API BOOL WINAPI XListView_ExpandGroup(HELE hEle, int iGroup, BOOL bExpand);
XC_API int  WINAPI XListView_Group_AddColumn(HELE hEle, const wchar_t* pName);
XC_API int  WINAPI XListView_Group_AddItemText(HELE hEle, const wchar_t* pValue, int iPos);
XC_API int  WINAPI XListView_Group_AddItemTextEx(HELE hEle, const wchar_t* pName, const wchar_t* pValue, int iPos);
XC_API int  WINAPI XListView_Group_AddItemImage(HELE hEle, HIMAGE hImage, int iPos);
XC_API int  WINAPI XListView_Group_AddItemImageEx(HELE hEle, const wchar_t* pName, HIMAGE hImage, int iPos);
XC_API BOOL WINAPI XListView_Group_SetText(HELE hEle, int iGroup, int iColumn, const wchar_t* pValue);
XC_API BOOL WINAPI XListView_Group_SetTextEx(HELE hEle, int iGroup, const wchar_t* pName, const wchar_t* pValue);
XC_API BOOL WINAPI XListView_Group_SetImage(HELE hEle, int iGroup, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XListView_Group_SetImageEx(HELE hEle, int iGroup, const wchar_t* pName, HIMAGE hImage);
XC_API int  WINAPI XListView_Group_GetCount(HELE hEle);
XC_API int  WINAPI XListView_Item_GetCount(HELE hEle, int iGroup);
XC_API int  WINAPI XListView_Item_AddColumn(HELE hEle, const wchar_t* pName);  //增加列
XC_API int  WINAPI XListView_Item_AddItemText(HELE hEle, int iGroup, const wchar_t* pValue, int iPos);
XC_API int  WINAPI XListView_Item_AddItemTextEx(HELE hEle, int iGroup, const wchar_t* pName, const wchar_t* pValue, int iPos);
XC_API int  WINAPI XListView_Item_AddItemImage(HELE hEle, int iGroup, HIMAGE hImage, int iPos);
XC_API int  WINAPI XListView_Item_AddItemImageEx(HELE hEle, int iGroup, const wchar_t* pName, HIMAGE hImage, int iPos);
XC_API BOOL WINAPI XListView_Item_SetText(HELE hEle, int iGroup, int iItem, int iColumn, const wchar_t* pValue);
XC_API BOOL WINAPI XListView_Item_SetTextEx(HELE hEle, int iGroup, int iItem, const wchar_t* pName, const wchar_t* pValue);
XC_API BOOL WINAPI XListView_Item_SetImage(HELE hEle, int iGroup, int iItem, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XListView_Item_SetImageEx(HELE hEle, int iGroup, int iItem, const wchar_t* pName, HIMAGE hImage);
XC_API BOOL WINAPI XListView_Group_DeleteItem(HELE hEle, int iGroup);
XC_API void WINAPI XListView_Group_DeleteAllChildItem(HELE hEle, int iGroup);
XC_API BOOL WINAPI XListView_Item_DeleteItem(HELE hEle, int iGroup, int iItem);
XC_API void WINAPI XListView_DeleteAll(HELE hEle);
XC_API void WINAPI XListView_DeleteAllGroup(HELE hEle);
XC_API void WINAPI XListView_DeleteAllItem(HELE hEle);
XC_API void WINAPI XListView_DeleteColumnGroup(HELE hEle, int iColumn);
XC_API void WINAPI XListView_DeleteColumnItem(HELE hEle, int iColumn);
XC_API const wchar_t* WINAPI XListView_Item_GetTextEx(HELE hEle, int iGroup, int iItem, const wchar_t* pName);
XC_API HIMAGE WINAPI XListView_Item_GetImageEx(HELE hEle, int iGroup, int iItem, const wchar_t* pName);
XC_API HELE WINAPI XMenuBar_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int  WINAPI XMenuBar_AddButton(HELE hEle, const wchar_t* pText);     //增加弹出菜单按钮
XC_API void WINAPI XMenuBar_SetButtonHeight(HELE hEle, int height);
XC_API HMENUX WINAPI XMenuBar_GetMenu(HELE hEle, int nIndex);
XC_API BOOL WINAPI XMenuBar_DeleteButton(HELE hEle, int nIndex); //删除菜单项并且销毁,同时该按钮下的弹出菜单也被销毁
XC_API void WINAPI XMenuBar_EnableAutoWidth(HELE hEle, BOOL bEnable);
XC_API HMENUX WINAPI XMenu_Create();
XC_API void WINAPI XMenu_AddItem(HMENUX hMenu, int nID, const wchar_t* pText, int parentId = XC_ID_ROOT, int nFlags = 0); //添加菜单项
XC_API void WINAPI XMenu_AddItemIcon(HMENUX hMenu, int nID, const wchar_t* pText, int nParentID, HIMAGE hImage, int nFlags = 0);
XC_API void WINAPI XMenu_InsertItem(HMENUX hMenu, int nID, const wchar_t* pText, int nFlags, int insertID);
XC_API void WINAPI XMenu_InsertItemIcon(HMENUX hMenu, int nID, const wchar_t* pText, HIMAGE hIcon, int nFlags, int insertID);
XC_API int  WINAPI XMenu_GetFirstChildItem(HMENUX hMenu, int nID);
XC_API int  WINAPI XMenu_GetEndChildItem(HMENUX hMenu, int nID);
XC_API int  WINAPI XMenu_GetPrevSiblingItem(HMENUX hMenu, int nID);
XC_API int  WINAPI XMenu_GetNextSiblingItem(HMENUX hMenu, int nID);
XC_API int  WINAPI XMenu_GetParentItem(HMENUX hMenu, int nID);
XC_API void WINAPI XMenu_SetAutoDestroy(HMENUX hMenu, BOOL bAuto); //是否自动销毁对象,默认弹出菜单关闭后自动销毁
XC_API void WINAPI XMenu_EnableDrawBackground(HMENUX hMenu, BOOL bEnable); //是否有用户绘制菜单背景
XC_API void WINAPI XMenu_EnableDrawItem(HMENUX hMenu, BOOL bEnable);
XC_API BOOL WINAPI XMenu_Popup(HMENUX hMenu, HWND hParentWnd, int x, int y, HELE hParentEle = NULL, menu_popup_position_ nPosition = menu_popup_position_left_top); //弹出菜单
XC_API void WINAPI XMenu_DestroyMenu(HMENUX hMenu);
XC_API void WINAPI XMenu_CloseMenu(HMENUX hMenu);
XC_API void WINAPI XMenu_SetBkImage(HMENUX hMenu, HIMAGE hImage);
XC_API BOOL WINAPI XMenu_SetItemText(HMENUX hMenu, int nID, const wchar_t* pText); //设置项文本
XC_API const wchar_t* WINAPI XMenu_GetItemText(HMENUX hMenu, int nID);
XC_API int  WINAPI XMenu_GetItemTextLength(HMENUX hMenu, int nID);
XC_API BOOL WINAPI XMenu_SetItemIcon(HMENUX hMenu, int nID, HIMAGE hIcon);
XC_API BOOL WINAPI XMenu_SetItemFlags(HMENUX hMenu, int nID, int uFlags);   //设置项属性
XC_API void WINAPI XMenu_SetItemHeight(HMENUX hMenu, int height); //设置菜单项高度
XC_API int  WINAPI XMenu_GetItemHeight(HMENUX hMenu);
XC_API void WINAPI XMenu_SetBorderColor(HMENUX hMenu, COLORREF crColor);
XC_API void WINAPI XMenu_SetBorderSize(HMENUX hMenu, int nLeft, int nTop, int nRight, int nBottom);
XC_API int  WINAPI XMenu_GetLeftWidth(HMENUX hMenu); //获取左侧宽度
XC_API int  WINAPI XMenu_GetLeftSpaceText(HMENUX hMenu);  //获取菜单项文本左间隔
XC_API int  WINAPI XMenu_GetItemCount(HMENUX hMenu); //获取菜单项数量,包含子菜单项
XC_API BOOL WINAPI XMenu_SetItemCheck(HMENUX hMenu, int nID, BOOL bCheck);
XC_API BOOL WINAPI XMenu_IsItemCheck(HMENUX hMenu, int nID);
XC_API HWINDOW WINAPI XModalWnd_Create(int nWidth, int nHeight, const wchar_t* pTitle, HWND hWndParent, int XCStyle = window_style_modal);
XC_API void WINAPI XModalWnd_EnableAutoClose(HWINDOW hWindow, BOOL bEnable);
XC_API void WINAPI XModalWnd_EnableEscClose(HWINDOW hWindow, BOOL bEnable);
XC_API int  WINAPI XModalWnd_DoModal(HWINDOW hWindow);     //启动模态窗口
XC_API void WINAPI XModalWnd_EndModal(HWINDOW hWindow, int nResult); //终止
XC_API HELE WINAPI XPane_Create(const wchar_t* pName, int nWidth, int nHeight, HWINDOW hFrameWnd = NULL);
XC_API void WINAPI XPane_SetView(HELE hEle, HELE hView);
XC_API BOOL WINAPI XPane_IsShowPane(HELE hEle); //判断窗格是否隐藏
XC_API void WINAPI XPane_SetSize(HELE hEle, int nWidth, int nHeight);
XC_API pane_state_ WINAPI XPane_GetState(HELE hEle);
XC_API void WINAPI XPane_GetViewRect(HELE hEle, __out RECT* pRect);
XC_API void WINAPI XPane_SetTitle(HELE hEle, wchar_t* pTitle);
XC_API const wchar_t* WINAPI XPane_GetTitle(HELE hEle);
XC_API void WINAPI XPane_SetCaptionHeight(HELE hEle, int nHeight);
XC_API int  WINAPI XPane_GetCaptionHeight(HELE hEle);
//XC_API void  WINAPI XPane_HidePane(HELE hEle);     //隐藏窗格
//XC_API void  WINAPI XPane_ShowPane(HELE hEle);     //隐藏-显示窗格,并切换窗格
XC_API void  WINAPI XPane_DockPane(HELE hEle);      //停靠窗格,自动隐藏
XC_API void  WINAPI XPane_LockPane(HELE hEle);      //锁定窗格
XC_API void  WINAPI XPane_FloatPane(HELE hEle);     //弹出窗格,当在码头上
XC_API void  WINAPI XPane_DrawPane(HELE hEle, HDRAW hDraw);
XC_API BOOL  WINAPI XPane_SetSelect(HELE hEle);   //如果在组中,使其选择
XC_API BOOL WINAPI XFloatWnd_EnableCaptionContent(HWINDOW hWindow, BOOL bEnable);
XC_API HXCGUI WINAPI XFloatWnd_GetCaptionLayout(HWINDOW hWindow);
XC_API HXCGUI WINAPI XFloatWnd_GetCaptionShapeText(HWINDOW hWindow);
XC_API HELE   WINAPI XFloatWnd_GetCaptionButtonClose(HWINDOW hWindow);
XC_API void  WINAPI XFloatWnd_SetTitle(HWINDOW hWindow, const wchar_t* pTitle);
XC_API const wchar_t* WINAPI XFloatWnd_GetTitle(HWINDOW hWindow);
XC_API HELE WINAPI XProgBar_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XProgBar_SetRange(HELE hEle, int range);
XC_API int  WINAPI XProgBar_GetRange(HELE hEle);

XC_API void WINAPI XProgBar_SetPos(HELE hEle, int pos);
XC_API int  WINAPI XProgBar_GetPos(HELE hEle);
XC_API void WINAPI XProgBar_EnableHorizon(HELE hEle, BOOL bHorizon);
XC_API void WINAPI XProgBar_SetImageLoad(HELE hEle, HIMAGE hImage);
XC_API HELE WINAPI XPGrid_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int  WINAPI XPGrid_AddItem(HELE hEle, const wchar_t* pName, propertyGrid_item_type_ nType, int nParentID = XC_ID_ROOT); //添加项
XC_API int  WINAPI XPGrid_AddItemString(HELE hEle, const wchar_t* pName, const wchar_t* pValue, int nParentID = XC_ID_ROOT);
XC_API int  WINAPI XPGrid_AddItemEle(HELE hEle, HELE hElePanel, int nParentID = XC_ID_ROOT);
XC_API void WINAPI XPGrid_DeleteAll(HELE hEle);
XC_API HELE WINAPI XPGrid_GetItemHELE(HELE hEle, int nItemID);
XC_API void WINAPI XPGrid_SetWidth(HELE hEle, int nWidth);
XC_API BOOL WINAPI XPGrid_SetItemValue(HELE hEle, int nItemID, const wchar_t* pValue);
XC_API BOOL WINAPI XPGrid_SetItemValueInt(HELE hEle, int nItemID, int nValue);
XC_API BOOL WINAPI XPGrid_SetItemData(HELE hEle, int nItemID, vint nUserData);
XC_API vint WINAPI XPGrid_GetItemData(HELE hEle, int nItemID);
XC_API const wchar_t* WINAPI XPGrid_GetItemValue(HELE hEle, int nItemID);
XC_API int  WINAPI XPGrid_HitTest(HELE hEle, POINT* pPt, BOOL* pbExpandButton);
XC_API int  WINAPI XPGrid_HitTestOffset(HELE hEle, POINT* pPt, BOOL* pbExpandButton);
XC_API BOOL WINAPI XPGrid_ExpandItem(HELE hEle, int nItemID, BOOL bExpand);//展开项
XC_API int  WINAPI XPGrid_GetSelItem(HELE hEle);
XC_API BOOL WINAPI XPGrid_SetSelItem(HELE hEle, int nItemID);
XC_API void WINAPI XPGrid_SetDrawItemBkFlags(HELE hEle, int nFlags);
XC_API void   WINAPI XRes_EnableDelayLoad(BOOL bEnable);
XC_API void   WINAPI XRes_SetLoadFileCallback(funLoadFile pFun);
XC_API int    WINAPI XRes_GetIDValue(const wchar_t* pName);  //获取资源ID值
XC_API HIMAGE WINAPI XRes_GetImage(const wchar_t* pName);  //获取资源图片
XC_API HIMAGE WINAPI XRes_GetImageEx(const wchar_t* pFileName, const wchar_t* pName); //获取资源图片
XC_API COLORREF WINAPI XRes_GetColor(const wchar_t* pName);  //获取资源颜色
XC_API HFONTX   WINAPI XRes_GetFont(const wchar_t* pName);  //获取资源字体
XC_API HBKM     WINAPI XRes_GetBkM(const wchar_t* pName);  //获取资源背景信息
XC_API HELE WINAPI XEditColor_Create(int x, int y, int cx, int cy, HXCGUI hParent);
XC_API void WINAPI XEditColor_SetColor(HELE hEle, COLORREF color);//设置颜色
XC_API COLORREF WINAPI XEditColor_GetColor(HELE hEle); //获取颜色RGB值
XC_API HELE WINAPI XEditSet_Create(int x, int y, int cx, int cy, HXCGUI hParent);
XC_API HELE WINAPI XEditFile_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XEditFile_SetOpenFileType(HELE hEle, const wchar_t* pType); //设置打开文件类型
XC_API void WINAPI XEditFile_SetDefaultFile(HELE hEle, const wchar_t* pFile); //设置默认目录文件
XC_API void WINAPI XEditFile_SetRelativeDir(HELE hEle, const wchar_t* pDir); //TODO:设置相对路径
XC_API HELE WINAPI XEditFolder_Create(int x, int y, int cx, int cy, HXCGUI hParent);
XC_API void WINAPI XEditFolder_SetDefaultDir(HELE hEle, const wchar_t* pDir);  //设置默认目录
XC_API HELE WINAPI XSBar_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XSBar_SetRange(HELE hEle, int range);
XC_API int  WINAPI XSBar_GetRange(HELE hEle);
XC_API void  WINAPI XSBar_ShowButton(HELE hEle, BOOL bShow);
XC_API void WINAPI XSBar_SetSliderLength(HELE hEle, int length); //设置滑块长度
XC_API void WINAPI XSBar_SetSliderMinLength(HELE hEle, int minLength); //设置滑块最小长度
XC_API void WINAPI XSBar_SetSliderPadding(HELE hEle, int nPadding);
XC_API BOOL WINAPI XSBar_EnableHorizon(HELE hEle, BOOL bHorizon);  //水平显示或垂直
XC_API int  WINAPI XSBar_GetSliderMaxLength(HELE hEle);
XC_API BOOL WINAPI XSBar_ScrollUp(HELE hEle);       //向左滚动
XC_API BOOL WINAPI XSBar_ScrollDown(HELE hEle);     //向右滚动
XC_API BOOL WINAPI XSBar_ScrollTop(HELE hEle);      //滚动到顶部
XC_API BOOL WINAPI XSBar_ScrollBottom(HELE hEle);   //滚动到底部
XC_API BOOL WINAPI XSBar_ScrollPos(HELE hEle, int pos); //滚动到指定点
XC_API HELE WINAPI XSBar_GetButtonUp(HELE hEle);
XC_API HELE WINAPI XSBar_GetButtonDown(HELE hEle);
XC_API HELE WINAPI XSBar_GetButtonSlider(HELE hEle);
XC_API HELE WINAPI XSView_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API BOOL WINAPI XSView_SetTotalSize(HELE hEle, int cx, int cy); //设置视图内容总大小(不包含边框间隔)
XC_API void WINAPI XSView_GetTotalSize(HELE hEle, __out SIZE* pSize);  //获取设置的内容大小
XC_API BOOL WINAPI XSView_SetLineSize(HELE hEle, int nWidth, int nHeight);
XC_API void WINAPI XSView_GetLineSize(HELE hEle, __out SIZE* pSize);
XC_API void WINAPI XSView_SetScrollBarSize(HELE hEle, int size); //设置滚动条大小
XC_API int  WINAPI XSView_GetViewPosH(HELE hEle);   //获取视口原点X坐标
XC_API int  WINAPI XSView_GetViewPosV(HELE hEle);   //获取视口原点Y坐标
XC_API int  WINAPI XSView_GetViewWidth(HELE hEle);
XC_API int  WINAPI XSView_GetViewHeight(HELE hEle);
XC_API void WINAPI XSView_GetViewRect(HELE hEle, __out RECT* pRect); //获取视口坐标(不含边框间隔),left为视口左间隔大小,top为视口上间隔大小,非(0,0).
XC_API HELE WINAPI XSView_GetScrollBarH(HELE hEle); //获取水平滚动条
XC_API HELE WINAPI XSView_GetScrollBarV(HELE hEle); //获取垂直滚动条

XC_API BOOL WINAPI XSView_ScrollPosH(HELE hEle, int pos); //滚动到指定点
XC_API BOOL WINAPI XSView_ScrollPosV(HELE hEle, int pos); //滚动到指定点
XC_API BOOL WINAPI XSView_ScrollPosXH(HELE hEle, int posX); //滚动到指定坐标
XC_API BOOL WINAPI XSView_ScrollPosYV(HELE hEle, int posY); //滚动到指定坐标
XC_API void WINAPI XSView_ShowSBarH(HELE hEle, BOOL bShow); //启用水平滚动条
XC_API void WINAPI XSView_ShowSBarV(HELE hEle, BOOL bShow); //启用垂直滚动条
XC_API void WINAPI XSView_EnableAutoShowScrollBar(HELE hEle, BOOL bEnable);
XC_API BOOL WINAPI XSView_ScrollLeftLine(HELE hEle);    //向左滚动
XC_API BOOL WINAPI XSView_ScrollRightLine(HELE hEle);   //向右滚动
XC_API BOOL WINAPI XSView_ScrollTopLine(HELE hEle);     //向上滚动
XC_API BOOL WINAPI XSView_ScrollBottomLine(HELE hEle);    //向下滚动
XC_API BOOL WINAPI XSView_ScrollLeft(HELE hEle);    //水平滚动到左侧
XC_API BOOL WINAPI XSView_ScrollRight(HELE hEle);   //水平滚动到右侧
XC_API BOOL WINAPI XSView_ScrollTop(HELE hEle);     //滚动到顶部
XC_API BOOL WINAPI XSView_ScrollBottom(HELE hEle);  //滚动到底部

XC_API void  WINAPI XShape_RemoveShape(HXCGUI hShape);

XC_API int  WINAPI XShape_GetZOrder(HXCGUI hShape);
XC_API void WINAPI XShape_Redraw(HXCGUI hShape);
XC_API int  WINAPI XShape_GetWidth(HXCGUI hShape);
XC_API int  WINAPI XShape_GetHeight(HXCGUI hShape);
XC_API void WINAPI XShape_GetRect(HXCGUI hShape, __out RECT* pRect);
XC_API void WINAPI XShape_SetRect(HXCGUI hShape, __in  RECT* pRect);
XC_API BOOL WINAPI XShape_SetRectLogic(HXCGUI hShape, RECT* pRect, BOOL bRedraw);
XC_API void WINAPI XShape_GetRectLogic(HXCGUI hShape, __out RECT* pRect);
XC_API void WINAPI XShape_GetWndClientRect(HXCGUI hShape, __out RECT* pRect);
XC_API void WINAPI XShape_GetContentSize(HXCGUI hShape, __out SIZE* pSize);//获取内容大小
XC_API void WINAPI XShape_ShowLayout(HXCGUI hShape, BOOL bShow);
XC_API void WINAPI XShape_AdjustLayout(HXCGUI hShape);
XC_API void WINAPI XShape_Destroy(HXCGUI hShape);
XC_API HXCGUI WINAPI XShapeText_Create(int x, int y, int cx, int cy, const wchar_t* pName, HXCGUI hParent = NULL);
XC_API void  WINAPI XShapeText_SetText(HXCGUI hTextBlock, const wchar_t* pName);
XC_API const wchar_t* WINAPI XShapeText_GetText(HXCGUI hTextBlock);
XC_API int   WINAPI XShapeText_GetTextLength(HXCGUI hTextBlock);
XC_API void  WINAPI XShapeText_SetFont(HXCGUI hTextBlock, HFONTX hFontx);
XC_API HFONTX WINAPI XShapeText_GetFont(HXCGUI hTextBlock);
XC_API void WINAPI XShapeText_SetTextColor(HXCGUI hTextBlock, COLORREF color);
XC_API COLORREF WINAPI XShapeText_GetTextColor(HXCGUI hTextBlock);
XC_API void WINAPI XShapeText_SetTextAlign(HXCGUI hTextBlock, int align);
XC_API void WINAPI XShapeText_SetOffset(HXCGUI hTextBlock, int x, int y);
XC_API HXCGUI WINAPI XShapePic_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void   WINAPI XShapePic_SetImage(HXCGUI hShape, HIMAGE hImage);
XC_API HIMAGE WINAPI XShapePic_GetImage(HXCGUI hShape);
XC_API HXCGUI WINAPI XShapeGif_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void   WINAPI XShapeGif_SetImage(HXCGUI hShape, HIMAGE hImage);
XC_API HIMAGE WINAPI XShapeGif_GetImage(HXCGUI hShape);
XC_API HXCGUI WINAPI XShapeRect_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XShapeRect_SetBorderColor(HXCGUI hShape, COLORREF color);
XC_API void WINAPI XShapeRect_SetFillColor(HXCGUI hShape, COLORREF color);
XC_API void WINAPI XShapeRect_SetRoundAngle(HXCGUI hShape, int nWidth, int nHeight);
XC_API void WINAPI XShapeRect_GetRoundAngle(HXCGUI hShape, __out int* pWidth, __out int* pHeight);
XC_API void WINAPI XShapeRect_EnableBorder(HXCGUI hShape, BOOL bEnable);
XC_API void WINAPI XShapeRect_EnableFill(HXCGUI hShape, BOOL bEnable);
XC_API void WINAPI XShapeRect_EnableRoundAngle(HXCGUI hShape, BOOL bEnable);
XC_API HXCGUI WINAPI XShapeEllipse_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XShapeEllipse_SetBorderColor(HXCGUI hShape, COLORREF color);
XC_API void WINAPI XShapeEllipse_SetFillColor(HXCGUI hShape, COLORREF color);
XC_API void WINAPI XShapeEllipse_EnableBorder(HXCGUI hShape, BOOL bEnable);
XC_API void WINAPI XShapeEllipse_EnableFill(HXCGUI hShape, BOOL bEnable);
XC_API HXCGUI WINAPI XShapeGroupBox_Create(int x, int y, int cx, int cy, const wchar_t* pName, HXCGUI hParent = NULL);
XC_API void WINAPI XShapeGroupBox_SetBorderColor(HXCGUI hShape, COLORREF color);
XC_API void WINAPI XShapeGroupBox_SetTextColor(HXCGUI hShape, COLORREF color);
XC_API void WINAPI XShapeGroupBox_SetFontX(HXCGUI hShape, HFONTX hFontX);
XC_API void WINAPI XShapeGroupBox_SetTextOffset(HXCGUI hShape, int offsetX, int offsetY);
XC_API void WINAPI XShapeGroupBox_SetRoundAngle(HXCGUI hShape, int nWidth, int nHeight);
XC_API void WINAPI XShapeGroupBox_SetText(HXCGUI hShape, const wchar_t* pText);
XC_API void WINAPI XShapeGroupBox_GetTextOffset(HXCGUI hShape, __out int* pOffsetX, __out int* pOffsetY);
XC_API void WINAPI XShapeGroupBox_GetRoundAngle(HXCGUI hShape, __out int* pWidth, __out int* pHeight);
XC_API void WINAPI XShapeGroupBox_EnableRoundAngle(HXCGUI hShape, BOOL bEnable);
XC_API HXCGUI WINAPI XShapeLine_Create(int x1, int y1, int x2, int y2, HXCGUI hParent = NULL);
XC_API void WINAPI XShapeLine_SetPosition(HXCGUI hShape, int x1, int y1, int x2, int y2);
XC_API void WINAPI XShapeLine_SetColor(HXCGUI hShape, COLORREF color);
XC_API HELE WINAPI XSliderBar_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XSliderBar_SetRange(HELE hEle, int range);
XC_API int  WINAPI XSliderBar_GetRange(HELE hEle);
XC_API void WINAPI XSliderBar_SetButtonWidth(HELE hEle, int width);
XC_API void WINAPI XSliderBar_SetButtonHeight(HELE hEle, int height);

XC_API void WINAPI XSliderBar_SetPos(HELE hEle, int pos);
XC_API int  WINAPI XSliderBar_GetPos(HELE hEle);
XC_API HELE WINAPI XSliderBar_GetButton(HELE hEle);
XC_API void WINAPI XSliderBar_EnableHorizon(HELE hEle, BOOL bHorizon);
XC_API void WINAPI XSliderBar_SetImageLoad(HELE hEle, HIMAGE hImage);
XC_API const char* WINAPI XC_itoa(int nValue);
XC_API const wchar_t* WINAPI XC_itow(int nValue);
XC_API const wchar_t* WINAPI XC_i64tow(__int64 nValue);
XC_API const char* WINAPI XC_ftoa(float fValue);
XC_API const wchar_t* WINAPI XC_ftow(float fValue);
XC_API const wchar_t* WINAPI XC_fftow(double fValue);
XC_API const wchar_t* WINAPI XC_atow(const char* pValue);
XC_API const char* WINAPI XC_wtoa(const wchar_t* pValue);
XC_API const wchar_t* WINAPI XC_utf8tow(const char* pUtf8);
XC_API const wchar_t* WINAPI XC_utf8towEx(const char* pUtf8, int length);
XC_API const char* WINAPI XC_utf8toa(const char* pUtf8);
XC_API const char* WINAPI XC_atoutf8(const char* pValue);
XC_API const char* WINAPI XC_wtoutf8(const wchar_t* pValue);
XC_API const char* WINAPI XC_wtoutf8Ex(const wchar_t* pValue, int length);
XC_API HELE WINAPI XTabBar_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int  WINAPI XTabBar_AddLabel(HELE hEle, const wchar_t* pName); //添加一个标签
XC_API int  WINAPI XTabBar_InsertLabel(HELE hEle, int index, const wchar_t* pName);
XC_API BOOL WINAPI XTabBar_MoveLabel(HELE hEle, int iSrc, int iDest);
XC_API BOOL WINAPI XTabBar_DeleteLabel(HELE hEle, int index);  //删除
XC_API void WINAPI XTabBar_DeleteLabelAll(HELE hEle);  //删除所有TAB
XC_API HELE WINAPI XTabBar_GetLabel(HELE hEle, int index);//获取标签按钮Button
XC_API HELE WINAPI XTabBar_GetLabelClose(HELE hEle, int index);
XC_API HELE WINAPI XTabBar_GetButtonLeft(HELE hEle);
XC_API HELE WINAPI XTabBar_GetButtonRight(HELE hEle);
XC_API HELE WINAPI XTabBar_GetButtonDropMenu(HELE hEle);
XC_API int  WINAPI XTabBar_GetSelect(HELE hEle);  //获取选择的标签
XC_API int  WINAPI XTabBar_GetLabelSpacing(HELE hEle); //获取标签间距, 0没有间距
XC_API int  WINAPI XTabBar_GetLabelCount(HELE hEle); //获取标签项数量
XC_API int  WINAPI XTabBar_GetindexByEle(HELE hEle, HELE hLabel);
XC_API void WINAPI XTabBar_SetLabelSpacing(HELE hEle, int spacing);//设置标签间距, 0没有间距
XC_API void WINAPI XTabBar_SetPadding(HELE hEle, int left, int top, int right, int bottom);
XC_API void WINAPI XTabBar_SetSelect(HELE hEle, int index);   //设置选择标签
XC_API void WINAPI XTabBar_SetUp(HELE hEle);    //左滚动
XC_API void WINAPI XTabBar_SetDown(HELE hEle);  //右滚动
XC_API void WINAPI XTabBar_EnableTile(HELE hEle, BOOL bTile);  //平铺标签,每个标签显示相同大小
XC_API void WINAPI XTabBar_EnableDropMenu(HELE hEle, BOOL bEnable);
XC_API void WINAPI XTabBar_EnableClose(HELE hEle, BOOL bEnable);
XC_API void WINAPI XTabBar_SetCloseSize(HELE hEle, SIZE* pSize);
XC_API void WINAPI XTabBar_SetTurnButtonSize(HELE hEle, SIZE* pSize);
XC_API void WINAPI XTabBar_SetLabelWidth(HELE hEle, int index, int nWidth);
XC_API BOOL WINAPI XTabBar_ShowLabel(HELE hEle, int index, BOOL bShow); //显示或隐藏指定项
XC_API HXCGUI WINAPI XTable_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XTable_Reset(HXCGUI hShape, int nRow, int nCol);
XC_API void WINAPI XTable_ComboRow(HXCGUI hShape, int iRow, int iCol, int count);
XC_API void WINAPI XTable_ComboCol(HXCGUI hShape, int iRow, int iCol, int count);
XC_API void WINAPI XTable_SetColWidth(HXCGUI hShape, int iCol, int width);
XC_API void WINAPI XTable_SetRowHeight(HXCGUI hShape, int iRow, int height);
XC_API void WINAPI XTable_SetBorderColor(HXCGUI hShape, COLORREF color);
XC_API void WINAPI XTable_SetTextColor(HXCGUI hShape, COLORREF color);
XC_API void WINAPI XTable_SetFont(HXCGUI hShape, HFONTX hFont);
XC_API void WINAPI XTable_SetItemPadding(HXCGUI hShape, int leftSize, int topSize, int rightSize, int bottomSize);
XC_API void WINAPI XTable_SetItemText(HXCGUI hShape, int iRow, int iCol, const wchar_t* pText);
XC_API void WINAPI XTable_SetItemFont(HXCGUI hShape, int iRow, int iCol, HFONTX hFont);
XC_API void WINAPI XTable_SetItemTextAlign(HXCGUI hShape, int iRow, int iCol, int nAlign);
XC_API void WINAPI XTable_SetItemTextColor(HXCGUI hShape, int iRow, int iCol, COLORREF color, BOOL bColor);
XC_API void WINAPI XTable_SetItemBkColor(HXCGUI hShape, int iRow, int iCol, COLORREF color, BOOL bColor);
XC_API void WINAPI XTable_SetItemLine(HXCGUI hShape, int iRow1, int iCol1, int iRow2, int iCol2, int nFlag, COLORREF color);
XC_API void WINAPI XTable_SetItemFlag(HXCGUI hShape, int iRow, int iCol, int flag);
XC_API BOOL WINAPI XTable_GetItemRect(HXCGUI hShape, int iRow, int iCol, __out RECT* pRect);
XC_API HELE WINAPI XTextLink_Create(int x, int y, int cx, int cy, const wchar_t* pName, HXCGUI hParent = NULL);
XC_API void WINAPI XTextLink_EnableUnderlineLeave(HELE hEle, BOOL bEnable);
XC_API void WINAPI XTextLink_EnableUnderlineStay(HELE hEle, BOOL bEnable);
XC_API void WINAPI XTextLink_SetTextColorStay(HELE hEle, COLORREF color);
XC_API void WINAPI XTextLink_SetUnderlineColorLeave(HELE hEle, COLORREF color);
XC_API void WINAPI XTextLink_SetUnderlineColorStay(HELE hEle, COLORREF color);
XC_API HELE WINAPI XToolBar_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int WINAPI XToolBar_InsertEle(HELE hEle, HELE hNewEle, int index = -1); //添加元素到工具条, -1插入到末尾
XC_API int WINAPI XToolBar_InsertSeparator(HELE hEle, int index = -1, COLORREF color = RGB(128, 128, 128)); //添加分隔符, -1插入到末尾
XC_API void WINAPI XToolBar_EnableButtonMenu(HELE hEle, BOOL bEnable);  //显示隐藏项菜单按钮
XC_API HELE WINAPI XToolBar_GetEle(HELE hEle, int index);  //获取工具条上元素句柄
XC_API HELE WINAPI XToolBar_GetButtonLeft(HELE hEle);   //获取工具条左滚动按钮Button
XC_API HELE WINAPI XToolBar_GetButtonRight(HELE hEle);  //获取工具条右滚动按钮Button
XC_API HELE WINAPI XToolBar_GetButtonMenu(HELE hEle);   //获取弹出菜单按钮
XC_API void WINAPI XToolBar_SetSpace(HELE hEle, int nSize);
XC_API void WINAPI XToolBar_DeleteEle(HELE hEle, int index); //移除工具条上元素并销毁
XC_API void WINAPI XToolBar_DeleteAllEle(HELE hEle);
XC_API HELE WINAPI XTree_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XTree_EnableDragItem(HELE hEle, BOOL bEnable);
XC_API void WINAPI XTree_EnableConnectLine(HELE hEle, BOOL bEnable, BOOL bSolid);
XC_API void WINAPI XTree_EnableExpand(HELE hEle, BOOL bEnable);
XC_API void WINAPI XTree_EnableTemplateReuse(HELE hEle, BOOL bEnable);
XC_API void WINAPI XTree_SetConnectLineColor(HELE hEle, COLORREF color);
XC_API void WINAPI XTree_SetExpandButtonSize(HELE hEle, int nWidth, int nHeight);
XC_API void WINAPI XTree_SetConnectLineLength(HELE hEle, int nLength);
XC_API void WINAPI XTree_SetDragInsertPositionColor(HELE hEle, COLORREF color);
XC_API BOOL WINAPI XTree_SetItemTemplateXML(HELE hEle, const wchar_t* pXmlFile);
XC_API BOOL WINAPI XTree_SetItemTemplateXMLSel(HELE hEle, const wchar_t* pXmlFile);
XC_API BOOL WINAPI XTree_SetItemTemplate(HELE hEle, HTEMP hTemp);
XC_API BOOL WINAPI XTree_SetItemTemplateSel(HELE hEle, HTEMP hTemp);
XC_API BOOL WINAPI XTree_SetItemTemplateXMLFromString(HELE hEle, const char* pStringXML);
XC_API BOOL WINAPI XTree_SetItemTemplateXMLSelFromString(HELE hEle, const char* pStringXML);
XC_API void WINAPI XTree_SetDrawItemBkFlags(HELE hEle, int nFlags);
XC_API BOOL WINAPI XTree_SetItemData(HELE hEle, int nID, vint nUserData);
XC_API vint WINAPI XTree_GetItemData(HELE hEle, int nID);
XC_API BOOL WINAPI XTree_SetSelectItem(HELE hEle, int nID);
XC_API int  WINAPI XTree_GetSelectItem(HELE hEle);
XC_API void WINAPI XTree_VisibleItem(HELE hEle, int nID);
XC_API BOOL WINAPI XTree_IsExpand(HELE hEle, int nID);
XC_API BOOL WINAPI XTree_ExpandItem(HELE hEle, int nID, BOOL bExpand);
XC_API BOOL WINAPI XTree_ExpandAllChildItem(HELE hEle, int nID, BOOL bExpand);
XC_API int  WINAPI XTree_HitTest(HELE hEle, POINT* pPt);
XC_API int  WINAPI XTree_HitTestOffset(HELE hEle, POINT* pPt);
XC_API int  WINAPI XTree_GetFirstChildItem(HELE hEle, int nID);
XC_API int  WINAPI XTree_GetEndChildItem(HELE hEle, int nID);
XC_API int  WINAPI XTree_GetPrevSiblingItem(HELE hEle, int nID);
XC_API int  WINAPI XTree_GetNextSiblingItem(HELE hEle, int nID);
XC_API int  WINAPI XTree_GetParentItem(HELE hEle, int nID);
XC_API void WINAPI XTree_SetIndentation(HELE hEle, int nWidth);
XC_API int  WINAPI XTree_GetIndentation(HELE hEle);
XC_API void WINAPI XTree_SetItemHeight(HELE hEle, int nID, int nHeight, int nSelHeight);
XC_API void WINAPI XTree_GetItemHeight(HELE hEle, int nID, __out int* pHeight, __out int* pSelHeight);
XC_API void WINAPI XTree_SetRowSpace(HELE hEle, int nSpace);
XC_API int  WINAPI XTree_GetRowSpace(HELE hEle);
XC_API BOOL WINAPI XTree_MoveItem(HELE hEle, int nMoveItem, int nDestItem, int nFlag);

XC_API void WINAPI XTree_SetItemHeightDefault(HELE hEle, int nHeight, int nSelHeight);
XC_API void WINAPI XTree_GetItemHeightDefault(HELE hEle, __out int* pHeight, __out int* pSelHeight);
XC_API HXCGUI WINAPI XTree_GetTemplateObject(HELE hEle, int nID, int nTempItemID); //通过模板项ID,获取实例化模板项ID对应的对象.
XC_API int    WINAPI XTree_GetItemIDFromHXCGUI(HELE hEle, HXCGUI hXCGUI);
XC_API HXCGUI WINAPI XTree_CreateAdapter(HELE hEle);
XC_API void WINAPI XTree_BindAdapter(HELE hEle, HXCGUI hAdapter);
XC_API HXCGUI WINAPI XTree_GetAdapter(HELE hEle);
XC_API void WINAPI XTree_RefreshData(HELE hEle);
XC_API void WINAPI XTree_RefreshItem(HELE hEle, int nID);
XC_API int WINAPI XTree_InsertItemText(HELE hEle, const wchar_t* pValue, int nParentID = XC_ID_ROOT, int insertID = XC_ID_LAST);
XC_API int WINAPI XTree_InsertItemTextEx(HELE hEle, const wchar_t* pName, const wchar_t* pValue, int nParentID = XC_ID_ROOT, int insertID = XC_ID_LAST);
XC_API int WINAPI XTree_InsertItemImage(HELE hEle, HIMAGE hImage, int nParentID = XC_ID_ROOT, int insertID = XC_ID_LAST);
XC_API int WINAPI XTree_InsertItemImageEx(HELE hEle, const wchar_t* pName, HIMAGE hImage, int nParentID = XC_ID_ROOT, int insertID = XC_ID_LAST);
XC_API int WINAPI XTree_GetCount(HELE hEle);
XC_API int WINAPI XTree_GetCountColumn(HELE hEle);
XC_API BOOL WINAPI XTree_SetItemText(HELE hEle, int nID, int iColumn, const wchar_t* pValue);
XC_API BOOL WINAPI XTree_SetItemTextEx(HELE hEle, int nID, const wchar_t* pName, const wchar_t* pValue);
XC_API BOOL WINAPI XTree_SetItemImage(HELE hEle, int nID, int iColumn, HIMAGE hImage);
XC_API BOOL WINAPI XTree_SetItemImageEx(HELE hEle, int nID, const wchar_t* pName, HIMAGE hImage);
XC_API const wchar_t* WINAPI XTree_GetItemText(HELE hEle, int nID, int iColumn);
XC_API const wchar_t* WINAPI XTree_GetItemTextEx(HELE hEle, int nID, const wchar_t* pName);
XC_API HIMAGE WINAPI XTree_GetItemImage(HELE hEle, int nID, int iColumn);
XC_API HIMAGE WINAPI XTree_GetItemImageEx(HELE hEle, int nID, const wchar_t* pName);
XC_API BOOL WINAPI XTree_DeleteItem(HELE hEle, int nID);
XC_API void WINAPI XTree_DeleteItemAll(HELE hEle);
XC_API void WINAPI XTree_DeleteColumnAll(HELE hEle);
XC_API BOOL WINAPI _XWnd_RegEvent(HWINDOW hWindow, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI _XWnd_RemoveEvent(HWINDOW hWindow, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI XWnd_RegEventC(HWINDOW hWindow, int nEvent, void* pFun);
XC_API BOOL WINAPI XWnd_RegEventC1(HWINDOW hWindow, int nEvent, void* pFun);
XC_API BOOL WINAPI XWnd_RemoveEventC(HWINDOW hWindow, int nEvent, void* pFun);
XC_API HWINDOW WINAPI XWnd_Create(int x, int y, int cx, int cy, const wchar_t* pTitle, HWND hWndParent = NULL, int XCStyle = window_style_default);
XC_API BOOL WINAPI XWnd_AddChild(HWINDOW hWindow, HXCGUI hChild);
XC_API BOOL WINAPI XWnd_InsertChild(HWINDOW hWindow, HXCGUI hChild, int index);
XC_API HWND WINAPI XWnd_GetHWND(HWINDOW hWindow);
XC_API void WINAPI XWnd_EnableDragBorder(HWINDOW hWindow, BOOL bEnable);
XC_API void WINAPI XWnd_EnableDragWindow(HWINDOW hWindow, BOOL bEnable);
XC_API void WINAPI XWnd_EnableDragCaption(HWINDOW hWindow, BOOL bEnable);
XC_API void WINAPI XWnd_EnableDrawBk(HWINDOW hWindow, BOOL bEnable);
XC_API void WINAPI XWnd_EnableAutoFocus(HWINDOW hWindow, BOOL bEnable); //当鼠标左键按下是否获得焦点
XC_API void WINAPI XWnd_EnableMaxWindow(HWINDOW hWindow, BOOL bEnable);
XC_API void WINAPI XWnd_EnableLimitWindowSize(HWINDOW hWindow, BOOL bEnable);
XC_API void WINAPI XWnd_EnableLayout(HWINDOW hWindow, BOOL bEnable);
XC_API void WINAPI XWnd_EnableLayoutOverlayBorder(HWINDOW hWindow, BOOL bEnable);
XC_API void WINAPI XWnd_ShowLayoutFrame(HWINDOW hWindow, BOOL bEnable);
XC_API BOOL WINAPI XWnd_IsEnableLayout(HWINDOW hWindow);
XC_API BOOL WINAPI XWnd_IsMaxWindow(HWINDOW hWindow);
XC_API void WINAPI XWnd_Redraw(HWINDOW hWindow, BOOL bImmediate = FALSE);
XC_API void WINAPI XWnd_RedrawRect(HWINDOW hWindow, RECT* pRect, BOOL bImmediate = FALSE); //重绘窗口指定区域
XC_API void WINAPI XWnd_SetFocusEle(HWINDOW hWindow, HELE hFocusEle);
XC_API HELE WINAPI XWnd_GetFocusEle(HWINDOW hWindow);
XC_API HELE WINAPI XWnd_GetStayEle(HWINDOW hWindow);  //获取当前鼠标所停留元素
XC_API void WINAPI XWnd_DrawWindow(HWINDOW hWindow, HDRAW hDraw);
XC_API void WINAPI XWnd_Center(HWINDOW hWindow);
XC_API void WINAPI XWnd_CenterEx(HWINDOW hWindow, int width, int height);
XC_API void WINAPI XWnd_SetCursor(HWINDOW hWindow, HCURSOR hCursor);
XC_API HCURSOR WINAPI XWnd_GetCursor(HWINDOW hWindow);
XC_API HCURSOR WINAPI XWnd_SetCursorSys(HWINDOW hWindow, HCURSOR hCursor);
XC_API void WINAPI XWnd_SetFont(HWINDOW hWindow, HFONTX hFontx);
XC_API void WINAPI XWnd_SetTextColor(HWINDOW hWindow, COLORREF color);
XC_API COLORREF WINAPI XWnd_GetTextColor(HWINDOW hWindow);
XC_API COLORREF WINAPI XWnd_GetTextColorEx(HWINDOW hWindow);
XC_API void WINAPI XWnd_SetID(HWINDOW hWindow, int nID);
XC_API int  WINAPI XWnd_GetID(HWINDOW hWindow);
XC_API void  WINAPI XWnd_SetName(HWINDOW hWindow, const wchar_t* pName);
XC_API const wchar_t* WINAPI XWnd_GetName(HWINDOW hWindow);
XC_API void WINAPI XWnd_SetCaptureEle(HWINDOW hWindow, HELE hEle);
XC_API HELE WINAPI XWnd_GetCaptureEle(HWINDOW hWindow);
XC_API void WINAPI XWnd_SetBorderSize(HWINDOW hWindow, int left, int top, int right, int bottom);
XC_API void WINAPI XWnd_GetBorderSize(HWINDOW hWindow, __out borderSize_* pBorder);
XC_API void WINAPI XWnd_SetPadding(HWINDOW hWindow, int left, int top, int right, int bottom);
XC_API void WINAPI XWnd_GetPadding(HWINDOW hWindow, __out paddingSize_* pPadding);
XC_API void WINAPI XWnd_SetDragBorderSize(HWINDOW hWindow, int left, int top, int right, int bottom); //设置拖动边框大小
XC_API void WINAPI XWnd_GetDragBorderSize(HWINDOW hWindow, __out borderSize_* pSize);
XC_API void WINAPI XWnd_SetMinimumSize(HWINDOW hWindow, int width, int height);
XC_API HELE WINAPI XWnd_HitChildEle(HWINDOW hWindow, POINT* pPt);
XC_API int  WINAPI XWnd_GetChildCount(HWINDOW hWindow);
XC_API HXCGUI WINAPI XWnd_GetChildByIndex(HWINDOW hWindow, int index);
XC_API HXCGUI WINAPI XWnd_GetChildByID(HWINDOW hWindow, int nID);
XC_API HXCGUI WINAPI XWnd_GetChild(HWINDOW hWindow, int nID);
XC_API void WINAPI XWnd_GetDrawRect(HWINDOW hWindow, RECT* pRcPaint);
XC_API BOOL WINAPI XWnd_ShowWindow(HWINDOW hWindow, int nCmdShow);
XC_API void WINAPI XWnd_AdjustLayout(HWINDOW hWindow);
XC_API void WINAPI XWnd_AdjustLayoutEx(HWINDOW hWindow, int nFlags = adjustLayout_self);
XC_API void WINAPI XWnd_CloseWindow(HWINDOW hWindow);
XC_API void WINAPI XWnd_CreateCaret(HWINDOW hWindow, HELE hEle, int x, int y, int width, int height);//创建插入符

XC_API HELE WINAPI XWnd_GetCaretHELE(HWINDOW hWindow);
XC_API void WINAPI XWnd_SetCaretColor(HWINDOW hWindow, COLORREF color); //设置插入符颜色
XC_API void WINAPI XWnd_ShowCaret(HWINDOW hWindow, BOOL bShow);  //显示插入符
XC_API void WINAPI XWnd_DestroyCaret(HWINDOW hWindow);    //销毁插入符

XC_API void WINAPI XWnd_SetCaretPos(HWINDOW hWindow, int x, int y, int width, int height, BOOL bUpdate = FALSE);
XC_API HELE WINAPI XWnd_GetCaretInfo(HWINDOW hWindow, int* pX, int* pY, int* pWidth, int* pHeight);

XC_API BOOL WINAPI XWnd_GetClientRect(HWINDOW hWindow, __out RECT* pRect); //获取客户区坐标
XC_API void WINAPI XWnd_GetBodyRect(HWINDOW hWindow, __out RECT* pRect);  //获取窗口body坐标
XC_API void WINAPI XWnd_GetLayoutRect(HWINDOW hWindow, __out RECT* pRect);
XC_API void WINAPI XWnd_GetRect(HWINDOW hWindow, __out RECT* pRect);
XC_API void WINAPI XWnd_SetRect(HWINDOW hWindow, RECT* pRect);
XC_API void WINAPI XWnd_SetTop(HWINDOW hWindow);
XC_API void WINAPI XWnd_MaxWindow(HWINDOW hWindow, BOOL bMaximize);
XC_API UINT WINAPI XWnd_SetTimer(HWINDOW hWindow, UINT nIDEvent, UINT uElapse); //设置定时器
XC_API BOOL WINAPI XWnd_KillTimer(HWINDOW hWindow, UINT nIDEvent);
XC_API BOOL WINAPI XWnd_SetXCTimer(HWINDOW hWindow, UINT nIDEvent, UINT uElapse); //设置定时器
XC_API BOOL WINAPI XWnd_KillXCTimer(HWINDOW hWindow, UINT nIDEvent);
XC_API HBKM WINAPI  XWnd_GetBkManager(HWINDOW hWindow);
XC_API HBKM WINAPI  XWnd_GetBkManagerEx(HWINDOW hWindow);
XC_API void WINAPI  XWnd_SetBkMagager(HWINDOW hWindow, HBKM hBkInfoM);
XC_API void WINAPI XWnd_SetTransparentType(HWINDOW hWindow, window_transparent_ nType);  //设置透明窗口
XC_API void WINAPI XWnd_SetTransparentAlpha(HWINDOW hWindow, BYTE alpha); //设置窗口透明度
XC_API void WINAPI XWnd_SetTransparentColor(HWINDOW hWindow, COLORREF color); //设置窗口透明色
XC_API void WINAPI XWnd_SetShadowInfo(HWINDOW hWindow, int nSize, int nDepth, int nAngeleSize, BOOL bRightAngle, COLORREF color);
XC_API window_transparent_ WINAPI XWnd_GetTransparentType(HWINDOW hWindow);
XC_API void WINAPI XWnd_GetShadowInfo(HWINDOW hWindow, __out int* pnSize, __out int* pnDepth, __out int* pnAngeleSize, __out BOOL* pbRightAngle, __out COLORREF* pColor);
XC_API BOOL WINAPI _XWnd_RegEvent(HWINDOW hWindow, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI _XWnd_RemoveEvent(HWINDOW hWindow, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI _XEle_RegEvent(HELE hEle, UINT nEvent, xc_event* pEvent);
XC_API BOOL WINAPI _XEle_RemoveEvent(HELE hEle, UINT nEvent, xc_event* pEvent);

//布局
XC_API void WINAPI XWidget_LayoutItem_EnableWrap(HXCGUI hXCGUI, BOOL bWrap);
XC_API void WINAPI XWidget_LayoutItem_EnableSwap(HXCGUI hXCGUI, BOOL bEnable);
XC_API void WINAPI XWidget_LayoutItem_EnableFloat(HXCGUI hXCGUI, BOOL bFloat);

XC_API void WINAPI XWidget_LayoutItem_SetWidth(HXCGUI hXCGUI, layout_size_ nType, int nWidth);
XC_API void WINAPI XWidget_LayoutItem_SetHeight(HXCGUI hXCGUI, layout_size_ nType, int nHeight);
XC_API void WINAPI XWidget_LayoutItem_GetWidth(HXCGUI hXCGUI, __out layout_size_* pType, __out int* pWidth);
XC_API void WINAPI XWidget_LayoutItem_GetHeight(HXCGUI hXCGUI, __out layout_size_* pType, __out int* pHeight);
XC_API void WINAPI XWidget_LayoutItem_SetAlign(HXCGUI hXCGUI, layout_align_axis_ nAlign);
XC_API void WINAPI XWidget_LayoutItem_SetMargin(HXCGUI hXCGUI, int left, int top, int right, int bottom);
XC_API void WINAPI XWidget_LayoutItem_GetMargin(HXCGUI hXCGUI, __out marginSize_* pMargin);
XC_API void WINAPI XWidget_LayoutItem_SetMinSize(HXCGUI hXCGUI, int width, int height);
XC_API void WINAPI XWidget_LayoutItem_SetPosition(HXCGUI hXCGUI, int left, int top, int right, int bottom);

XC_API HWINDOW WINAPI XWnd_Attach(HWND hWnd, int XCStyle);
XC_API HWINDOW WINAPI XModalWnd_Attach(HWND  hWnd, int XCStyle);
XC_API HWINDOW WINAPI XFrameWnd_Attach(HWND  hWnd, int XCStyle);
XC_API void WINAPI XWnd_EnableDragFiles(HWINDOW hWindow, BOOL bEnable);
XC_API HELE WINAPI XMenuBar_GetButton(HELE hEle, int nIndex);
XC_API void WINAPI XDraw_DrawArc(HDRAW hDraw, int x, int y, int nWidth, int nHeight, float startAngle, float sweepAngle);


XC_API void WINAPI XObj_SetTypeEx(HXCGUI hXCGUI, XC_OBJECT_TYPE_EX nType);
XC_API void WINAPI XWnd_Show(HWINDOW hWindow, BOOL bShow);
XC_API void WINAPI XProgBar_EnableShowText(HELE hEle, BOOL bEnable);

XC_API void WINAPI XWidget_SetID(HXCGUI hXCGUI, int nID);
XC_API int  WINAPI XWidget_GetID(HXCGUI hXCGUI);

XC_API void WINAPI XWidget_SetUID(HXCGUI hXCGUI, int nUID);
XC_API int  WINAPI XWidget_GetUID(HXCGUI hXCGUI);

XC_API void WINAPI XWidget_SetName(HXCGUI hXCGUI, const wchar_t* pName);
XC_API const wchar_t* WINAPI XWidget_GetName(HXCGUI hXCGUI);



XC_API HDRAW WINAPI XDraw_Create(HWINDOW hWindow); //创建
XC_API HDRAW WINAPI XDraw_CreateGDI(HWINDOW hWindow, HDC hdc);

XC_API void  WINAPI XDraw_Destroy(HDRAW hDraw); //销毁
XC_API void  WINAPI XDraw_SetOffset(HDRAW hDraw, int x, int y); //设置坐标偏移量
XC_API void  WINAPI XDraw_GetOffset(HDRAW hDraw, __out int* pX, __out int* pY); //获取坐标偏移量
XC_API HDC   WINAPI XDraw_GetHDC(HDRAW hDraw);

XC_API void WINAPI XDraw_SetBrushColor(HDRAW hDraw, COLORREF color);
XC_API void WINAPI XDraw_SetTextAlign(HDRAW hDraw, int nFlag);
XC_API void WINAPI XDraw_SetTextVertical(HDRAW hDraw, BOOL bVertical);
XC_API void WINAPI XDraw_SetFont(HDRAW hDraw, HFONTX  hFontx);
XC_API void WINAPI XDraw_SetLineWidth(HDRAW hDraw, int width);
XC_API void WINAPI XDraw_SetLineWidthF(HDRAW hDraw, float width);

XC_API void WINAPI XDraw_SetClipRect(HDRAW hDraw, RECT* pRect);
XC_API void WINAPI XDraw_ClearClip(HDRAW hDraw);

XC_API void WINAPI XDraw_EnableSmoothingMode(HDRAW hDraw, BOOL  bEnable);   //启用平滑模式
XC_API void WINAPI XDraw_EnableWndTransparent(HDRAW hDraw, BOOL  bTransparent);

//GDI:
XC_API void WINAPI XDraw_GDI_RestoreGDIOBJ(HDRAW hDraw);  //还原状态,释放用户绑定的GDI对象
XC_API int  WINAPI XDraw_GDI_SetBkMode(HDRAW hDraw, BOOL bTransparent);
XC_API int  WINAPI XDraw_GDI_SelectClipRgn(HDRAW hDraw, HRGN hRgn);

XC_API HBRUSH WINAPI XDraw_GDI_CreateSolidBrush(HDRAW hDraw, COLORREF crColor);
XC_API HPEN WINAPI XDraw_GDI_CreatePen(HDRAW hDraw, int fnPenStyle, int width, COLORREF crColor);
XC_API HRGN WINAPI XDraw_GDI_CreateRectRgn(HDRAW hDraw, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
XC_API HRGN WINAPI XDraw_GDI_CreateRoundRectRgn(HDRAW hDraw, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidthEllipse, int nHeightEllipse);
XC_API HRGN WINAPI XDraw_GDI_CreatePolygonRgn(HDRAW hDraw, POINT* pPt, int cPoints, int fnPolyFillMode);

XC_API BOOL WINAPI XDraw_GDI_Rectangle(HDRAW hDraw, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
XC_API BOOL WINAPI XDraw_GDI_FillRgn(HDRAW hDraw, HRGN hrgn, HBRUSH hbr);
XC_API BOOL WINAPI XDraw_GDI_Ellipse(HDRAW hDraw, RECT* pRect);
XC_API BOOL WINAPI XDraw_GDI_FrameRgn(HDRAW hDraw, HRGN hrgn, HBRUSH hbr, int width, int nHeight);

XC_API BOOL WINAPI XDraw_GDI_MoveToEx(HDRAW hDraw, int X, int Y, POINT* pPoint = NULL);
XC_API BOOL WINAPI XDraw_GDI_LineTo(HDRAW hDraw, int nXEnd, int nYEnd);
XC_API BOOL WINAPI XDraw_GDI_Polyline(HDRAW hDraw, in_buffer_ POINT* pArrayPt, int arrayPtSize);

XC_API BOOL WINAPI XDraw_GDI_DrawIconEx(HDRAW hDraw, int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);

XC_API BOOL WINAPI XDraw_GDI_BitBlt(HDRAW hDrawDest, int nXDest, int nYDest, int width, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);
XC_API BOOL WINAPI XDraw_GDI_BitBlt2(HDRAW hDrawDest, int nXDest, int nYDest, int width, int nHeight, HDRAW hDrawSrc, int nXSrc, int nYSrc, DWORD dwRop);
XC_API BOOL WINAPI XDraw_GDI_AlphaBlend(HDRAW hDraw, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int alpha);
XC_API COLORREF WINAPI XDraw_GDI_SetPixel(HDRAW hDraw, int X, int Y, COLORREF crColor);

//-----------------
XC_API void WINAPI XDraw_FillRect(HDRAW hDraw, RECT* pRect);
XC_API void WINAPI XDraw_FillRectF(HDRAW hDraw, RECTF* pRect);
XC_API void WINAPI XDraw_FillRectColor(HDRAW hDraw, RECT* pRect, COLORREF color);
XC_API void WINAPI XDraw_FillRectColorF(HDRAW hDraw, RECTF* pRect, COLORREF color);

XC_API void WINAPI XDraw_DrawRect(HDRAW hDraw, RECT* pRect);
XC_API void WINAPI XDraw_DrawRectF(HDRAW hDraw, RECTF* pRect);

XC_API void WINAPI XDraw_FillEllipse(HDRAW hDraw, RECT* pRect);
XC_API void WINAPI XDraw_FillEllipseF(HDRAW hDraw, RECTF* pRect);

XC_API void WINAPI XDraw_DrawEllipse(HDRAW hDraw, RECT* pRect);
XC_API void WINAPI XDraw_DrawEllipseF(HDRAW hDraw, RECTF* pRect);

XC_API void WINAPI XDraw_FillRoundRect(HDRAW hDraw, RECT* pRect, int width, int nHeight);
XC_API void WINAPI XDraw_FillRoundRectF(HDRAW hDraw, RECTF* pRect, float width, float height);

XC_API void WINAPI XDraw_DrawRoundRect(HDRAW hDraw, RECT* pRect, int width, int nHeight);
XC_API void WINAPI XDraw_DrawRoundRectF(HDRAW hDraw, RECTF* pRect, float width, float height);

XC_API void WINAPI XDraw_FillRoundRectEx(HDRAW hDraw, RECT* pRect, int leftTop, int rightTop, int rightBottom, int leftBottom);
XC_API void WINAPI XDraw_FillRoundRectExF(HDRAW hDraw, RECTF* pRect, float leftTop, float rightTop, float rightBottom, float leftBottom);

XC_API void WINAPI XDraw_DrawRoundRectEx(HDRAW hDraw, RECT* pRect, int leftTop, int rightTop, int rightBottom, int leftBottom);
XC_API void WINAPI XDraw_DrawRoundRectExF(HDRAW hDraw, RECTF* pRect, float leftTop, float rightTop, float rightBottom, float leftBottom);

XC_API void WINAPI XDraw_GradientFill2(HDRAW hDraw, RECT* pRect, COLORREF color1, COLORREF color2, int mode);
XC_API void WINAPI XDraw_GradientFill2F(HDRAW hDraw, RECTF* pRect, COLORREF color1, COLORREF color2, int mode);

XC_API void WINAPI XDraw_GradientFill4(HDRAW hDraw, RECT* pRect, COLORREF color1, COLORREF color2, COLORREF color3, COLORREF color4, int mode);
XC_API void WINAPI XDraw_GradientFill4F(HDRAW hDraw, RECTF* pRect, COLORREF color1, COLORREF color2, COLORREF color3, COLORREF color4, int mode);

XC_API void WINAPI XDraw_FocusRect(HDRAW hDraw, RECT* pRect);
XC_API void WINAPI XDraw_FocusRectF(HDRAW hDraw, RECTF* pRect);

XC_API void WINAPI XDraw_DrawLine(HDRAW hDraw, int x1, int y1, int x2, int y2);
XC_API void WINAPI XDraw_DrawLineF(HDRAW hDraw, float x1, float y1, float x2, float y2);

XC_API void WINAPI XDraw_Dottedline(HDRAW hDraw, int x1, int y1, int x2, int y2);
XC_API void WINAPI XDraw_DottedlineF(HDRAW hDraw, float x1, float y1, float x2, float y2);

XC_API void WINAPI XDraw_DrawCurve(HDRAW hDraw, in_buffer_ POINT* points, int count, float tension);
XC_API void WINAPI XDraw_DrawCurveF(HDRAW hDraw, in_buffer_ POINTF* points, int count, float tension);

//绘制圆弧
XC_API void WINAPI XDraw_DrawArc(HDRAW hDraw, int x, int y, int width, int nHeight, float startAngle, float sweepAngle);
XC_API void WINAPI XDraw_DrawArcF(HDRAW hDraw, float x, float y, float width, float height, float startAngle, float sweepAngle);

//绘制多边形
XC_API void WINAPI XDraw_DrawPolygon(HDRAW hDraw, in_buffer_ POINT* points, int nCount);
XC_API void WINAPI XDraw_DrawPolygonF(HDRAW hDraw, in_buffer_ POINTF* points, int nCount);

XC_API void WINAPI XDraw_FillPolygon(HDRAW hDraw, in_buffer_ POINT* points, int nCount);
XC_API void WINAPI XDraw_FillPolygonF(HDRAW hDraw, in_buffer_ POINTF* points, int nCount);

//图片
XC_API void WINAPI XDraw_Image(HDRAW hDraw, HIMAGE hImageFrame, int x, int y);
XC_API void WINAPI XDraw_ImageF(HDRAW hDraw, HIMAGE hImageFrame, float x, float y);

XC_API void WINAPI XDraw_ImageEx(HDRAW hDraw, HIMAGE hImageFrame, int x, int y, int width, int height);
XC_API void WINAPI XDraw_ImageExF(HDRAW hDraw, HIMAGE hImageFrame, float x, float y, float width, float height);

XC_API void WINAPI XDraw_ImageAdaptive(HDRAW hDraw, HIMAGE hImageFrame, RECT* pRect, BOOL bOnlyBorder = FALSE);
XC_API void WINAPI XDraw_ImageAdaptiveF(HDRAW hDraw, HIMAGE hImageFrame, RECTF* pRect, BOOL bOnlyBorder = FALSE);

//从左下角往右上角铺,现在平铺区域
//flag:平板类型,0左上角,1左左下角
XC_API void WINAPI XDraw_ImageTile(HDRAW hDraw, HIMAGE hImageFrame, RECT* pRect, int flag = 0);
XC_API void WINAPI XDraw_ImageTileF(HDRAW hDraw, HIMAGE hImageFrame, RECTF* pRect, int flag = 0);

XC_API void WINAPI XDraw_ImageSuper(HDRAW hDraw, HIMAGE hImageFrame, RECT* pRect, BOOL bClip = FALSE);
XC_API void WINAPI XDraw_ImageSuperF(HDRAW hDraw, HIMAGE hImageFrame, RECTF* pRect, BOOL bClip = FALSE);

XC_API void WINAPI XDraw_ImageSuperEx(HDRAW hDraw, HIMAGE hImageFrame, RECT* pRcDest, RECT* pRcSrc);
XC_API void WINAPI XDraw_ImageSuperExF(HDRAW hDraw, HIMAGE hImageFrame, RECTF* pRcDest, RECTF* pRcSrc);

XC_API void WINAPI XDraw_ImageSuperMask(HDRAW hDraw, HIMAGE hImageFrame, HIMAGE hImageFrameMask, RECT* pRect, RECT* pRectMask, BOOL bClip = FALSE);

//文本
XC_API void WINAPI XDraw_DrawText(HDRAW hDraw, const wchar_t* pString, int nCount, RECT* pRect);
XC_API void WINAPI XDraw_DrawTextF(HDRAW hDraw, const wchar_t* pString, int nCount, RECTF* pRect);

XC_API void WINAPI XDraw_DrawTextUnderline(HDRAW hDraw, const wchar_t* pString, int nCount, RECT* pRect, COLORREF colorLine);
XC_API void WINAPI XDraw_DrawTextUnderlineF(HDRAW hDraw, const wchar_t* pString, int nCount, RECTF* pRect, COLORREF colorLine);

XC_API void WINAPI XDraw_TextOut(HDRAW hDraw, int xStart, int yStart, const wchar_t* pString, int cbString);
XC_API void WINAPI XDraw_TextOutF(HDRAW hDraw, float xStart, float yStart, const wchar_t* pString, int cbString);

XC_API void WINAPI XDraw_TextOutEx(HDRAW hDraw, int xStart, int yStart, const wchar_t* pString);
XC_API void WINAPI XDraw_TextOutExF(HDRAW hDraw, float xStart, float yStart, const wchar_t* pString);

XC_API void WINAPI XDraw_TextOutA(HDRAW hDraw, int xStart, int yStart, const char* pString);
XC_API void WINAPI XDraw_TextOutAF(HDRAW hDraw, float xStart, float yStart, const char* pString);

//v3.1.1
XC_API void WINAPI XWnd_SetIcon(HWINDOW hWindow, HIMAGE hImage);
XC_API void WINAPI XWnd_SetTitle(HWINDOW hWindow, const wchar_t* pTitle);
XC_API void WINAPI XWnd_SetTitleColor(HWINDOW hWindow, COLORREF color);
XC_API HELE WINAPI XWnd_GetButton(HWINDOW hWindow, int nFlag);
XC_API HIMAGE WINAPI XWnd_GetIcon(HWINDOW hWindow);
XC_API const wchar_t* WINAPI XWnd_GetTitle(HWINDOW hWindow);
XC_API COLORREF WINAPI XWnd_GetTitleColor(HWINDOW hWindow);

XC_API vint WINAPI XC_GetD2dFactory();
XC_API vint WINAPI XC_GetWicFactory();
XC_API vint WINAPI XC_GetDWriteFactory();
XC_API void WINAPI XC_SetD2dTextRenderingMode(XC_DWRITE_RENDERING_MODE mode);

XC_API vint WINAPI XDraw_GetD2dRenderTarget(HDRAW hDraw);
XC_API void WINAPI XDraw_SetD2dTextRenderingMode(HDRAW hDraw, XC_DWRITE_RENDERING_MODE mode);

XC_API HELE WINAPI XLayoutFrame_CreateEx(HXCGUI hParent);
XC_API void WINAPI XLayoutFrame_EnableLayout(HELE hEle, BOOL bEnable);
XC_API BOOL WINAPI XLayoutFrame_IsEnableLayout(HELE hEle);
XC_API int  WINAPI XLayoutFrame_GetWidthIn(HELE hEle);
XC_API int  WINAPI XLayoutFrame_GetHeightIn(HELE hEle);

XC_API void   WINAPI XDraw_SetTextRenderingHint(HDRAW hDraw, int  nType);
XC_API HFONTX WINAPI XFont_CreateFromMem(void* data, UINT length, int fontSize = 12, int style = fontStyle_regular);
XC_API void WINAPI XComboBox_PopupDropList(HELE hEle);
XC_API BOOL WINAPI XComboBox_SetItemTemplate(HELE hEle, HTEMP hTemp);

XC_API BOOL WINAPI XC_IsEnableD2D();
XC_API HFONTX WINAPI XFont_CreateFromRes(int id, const wchar_t* pType, int fontSize, int style, HMODULE hModule = NULL);

XC_API int WINAPI XC_MessageBox(const wchar_t* pTitle, const wchar_t* pText, int nFlags = messageBox_flag_ok | messageBox_flag_icon_info, HWND hWndParent = 0, int XCStyle = window_style_modal);
XC_API HWINDOW WINAPI XMsg_Create(const wchar_t* pTitle, const wchar_t* pText, int nFlags = messageBox_flag_ok | messageBox_flag_icon_info, HWND hWndParent = 0, int XCStyle = window_style_modal);

//3.2.0--------------------------
//修改:
XC_API BOOL WINAPI XC_LoadStyleFromStringW(const wchar_t* pString, const wchar_t* pFileName);
//增加:
XC_API BOOL WINAPI XC_LoadStyleFromString(const char* pString, const wchar_t* pFileName);
XC_API BOOL WINAPI XC_LoadStyleFromStringUtf8(const char* pString, const wchar_t* pFileName);

XC_API HIMAGE WINAPI XImage_LoadSvg(HSVG hSvg);
XC_API HIMAGE WINAPI XImage_LoadSvgFile(const wchar_t* pFileName);
XC_API HSVG   WINAPI XImage_GetSvg(HIMAGE hImage);

//SVG 合并到 3.3.0

XC_API void WINAPI XDraw_DrawSvgSrc(HDRAW hDraw, HSVG hSvg);
XC_API void WINAPI XDraw_DrawSvg(HDRAW hDraw, HSVG hSvg, int x, int y);
XC_API void WINAPI XDraw_DrawSvgEx(HDRAW hDraw, HSVG hSvg, int x, int y, int nWidth, int nHeight);
XC_API void WINAPI XDraw_DrawSvgSize(HDRAW hDraw, HSVG hSvg, int nWidth, int nHeight);

XC_API void WINAPI XC_ShowSvgFrame(BOOL bShow);

XC_API void WINAPI XWnd_AddBkBorder(HWINDOW hWindow, int nState, COLORREF color, int width);
XC_API void WINAPI XWnd_AddBkFill(HWINDOW hWindow, int nState, COLORREF color);
XC_API void WINAPI XWnd_AddBkImage(HWINDOW hWindow, int nState, HIMAGE hImage);
XC_API int  WINAPI XWnd_GetBkInfoCount(HWINDOW hWindow);
XC_API void WINAPI XWnd_ClearBkInfo(HWINDOW hWindow);


//3.3.0----------------------------------------

//移除:
//XEle_Move
//XEle_MoveLogic
//XShape_Move
//XSvg_GetOffset
//XSvg_SetOffset
//XWnd_Move
//XSvg_LoadString
//XImage_LoadSvgString

//增加:
XC_API void WINAPI XWnd_SetPosition(HWINDOW hWindow, int x, int y);
XC_API int  WINAPI XEle_SetPosition(HELE hEle, int x, int y, BOOL bRedraw = FALSE, int nFlags = adjustLayout_all, UINT nAdjustNo = 0);
XC_API int  WINAPI XEle_SetPositionLogic(HELE hEle, int x, int y, BOOL bRedraw = FALSE, int nFlags = adjustLayout_all, UINT nAdjustNo = 0);
XC_API void WINAPI XEle_GetPosition(HELE hEle, int* pOutX, int* pOutY);
XC_API int  WINAPI XEle_SetSize(HELE hEle, int nWidth, int nHeight, BOOL bRedraw = FALSE, int nFlags = adjustLayout_all, UINT nAdjustNo = 0);
XC_API void WINAPI XEle_GetSize(HELE hEle, __out int* pOutWidth, __out int* pOutHeight);

XC_API void WINAPI XShape_SetPosition(HXCGUI hShape, int x, int y);
XC_API void WINAPI XShape_GetPosition(HXCGUI hShape, int* pOutX, int* pOutY);
XC_API void WINAPI XShape_SetSize(HXCGUI hShape, int  nWidth, int  nHeight);
XC_API void WINAPI XShape_GetSize(HXCGUI hShape, int* pOutWidth, int* pOutHeight);
XC_API void WINAPI XShape_SetAlpha(HXCGUI hShape, BYTE alpha);
XC_API BYTE WINAPI XShape_GetAlpha(HXCGUI hShape);

XC_API HIMAGE WINAPI XImage_LoadSvgString(const char* pString); //修改
XC_API HIMAGE WINAPI XImage_LoadSvgStringW(const wchar_t* pString);
XC_API HIMAGE WINAPI XImage_LoadSvgStringUtf8(const char* pString);

XC_API float WINAPI XEase_Ex(float pos, int flag);

//-----SVG---------------------------------------------------------------
XC_API HSVG WINAPI XSvg_LoadFile(const wchar_t* pFileName);
XC_API HSVG WINAPI XSvg_LoadString(const char* pString);
XC_API HSVG WINAPI XSvg_LoadStringW(const wchar_t* pString);
XC_API HSVG WINAPI XSvg_LoadStringUtf8(const char* pString);
XC_API HSVG WINAPI XSvg_LoadZip(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword = NULL);
XC_API HSVG WINAPI XSvg_LoadRes(int id, const wchar_t* pType, HMODULE hModule = NULL);

XC_API void WINAPI XSvg_SetSize(HSVG hSvg, int nWidth, int nHeight);
XC_API void WINAPI XSvg_GetSize(HSVG hSvg, __out int* pWidth, __out int* pHeight);

XC_API int  WINAPI XSvg_GetWidth(HSVG hSvg);
XC_API int  WINAPI XSvg_GetHeight(HSVG hSvg);

XC_API void WINAPI XSvg_SetPosition(HSVG hSvg, int x, int y);
XC_API void WINAPI XSvg_GetPosition(HSVG hSvg, __out int* pX, __out int* pY);

void WINAPI XSvg_SetPositionF(HSVG hSvg, float x, float y);
void WINAPI XSvg_GetPositionF(HSVG hSvg, __out float* pX, __out float* pY);

XC_API void WINAPI XSvg_GetViewBox(HSVG hSvg, __out RECT* pViewBox);
XC_API void WINAPI XSvg_SetAlpha(HSVG hSvg, BYTE alpha);
XC_API BYTE WINAPI XSvg_GetAlpha(HSVG hSvg);

XC_API void WINAPI XSvg_SetUserFillColor(HSVG hSvg, COLORREF color, BOOL bEnable);
XC_API void WINAPI XSvg_SetUserStrokeColor(HSVG hSvg, COLORREF color, float strokeWidth, BOOL bEnable);

XC_API BOOL WINAPI XSvg_GetUserFillColor(HSVG hSvg, __out COLORREF* pColor);
XC_API BOOL WINAPI XSvg_GetUserStrokeColor(HSVG hSvg, __out COLORREF* pColor, __out float* pStrokeWidth);

XC_API void WINAPI XSvg_SetRotateAngle(HSVG hSvg, float angle);
XC_API float WINAPI XSvg_GetRotateAngle(HSVG hSvg);
XC_API void WINAPI XSvg_SetRotate(HSVG hSvg, float angle, float x, float y, BOOL bOffset = FALSE);
XC_API void WINAPI XSvg_GetRotate(HSVG hSvg, __out float* pAngle, __out float* pX, __out float* pY, __out BOOL* pbOffset);

XC_API void WINAPI XSvg_Show(HSVG hSvg, BOOL bShow);
XC_API void WINAPI XSvg_EnableAutoDestroy(HSVG hSvg, BOOL bEnable);
XC_API void WINAPI XSvg_AddRef(HSVG hSvg);
XC_API void WINAPI XSvg_Release(HSVG hSvg);
XC_API int  WINAPI XSvg_GetRefCount(HSVG hSvg);
XC_API void WINAPI XSvg_Destroy(HSVG hSvg);

//动画特效------------------------------------------------
XC_API void   WINAPI XAnima_Run(HXCGUI hAnimation, HXCGUI hRedrawObjectUI);
XC_API BOOL   WINAPI XAnima_Release(HXCGUI hAnimation, BOOL bEnd = TRUE);
XC_API int    WINAPI XAnima_ReleaseEx(HXCGUI hObjectUI, BOOL bEnd); //移除指定UI对象关联的动画

//动画序列
XC_API HXCGUI WINAPI XAnima_Create(HXCGUI hObjectUI, int nLoopCount = 0);

XC_API HXCGUI WINAPI XAnima_Move(HXCGUI  hSequence, UINT duration, float x, float y, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE);
XC_API HXCGUI WINAPI XAnima_MoveEx(HXCGUI  hSequence, UINT duration, float from_x, float from_y, float to_x, float to_y, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE);
HXCGUI Anima_MoveExT(HXCGUI  hSequence, UINT duration, float from_x, float from_y, float to_x, float to_y, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE, BOOL bFrom = FALSE);

XC_API HXCGUI WINAPI XAnima_Rotate(HXCGUI  hSequence, UINT duration, float angle, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE);
XC_API HXCGUI WINAPI XAnima_RotateEx(HXCGUI  hSequence, UINT duration, float from, float to, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE);
HXCGUI Anima_RotateExT(HXCGUI  hSequence, UINT duration, float from, float to, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE, BOOL bFrom = FALSE);

XC_API HXCGUI WINAPI XAnima_Scale(HXCGUI hSequence, UINT duration, float scaleX, float scaleY, int nLoopCount = 0, int ease_flag = 0, BOOL bGoBack = TRUE);
XC_API HXCGUI WINAPI XAnima_ScaleSize(HXCGUI hSequence, UINT duration, float width, float height, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE);

XC_API HXCGUI WINAPI XAnima_Alpha(HXCGUI hSequence, UINT duration, BYTE alpha, int nLoopCount = 0, int ease_flag = 0, BOOL bGoBack = FALSE);
XC_API HXCGUI WINAPI XAnima_AlphaEx(HXCGUI hSequence, UINT duration, BYTE  from_alpha, BYTE to_alpha, int nLoopCount = 0, int ease_flag = 0, BOOL bGoBack = FALSE);
HXCGUI Anima_AlphaExT(HXCGUI hSequence, UINT duration, BYTE  from_alpha, BYTE to_alpha, int nLoopCount = 0, int ease_flag = 0, BOOL bGoBack = FALSE, BOOL bFrom = FALSE);

XC_API HXCGUI WINAPI XAnima_Color(HXCGUI hSequence, UINT duration, COLORREF color, int nLoopCount = 0, int ease_flag = 0, BOOL bGoBack = FALSE);
XC_API HXCGUI WINAPI XAnima_ColorEx(HXCGUI hSequence, UINT duration, COLORREF from, COLORREF to, int nLoopCount = 0, int ease_flag = 0, BOOL bGoBack = FALSE);
HXCGUI Anima_ColorExT(HXCGUI hSequence, UINT duration, COLORREF from, COLORREF to, int nLoopCount = 0, int ease_flag = 0, BOOL bGoBack = FALSE, BOOL bFrom = FALSE);

XC_API HXCGUI WINAPI XAnima_LayoutWidth(HXCGUI hSequence, UINT duration, layout_size_  nType, float width, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE);
XC_API HXCGUI WINAPI XAnima_LayoutHeight(HXCGUI hSequence, UINT duration, layout_size_  nType, float height, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE);

XC_API HXCGUI WINAPI XAnima_LayoutSize(HXCGUI hSequence, UINT duration, layout_size_  nWidthType, float width, layout_size_  nHeightType, float height, int nLoopCount = 0, int ease_flag = 0, BOOL bGoBack = TRUE);


XC_API HXCGUI WINAPI XAnima_Delay(HXCGUI hSequence, float duration);
XC_API HXCGUI WINAPI XAnima_Show(HXCGUI hSequence, float duration, BOOL bShow);

//动画组
XC_API HXCGUI WINAPI XAnimaGroup_Create(int nLoopCount = 0);
XC_API void   WINAPI XAnimaGroup_AddItem(HXCGUI hGroup, HXCGUI hSequence);

//设置项属性
XC_API void   WINAPI XAnimaItem_EnableCompleteRelease(HXCGUI hAnimationItem, BOOL bEnable);
XC_API void   WINAPI XAnimaRotate_SetCenter(HXCGUI hAnimationRotate, float x, float y, BOOL bOffset = FALSE);
XC_API void   WINAPI XAnimaScale_SetPosition(HXCGUI hAnimationScale, position_flag_  position);

XC_API HXCGUI WINAPI XAnima_GetObjectUI(HXCGUI hAnimation); //获取动画关联的UI对象
XC_API void   WINAPI XAnima_EnableAutoDestroy(HXCGUI hAnimation, BOOL bEnable);//启用自动销毁


//v3.3.1---------------------------------------------------------

//优化参数顺序
XC_API HWINDOW WINAPI XWnd_CreateEx(DWORD dwExStyle, DWORD dwStyle, const wchar_t* lpClassName, int x, int y, int cx, int cy, const wchar_t* pTitle, HWND hWndParent = NULL, int XCStyle = window_style_default);
XC_API HWINDOW WINAPI XModalWnd_CreateEx(DWORD dwExStyle, DWORD dwStyle, const wchar_t* lpClassName, int x, int y, int cx, int cy, const wchar_t* pTitle, HWND hWndParent, int XCStyle = window_style_modal);  //创建窗口
XC_API HWINDOW WINAPI XFrameWnd_CreateEx(DWORD dwExStyle, DWORD dwStyle, const wchar_t* lpClassName, int x, int y, int cx, int cy, wchar_t* pTitle, HWND hWndParent, int XCStyle);  //创建窗口

//新增
XC_API HXCGUI WINAPI XAnima_DestroyObjectUI(HXCGUI hSequence, float duration);
XC_API void   WINAPI XAnima_SetCallback(HXCGUI hAnimation, funAnimation callback);
XC_API void   WINAPI XAnima_SetUserData(HXCGUI hAnimation, vint nUserData);
XC_API vint   WINAPI XAnima_GetUserData(HXCGUI hAnimation);
XC_API BOOL   WINAPI XAnima_Stop(HXCGUI hAnimation);
XC_API BOOL   WINAPI XAnima_Start(HXCGUI hAnimation);
XC_API BOOL   WINAPI XAnima_Pause(HXCGUI hAnimation);
XC_API void   WINAPI XAnimaItem_SetCallback(HXCGUI hAnimationItem, funAnimationItem callback);
XC_API void   WINAPI XAnimaItem_SetUserData(HXCGUI hAnimationItem, vint nUserData);
XC_API vint   WINAPI XAnimaItem_GetUserData(HXCGUI hAnimationItem);
XC_API void   WINAPI XAnimaItem_EnableAutoDestroy(HXCGUI hAnimationItem, BOOL bEnable);

XC_API HELE WINAPI XNotifyMsg_WindowPopup(HWINDOW hWindow, position_flag_ position, const wchar_t* pTitle, const wchar_t* pText, HIMAGE hIcon, notifyMsg_skin_ skin = notifyMsg_skin_no);
XC_API HELE WINAPI XNotifyMsg_WindowPopupEx(HWINDOW hWindow, position_flag_ position, const wchar_t* pTitle, const wchar_t* pText, HIMAGE hIcon = NULL, notifyMsg_skin_ skin = notifyMsg_skin_no, BOOL bBtnClose = TRUE, BOOL bAutoClose = TRUE, int nWidth = -1, int nHeight = -1);
//在桌面弹出通知消息,返回窗口句柄
XC_API HWINDOW WINAPI XNotifyMsg_Popup(position_flag_ position, const wchar_t* pTitle, const wchar_t* pText, HIMAGE hIcon, notifyMsg_skin_ skin = notifyMsg_skin_no);
XC_API HWINDOW WINAPI XNotifyMsg_PopupEx(position_flag_ position, const wchar_t* pTitle, const wchar_t* pText, HIMAGE hIcon = NULL, notifyMsg_skin_ skin = notifyMsg_skin_no, BOOL bBtnClose = TRUE, BOOL bAutoClose = TRUE, int nWidth = -1, int nHeight = -1);
//设置指定窗口通知消息属性, 如果未指定窗口,那么设置桌面通知消息属性
XC_API void WINAPI XNotifyMsg_SetDuration(HWINDOW hWindow, UINT duration);
XC_API void WINAPI XNotifyMsg_SetCaptionHeight(HWINDOW hWindow, int nHeight);
XC_API void WINAPI XNotifyMsg_SetWidth(HWINDOW hWindow, int nWidth);
XC_API void WINAPI XNotifyMsg_SetSpace(HWINDOW hWindow, int nSpace);
XC_API void WINAPI XNotifyMsg_SetBorderSize(HWINDOW hWindow, int left, int top, int right, int bottom);
XC_API void WINAPI XNotifyMsg_SetParentMargin(HWINDOW hWindow, int left, int top, int right, int bottom);

XC_API HWINDOW WINAPI XMsg_CreateEx(DWORD dwExStyle, DWORD dwStyle, const wchar_t* lpClassName, const wchar_t* pTitle, const wchar_t* pText, int nFlags = messageBox_flag_ok | messageBox_flag_icon_info, HWND hWndParent = 0, int XCStyle = window_style_modal);

//v3.3.2--------------------------------------------------------
XC_API HXCGUI WINAPI XAnima_DelayEx(HXCGUI hSequence, float duration, int nLoopCount = 1, int ease_flag = 0, BOOL bGoBack = FALSE);
XC_API void   WINAPI XAnimaMove_SetFlag(HXCGUI hAnimationMove, int flags);
XC_API int  WINAPI XEle_SetBkInfo(HELE hEle, const wchar_t* pText);
XC_API int  WINAPI XWnd_SetBkInfo(HWINDOW hWindow, const wchar_t* pText);
XC_API int  WINAPI XBkM_SetInfo(HBKM hBkInfoM, const wchar_t* pText);


//增加参数 hAttachWnd
XC_API HXCGUI WINAPI XC_LoadLayout(const wchar_t* pFileName, HXCGUI hParent = NULL, HWND hAttachWnd = NULL);
XC_API HXCGUI WINAPI XC_LoadLayoutZip(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HXCGUI hParent = NULL, HWND hAttachWnd = NULL);
XC_API HXCGUI WINAPI XC_LoadLayoutZipMem(void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HXCGUI hParent = NULL, HWND hAttachWnd = NULL);
XC_API HXCGUI WINAPI XC_LoadLayoutFromString(const char* pStringXML, HXCGUI hParent = NULL, HWND hAttachWnd = NULL);
XC_API HXCGUI WINAPI XC_LoadLayoutFromStringUtf8(const char* pStringXML, HXCGUI hParent = NULL, HWND hAttachWnd = NULL);

XC_API void WINAPI XWnd_SetCaptionMargin(HWINDOW hWindow, int left, int top, int right, int bottom);
XC_API BOOL WINAPI XWnd_IsDragBorder(HWINDOW hWindow);
XC_API BOOL WINAPI XWnd_IsDragWindow(HWINDOW hWindow);
XC_API BOOL WINAPI XWnd_IsDragCaption(HWINDOW hWindow);

//v3.3.3-------------------------------------------------------
XC_API void WINAPI XList_SetSplitLineColor(HELE hEle, COLORREF color);
XC_API void WINAPI XListBox_SetSplitLineColor(HELE hEle, COLORREF color);
XC_API void WINAPI XTree_SetSplitLineColor(HELE hEle, COLORREF color);

XC_API void  WINAPI XDraw_D2D_Clear(HDRAW hDraw, COLORREF color);

XC_API BOOL WINAPI XBkM_GetStateTextColor(HBKM hBkInfoM, int nState, __out COLORREF* color);
XC_API vint WINAPI XBkM_GetObject(HBKM hBkInfoM, int id);

XC_API BOOL WINAPI XMenu_SetItemWidth(HMENUX hMenu, int nID, int nWidth);

XC_API void WINAPI XBkObj_SetMargin(vint hObj, int left, int top, int right, int bottom);
XC_API void WINAPI XBkObj_SetAlign(vint hObj, int  nFlags);//bkInfo_align_flags_
XC_API void WINAPI XBkObj_SetImage(vint hObj, HIMAGE hImage);
XC_API void WINAPI XBkObj_SetRotate(vint hObj, float angle);

XC_API void WINAPI XBkObj_SetFillColor(vint hObj, COLORREF color);
XC_API void WINAPI XBkObj_SetBorderWidth(vint hObj, int  width);
XC_API void WINAPI XBkObj_SetBorderColor(vint hObj, COLORREF color);
XC_API void WINAPI XBkObj_SetRectRoundAngle(vint hObj, int leftTop, int leftBottom, int rightTop, int rightBottom);

XC_API void WINAPI XBkObj_EnableFill(vint hObj, BOOL bEnable);
XC_API void WINAPI XBkObj_EnableBorder(vint hObj, BOOL bEnable);

XC_API void WINAPI XBkObj_SetText(vint hObj, const wchar_t* pText);
XC_API void WINAPI XBkObj_SetFont(vint hObj, HFONTX hFont);
XC_API void WINAPI XBkObj_SetTextAlign(vint hObj, int nAlign);

XC_API void WINAPI XBkObj_GetMargin(vint hObj, __out marginSize_* pMargin);
XC_API int  WINAPI XBkObj_GetAlign(vint hObj);
XC_API HIMAGE WINAPI XBkObj_GetImage(vint hObj);
XC_API int  WINAPI XBkObj_GetRotate(vint hObj);

XC_API COLORREF WINAPI XBkObj_GetFillColor(vint hObj);
XC_API COLORREF WINAPI XBkObj_GetBorderColor(vint hObj);
XC_API int WINAPI XBkObj_GetBorderWidth(vint hObj);
XC_API void WINAPI XBkObj_GetRectRoundAngle(vint hObj, __out RECT* pRect);

XC_API BOOL WINAPI XBkObj_IsFill(vint hObj);
XC_API BOOL WINAPI XBkObj_IsBorder(vint hObj);

XC_API const wchar_t* WINAPI XBkObj_GetText(vint hObj);
XC_API HFONTX WINAPI XBkObj_GetFont(vint hObj);
XC_API int  WINAPI XBkObj_GetTextAlign(vint hObj);

//v3.3.4---------------------------------
XC_API void WINAPI XEdit_SetRowSpace(HELE hEle, int nSpace);
XC_API void WINAPI XEdit_SetBackFont(HELE hEle, HFONTX hFont);

XC_API BOOL WINAPI XEdit_ReleaseStyle(HELE hEle, int iStyle);
XC_API int  WINAPI XEdit_ModifyStyle(HELE hEle, HFONTX hFont, COLORREF color, BOOL bColor);

XC_API void WINAPI XEdit_SetSpaceSize(HELE hEle, int size);
XC_API void WINAPI XEdit_SetCharSpaceSize(HELE hEle, int size, int sizeZh);

XC_API int  WINAPI XEdit_GetSelectTextLength(HELE hEle);
XC_API void WINAPI XEdit_SetSelectTextStyle(HELE hEle, int iStyle);

XC_API const char* WINAPI XEditor_GetExpandState(HELE hEle); //获取折叠状态
XC_API BOOL WINAPI XEditor_SetExpandState(HELE hEle, const char* pString); //设置折叠状态
XC_API int  WINAPI XEditor_GetIndentation(HELE hEle, int iRow);
XC_API BOOL WINAPI XEidtor_IsEmptyRow(HELE hEle, int iRow);

XC_API void WINAPI XEdit_AddTextUser(HELE hEle, const wchar_t* pString);
XC_API void WINAPI XEdit_PosToRowCol(HELE hEle, int iPos, __out position_* pInfo);
XC_API int  WINAPI XEdit_RowColToPos(HELE hEle, int iRow, int iCol);
XC_API void WINAPI XEdit_SetCurPosEx(HELE hEle, int iRow, int iCol); //新增
XC_API void WINAPI XEdit_GetCurPosEx(HELE hEle, __out int* iRow, __out int* iCol); //新增
XC_API BOOL WINAPI XEdit_SetCurPos(HELE hEle, int pos);  //修改
XC_API void WINAPI XEdit_MoveEnd(HELE hEle); //新增

//增加参数
XC_API void  WINAPI XPane_ShowPane(HELE hEle, BOOL bActivate);
XC_API void  WINAPI XPane_HidePane(HELE hEle, BOOL bGroupDelay = FALSE);
//新增:
XC_API BOOL WINAPI XPane_IsGroupActivate(HELE hEle);

//增加参数:
XC_API void WINAPI XC_GetTextShowRect(const wchar_t* pString, int length, HFONTX hFontX, int nTextAlign, int width, __out SIZE* pOutSize);

//新增:
XC_API void WINAPI XList_SetItemHeight(HELE hEle, int iItem, int nHeight, int nSelHeight);
XC_API void WINAPI XList_GetItemHeight(HELE hEle, int iItem, __out int* pHeight, __out int* pSelHeight);

//弹出菜单修复 对背景管理器支持, 对窗口隐藏支持

//句柄上限增加到20万

//增加列表视图 取数据接口
XC_API const wchar_t* WINAPI XAdListView_Group_GetText(HXCGUI hAdapter, int iGroup, int iColumn); //new
XC_API const wchar_t* XAdListView_Group_GetTextEx(HXCGUI hAdapter, int iGroup, const wchar_t* pName); //new
XC_API HIMAGE WINAPI XAdListView_Group_GetImage(HXCGUI hAdapter, int iGroup, int iColumn); //new
XC_API HIMAGE WINAPI XAdListView_Group_GetImageEx(HXCGUI hAdapter, int iGroup, const wchar_t* pName);//new

XC_API const wchar_t* WINAPI XAdListView_Item_GetText(HXCGUI hAdapter, int iGroup, int iItem, int iColumn);
XC_API HIMAGE WINAPI XAdListView_Item_GetImage(HXCGUI hAdapter, int iGroup, int iItem, const wchar_t* pName);

XC_API const wchar_t* WINAPI XListView_Group_GetText(HELE hEle, int iGroup, int iColumn); //new
XC_API const wchar_t* XListView_Group_GetTextEx(HELE hEle, int iGroup, const wchar_t* pName); //new
XC_API HIMAGE WINAPI XListView_Group_GetImage(HELE hEle, int iGroup, int iColumn); //new
XC_API HIMAGE WINAPI XListView_Group_GetImageEx(HELE hEle, int iGroup, const wchar_t* pName);//new

XC_API const wchar_t* WINAPI XListView_Item_GetText(HELE hEle, int iGroup, int iItem, int iColumn);
XC_API HIMAGE WINAPI XListView_Item_GetImage(HELE hEle, int iGroup, int iItem, int iColumn);

XC_API void WINAPI XDraw_ImageMask(HDRAW hDraw, HIMAGE hImageFrame, HIMAGE hImageFrameMask, RECT* pRect, int x2, int y2);
XC_API void WINAPI XDraw_ImageMaskRect(HDRAW hDraw, HIMAGE hImageFrame, RECT* pRect, RECT* pRcMask, RECT* pRcRoundAngle);
XC_API void WINAPI XDraw_ImageMaskEllipse(HDRAW hDraw, HIMAGE hImageFrame, RECT* pRect, RECT* pRcMask);

XC_API void WINAPI XDateTime_Popup(HELE hEle);
XC_API void WINAPI XMonthCal_SetTextColor(HELE hEle, int nFlag, COLORREF color);
XC_API HTEMP WINAPI XTemp_Clone(HTEMP hTemp);
XC_API frameWnd_cell_type_ WINAPI XFrameWnd_GetDragFloatWndTopFlag(HWINDOW hWindow);

//3.3.5
XC_API void WINAPI XImage_SetScaleSize(HIMAGE hImage, int width, int height);
XC_API void WINAPI XEditor_SetAutoMatchMode(HELE hEle, int mode);
//--------------------------
XC_API void WINAPI XListView_SetDragRectColor(HELE hEle, COLORREF color, int width);
XC_API void WINAPI XListBox_SetDragRectColor(HELE hEle, COLORREF color, int width);
XC_API void WINAPI XList_SetDragRectColor(HELE hEle, COLORREF color, int width);

XC_API HSVG WINAPI XSvg_LoadZipMem(void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword);

XC_API HFONTX WINAPI XFont_CreateFromZip(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword, int fontSize, int style);
XC_API HFONTX WINAPI XFont_CreateFromZipMem(void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword, int fontSize, int style);

//增加参数 col_extend_count  列表项模板支持列延伸
//XC_API HXCGUI WINAPI XList_CreateAdapter(HELE hEle, int col_extend_count=0);

//--------------------------------------
XC_API void WINAPI XListBox_SetItemHeight(HELE hEle, int iItem, int nHeight, int nSelHeight);
XC_API void WINAPI XListBox_GetItemHeight(HELE hEle, int iItem, __out int* pHeight, __out int* pSelHeight);

XC_API int  WINAPI XEdit_GetRowCountEx(HELE hEle);

XC_API void WINAPI XUI_EnableCssEx(HXCGUI hXCGUI, BOOL bEnable);
XC_API void WINAPI XBtn_EnableHotkeyPrefix(HELE hEle, BOOL bEnable);

XC_API void  WINAPI XFont_SetUnderlineEdit(HFONTX hFontX, BOOL  bUnderline, BOOL bStrikeout);
XC_API void  WINAPI XFont_GetUnderlineEdit(HFONTX hFontX, __out BOOL* bUnderline, __out BOOL* bStrikeout);

//3.3.6
XC_API const wchar_t* WINAPI XEdit_GetText_Temp(HELE hEle);
XC_API const wchar_t* WINAPI XEdit_GetTextRow_Temp(HELE hEle, int iRow);
XC_API const wchar_t* WINAPI XEdit_GetSelectText_Temp(HELE hEle);

XC_API HTEMP WINAPI XList_GetItemTemplate(HELE hEle);
XC_API HTEMP WINAPI XList_GetItemTemplateHeader(HELE hEle);
XC_API void  WINAPI XList_RefreshDataHeader(HELE hEle);

XC_API BOOL  WINAPI XTemp_List_InsertNode(HTEMP hTemp, int index, void* pNode);
XC_API BOOL  WINAPI XTemp_List_DeleteNode(HTEMP hTemp, int index);
XC_API int   WINAPI XTemp_List_GetCount(HTEMP hTemp);
XC_API BOOL  WINAPI XTemp_List_MoveColumn(HTEMP hTemp, int iColDest, int iColSrc);

//3.3.7
//增加事件: XE_TOOLTIP_POPUP
//结构体 menu_drawItem_ 增加成员 nShortcutKeyWidth 

XC_API HXCGUI WINAPI XC_LoadLayoutEx(const wchar_t* pFileName, const wchar_t* pPrefixName = NULL, HXCGUI hParent = NULL, HWND hParentWnd = NULL, HWND hAttachWnd = NULL);
XC_API HXCGUI WINAPI XC_LoadLayoutZipEx(const wchar_t* pZipFileName, const wchar_t* pFileName, const wchar_t* pPassword = NULL, const wchar_t* pPrefixName = NULL, HXCGUI hParent = NULL, HWND hParentWnd = NULL, HWND hAttachWnd = NULL);
XC_API HXCGUI WINAPI XC_LoadLayoutZipMemEx(void* data, int length, const wchar_t* pFileName, const wchar_t* pPassword = NULL, const wchar_t* pPrefixName = NULL, HXCGUI hParent = NULL, HWND hParentWnd = NULL, HWND hAttachWnd = NULL);
XC_API HXCGUI WINAPI XC_LoadLayoutFromStringEx(const char* pStringXML, const wchar_t* pPrefixName = NULL, HXCGUI hParent = NULL, HWND hParentWnd = NULL, HWND hAttachWnd = NULL);
XC_API HXCGUI WINAPI XC_LoadLayoutFromStringUtf8Ex(const char* pStringXML, const wchar_t* pPrefixName = NULL, HXCGUI hParent = NULL, HWND hParentWnd = NULL, HWND hAttachWnd = NULL);
XC_API void   WINAPI XEdit_InsertChatBegin(HELE hEle, HIMAGE hImageAvatar, HIMAGE hImageBubble, int nFlag);
XC_API HFONTX WINAPI XDraw_GetFont(HDRAW hDraw);


//v3.3.8
//用户数据改为vint类型 XList_SetItemData() XList_GetItemData()

XC_API void WINAPI XC_EnableAutoDPI(BOOL bEnabel);
XC_API void WINAPI XWnd_SetDPI(HWINDOW hWindow, int nDPI);

XC_API HXCGUI WINAPI XC_LoadLayoutZipResEx(int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, const wchar_t* pPrefixName = NULL, HXCGUI hParent = NULL, HWND hParentWnd = NULL, HWND hAttachWnd = NULL, HMODULE hModule = NULL);
XC_API BOOL   WINAPI XC_LoadResourceZipRes(int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);
XC_API BOOL   WINAPI XC_LoadStyleZipRes(int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);

XC_API HTEMP WINAPI XTemp_LoadFromMem(listItemTemp_type_ nType, void* data, int length);
XC_API BOOL  WINAPI XTemp_LoadFromMemEx(listItemTemp_type_ nType, void* data, int length, __out HTEMP* pOutTemp1, __out HTEMP* pOutTemp2);

XC_API HTEMP WINAPI XTemp_LoadZipRes(listItemTemp_type_ nType, int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);
XC_API BOOL  WINAPI XTemp_LoadZipResEx(listItemTemp_type_ nType, int id, const wchar_t* pFileName, const wchar_t* pPassword, __out HTEMP* pOutTemp1, __out HTEMP* pOutTemp2, HMODULE hModule = NULL);

XC_API HIMAGE WINAPI XImage_LoadZipRes(int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);
XC_API HIMAGE WINAPI XImgSrc_LoadZipRes(int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);
XC_API HSVG   WINAPI XSvg_LoadZipRes(int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);

XC_API BOOL WINAPI XListBox_SetItemTemplateXMLFromMem(HELE hEle, void* data, int length);
XC_API BOOL WINAPI XListBox_SetItemTemplateXMLFromZipRes(HELE hEle, int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);
XC_API HTEMP WINAPI XListBox_GetItemTemplate(HELE hEle);

XC_API BOOL WINAPI XList_SetItemTemplateXMLFromMem(HELE hEle, void* data, int length);
XC_API BOOL WINAPI XList_SetItemTemplateXMLFromZipRes(HELE hEle, int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);

XC_API BOOL WINAPI XComboBox_SetItemTemplateXMLFromMem(HELE hEle, void* data, int length);
XC_API BOOL WINAPI XComboBox_SetItemTemplateXMLFromZipRes(HELE hEle, int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);
XC_API HTEMP WINAPI XComboBox_GetItemTemplate(HELE hEle);

XC_API BOOL WINAPI XTree_SetItemTemplateXMLFromMem(HELE hEle, void* data, int length);
XC_API BOOL WINAPI XTree_SetItemTemplateXMLFromZipRes(HELE hEle, int id, const wchar_t* pFileName, const wchar_t* pPassword = NULL, HMODULE hModule = NULL);
XC_API HTEMP WINAPI XTree_GetItemTemplate(HELE hEle);

XC_API BOOL WINAPI XListView_SetItemTemplateXMLFromMem(HELE hEle, void* data, int length);
XC_API BOOL WINAPI XListView_SetItemTemplateXMLFromZipRes(HELE hEle, int id, const wchar_t* pFileName, const wchar_t* pPassword, HMODULE hModule);
XC_API HTEMP WINAPI XListView_GetItemTemplate(HELE hEle);
XC_API HTEMP WINAPI XListView_GetItemTemplateGroup(HELE hEle);

//增加DPI支持
//UI设计器增加撤销重做
//XMsg_Create 图标继承父

//XListView_EnablemTemplateReuse, XListBox_EnablemTemplateReuse, XTree_EnablemTemplateReuse, XWnd_EnablemLimitWindowSize,
//_Enablem* 改为 *_Enable*

XC_API void WINAPI XC_SetWindowIcon(HIMAGE hImage);

XC_API void WINAPI XProgBar_SetColorLoad(HELE hEle, COLORREF color);

XC_API int  WINAPI XEdit_GetChatFlags(HELE hEle, int iRow);
XC_API void WINAPI XEdit_InsertTextEx(HELE hEle, int iRow, int iCol, const wchar_t* pString, int iStyle);
XC_API void WINAPI XEdit_InsertObject(HELE hEle, int iRow, int iCol, HXCGUI hObj);

XC_API void WINAPI XEle_GetWndClientRectDPI(HELE hEle, __out RECT* pRect);
XC_API void WINAPI XEle_PointClientToWndClientDPI(HELE hEle, __in_out POINT* pPt);
XC_API void WINAPI XEle_RectClientToWndClientDPI(HELE hEle, __in_out RECT* pRect);

XC_API BOOL WINAPI XWnd_SetWindowPos(HWINDOW hWindow, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);

XC_API int  WINAPI XWnd_GetDPI(HWINDOW hWindow);

XC_API void WINAPI XWnd_RectToDPI(HWINDOW hWindow, RECT* pRect);
XC_API void WINAPI XWnd_PointToDPI(HWINDOW hWindow, POINT* pPt);
XC_API BOOL WINAPI XWnd_GetCursorPos(HWINDOW hWindow, __out POINT* pPt);

XC_API BOOL WINAPI XWnd_ClientToScreen(HWINDOW hWindow, __in_out POINT* pPt);
XC_API BOOL WINAPI XWnd_ScreenToClient(HWINDOW hWindow, __in_out POINT* pPt);
