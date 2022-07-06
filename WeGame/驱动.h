#pragma once
#include <winsvc.h>

class 驱动
{
public:
	驱动();
	~驱动();

public:
	DWORD dwLastError;   //最后的错误
	HANDLE hDriver;      //驱动句柄
	SC_HANDLE hSCManager;  //SCM句柄
	SC_HANDLE hService;    //服务句柄

public:

	BOOL 加载驱动(LPCWSTR 驱动文件路径, LPCWSTR 服务名, LPCWSTR 服务显示名);

	//example: \\\\.\\xxoo
	BOOL Open驱动(LPCWSTR pLinkName);

	BOOL 卸载驱动(LPCWSTR 服务名);

	// 驱动通讯
	BOOL IoControl(DWORD dwIoCode, PVOID InBuff, DWORD InBuffLen, PVOID OutBuff, DWORD OutBuffLen, DWORD* RealRetBytes);
};

extern 驱动 drive;