#include "pch.h"
#include "Driver.h"


Driver::Driver() //构造函数
{
	//初始化变量
	hSCManager = NULL;
	hService = NULL;
	hDriver = INVALID_HANDLE_VALUE;

	dwLastError = 0;
}

Driver::~Driver() //析构函数
{
	//释放资源
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
	CloseHandle(hDriver);
}


BOOL Driver::LoadDriver(LPCWSTR 驱动文件路径, LPCWSTR 服务名, LPCWSTR 服务显示名) {

	BOOL result = false;

	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager != NULL) {

		hService = CreateService(
			hSCManager,
			服务名,//驱动程序在注册表中的名字
			服务显示名,// 注册表驱动程序的 DisplayName 值
			SERVICE_ALL_ACCESS,// 加载驱动程序的访问权限
			SERVICE_KERNEL_DRIVER,// 表示加载的服务是驱动程序
			SERVICE_DEMAND_START,// 注册表驱动程序的 Start 值
			SERVICE_ERROR_IGNORE,// 注册表驱动程序的 ErrorControl 值
			驱动文件路径,// 注册表驱动程序的 ImagePath 值
			NULL, NULL, NULL, NULL, NULL);

		if (hService == NULL && GetLastError() == ERROR_SERVICE_EXISTS)  // 服务已经存在
		{
			hService = OpenService(hSCManager, 服务名, SERVICE_ALL_ACCESS);
		}
		if (hService != NULL)
		{
			BOOL 启动服务 = StartService(hService, NULL, NULL);
			dwLastError = GetLastError();
			if (启动服务 || dwLastError == ERROR_SERVICE_ALREADY_RUNNING)
			{
				result = true;
			}
			else
			{
				CloseServiceHandle(hService);
			}
		}
		else
		{
			CloseServiceHandle(hSCManager);
		}
		
	}
	return result;
}

//example: \\\\.\\xxoo
BOOL Driver::OpenDriver(LPCWSTR pLinkName)
{
	if (hDriver != INVALID_HANDLE_VALUE)
	{
		return true;
	}
	hDriver = CreateFile(pLinkName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hDriver != INVALID_HANDLE_VALUE)
	{
		return true;
	}
	return false;
}

BOOL Driver::UnLoadDriver(LPCWSTR 服务名) {

	BOOL result = false;

	if (hSCManager != NULL) {
		if (hService != NULL) {
			SERVICE_STATUS ss;
			if (ControlService(hService, SERVICE_CONTROL_STOP, &ss))  // 停止运行
			{
				DeleteService(hService);
				CloseServiceHandle(hService);
				result = true;
			}
		}
		CloseServiceHandle(hSCManager);
	}

	return result;
}

BOOL Driver::IoControl(DWORD dwIoCode, PVOID InBuff, DWORD InBuffLen, PVOID OutBuff, DWORD OutBuffLen, DWORD* RealRetBytes)
{
	return DeviceIoControl(hService, dwIoCode, InBuff, InBuffLen, OutBuff, OutBuffLen, RealRetBytes, NULL);
}