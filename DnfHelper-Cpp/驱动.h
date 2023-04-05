#pragma once
#include "公用.h"

class Driver
{
public:
	Driver();
	~Driver();

public:
	DWORD dwLastError;   //最后的错误
	HANDLE hDriver;      //驱动句柄
	SC_HANDLE hSCManager;  //SCM句柄
	SC_HANDLE hService;    //服务句柄

public:

	BOOL LoadDriver(LPCWSTR 驱动文件路径, LPCWSTR 服务名, LPCWSTR 服务显示名);

	//example: \\\\.\\xxoo
	BOOL OpenDriver(LPCWSTR pLinkName);

	BOOL UnLoadDriver(LPCWSTR 服务名);

	// 驱动通讯
	BOOL IoControl(DWORD dwIoCode, PVOID InBuff, DWORD InBuffLen, PVOID OutBuff, DWORD OutBuffLen, DWORD* RealRetBytes);
};

extern Driver drive;