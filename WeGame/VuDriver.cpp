#include "pch.h"
#include "VuDriver.h"

static HANDLE g_hDrv = INVALID_HANDLE_VALUE;

VOID Vu驱动::设置驱动句柄(HANDLE hDrv)
{
	g_hDrv = hDrv;
	return;
}

ULONG64 Vu驱动::效验有效性(const char* key)
{
	IOCTL_BUFFER		pInfo = { 0 };
	pInfo.Buf = (ULONG64)key;
	ULONG64 返回数据 = 0;
	DWORD				returnLegth = 0;

	DeviceIoControl(g_hDrv, IOCTL_IO_FILE_CHECK, &pInfo, sizeof(pInfo), &返回数据, sizeof(返回数据), &returnLegth, NULL);

	return 返回数据;

	/*
	返回数据 > 0 = (“载入驱动成功!”)
	0 = (“参数错误 - 请检查DLL路径是否真实存在以及您的激活码是否正确”)
	-1= (“激活码不存在”)
	-2=(“账户余额不足”)
	-3=(“扣费失败”)
	-4=(“网络错误”)
	-5=(“驱动安装失败”)
	-6=(“有效性效验失败”)
	其他(“未知错误”)
	*/

}


ULONG64 Vu驱动::VU_内存_置读写模式(DWORD 模式, DWORD 类型)
{
	BOOL				bResult = FALSE;
	ULONG64             returnCode = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER		pInfo = { 0 };
	pInfo.Addr = 模式;
	pInfo.Size = 类型;
	bResult = DeviceIoControl(g_hDrv, IOCTL_IO_MEMORY_MOD, &pInfo, sizeof(pInfo), &returnCode, sizeof(returnCode), &returnLegth, NULL);
	return returnCode;
}

//枚举指定进程模块 
DWORD64	Vu驱动::VU_内存_取模块基址(DWORD pid, const char* moduleName)
{
	BOOL				bResult = FALSE;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER_GetBase		pInfo = { 0 };
	ALLOCATE_FREE_MEMORY_RESULT result = { 0 };

	pInfo.ModelAddr = 0;
	pInfo.PID = (ULONG)pid;
	sprintf_s(pInfo.ModelName, "%s", moduleName);

	bResult = DeviceIoControl(g_hDrv, IOCTL_IO_MEMORY_GETMODULEBASE, &pInfo, sizeof(pInfo), &result, sizeof(result), &returnLegth, NULL);

	return result.address;

}


//读内存函数，自己封装
BOOL Vu驱动::VU_内存_读字节集(DWORD pid, PVOID addr, PVOID pBuf, INT32 size)
{
	BOOL				bResult = FALSE;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER		pInfo = { 0 };

	pInfo.PID = pid;
	pInfo.Addr = (ULONG64)addr;
	pInfo.Size = size;

	bResult = DeviceIoControl(g_hDrv, IOCTL_IO_MEMORY_READ, &pInfo, sizeof(pInfo), pBuf, size, &returnLegth, NULL);

	return bResult;
}

//写内存函数，自己封装
BOOL Vu驱动::VU_内存_写字节集(DWORD pid, PVOID addr, PVOID pBuf, INT32 size)
{

	BOOL				bResult = FALSE;
	DWORD				returnLegth = 0;


	DWORD len = sizeof(IOCTL_BUFFER_Write) + size;
	IOCTL_BUFFER_Write* pInfo = (IOCTL_BUFFER_Write*)malloc(len);
	if (!pInfo)
		return FALSE;

	ZeroMemory(pInfo, len);


	pInfo->PID = pid;
	pInfo->Addr = (ULONG64)addr;
	pInfo->Size = size;
	memcpy(pInfo->Buf, pBuf, size);

	bResult = DeviceIoControl(g_hDrv, IOCTL_IO_MEMORY_WRITE, pInfo, len, 0, 0, &returnLegth, NULL);

	free(pInfo);
	return bResult;
}


DWORD64 Vu驱动::VU_内存_申请(DWORD 进程ID, DWORD64 进程地址, DWORD64 申请长度, DWORD64 内存属性, BOOL 是否物理)
{


	DWORD					returnLegth = 0;
	ALLOCATE_FREE_MEMORY	msgInfo = { 0 };
	ALLOCATE_FREE_MEMORY_RESULT result = { 0 };
	msgInfo.pid = 进程ID;
	msgInfo.base = 进程地址;
	msgInfo.size = 申请长度;
	msgInfo.protection = 内存属性;
	msgInfo.allocate = TRUE;
	msgInfo.physical = 是否物理;
	msgInfo.type = MEM_COMMIT;

	DeviceIoControl(g_hDrv, IOCTL_IO_MEMORY_ALLOC, &msgInfo, sizeof(msgInfo), &result, sizeof(result), &returnLegth, NULL);
	return result.address;
}


DWORD64 Vu驱动::VU_内存_释放(DWORD 进程ID, DWORD64 进程地址, DWORD64 内存长度, BOOL 是否物理)
{


	DWORD					returnLegth = 0;
	ALLOCATE_FREE_MEMORY	msgInfo = { 0 };
	ALLOCATE_FREE_MEMORY_RESULT result = { 0 };
	msgInfo.pid = 进程ID;
	msgInfo.base = 进程地址;
	msgInfo.size = 内存长度;
	msgInfo.protection = 0;
	msgInfo.allocate = FALSE;
	msgInfo.physical = 是否物理;
	msgInfo.type = MEM_RELEASE;

	DeviceIoControl(g_hDrv, IOCTL_IO_MEMORY_ALLOC, &msgInfo, sizeof(msgInfo), &result, sizeof(result), &returnLegth, NULL);
	return result.address;
}


DWORD64 Vu驱动::VU_内存_修改属性(DWORD 进程ID, DWORD64 地址, DWORD64 长度, DWORD64 内存属性)
{
	DWORD64 pAddr = 0;

	DWORD					returnLegth = 0;
	ALLOCATE_FREE_MEMORY	msgInfo = { 0 };
	msgInfo.pid = 进程ID;
	msgInfo.base = 地址;
	msgInfo.size = 长度;
	msgInfo.protection = 内存属性;
	msgInfo.allocate = TRUE;
	msgInfo.physical = 1;
	msgInfo.type = MEM_RELEASE;

	DeviceIoControl(g_hDrv, IOCTL_IO_MEMORY_PROTECT, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
	return pAddr;
}


DWORD64 Vu驱动::VU_内存_查询属性(DWORD 进程ID, DWORD64 地址)
{
	DWORD64 pAddr = 0;

	DWORD					returnLegth = 0;
	ALLOCATE_FREE_MEMORY	msgInfo = { 0 };
	msgInfo.pid = 进程ID;
	msgInfo.base = 地址;
	msgInfo.size = 4096;
	msgInfo.protection = 64;
	msgInfo.allocate = FALSE;
	msgInfo.physical = 1;
	msgInfo.type = 0;

	DeviceIoControl(g_hDrv, IOCTL_IO_MEMORY_QUERY, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
	return pAddr;
}


DWORD64 Vu驱动::VU_超级注入CALL_置主线程获取模式(DWORD64 模式)
{

	BOOL				bResult = FALSE;
	DWORD64				pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.Addr = 模式;

	DeviceIoControl(g_hDrv, IOCTL_IO_INJECT_SET_THREADMOD, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
	return pAddr;
}

DWORD64 Vu驱动::VU_远程注入CALL(DWORD 进程ID, PBYTE CALL代码, DWORD CALL代码长度, BOOL 硬件物理执行)
{
	DWORD len = sizeof(IOCTL_BUFFER_InjectCode) + CALL代码长度;
	IOCTL_BUFFER_InjectCode* pInfo = (IOCTL_BUFFER_InjectCode*)malloc(len);
	if (!pInfo)
		return FALSE;
	ZeroMemory(pInfo, len);
	pInfo->PID = 进程ID;
	pInfo->isPhyMem = 硬件物理执行;
	pInfo->Size = CALL代码长度;

	memcpy(pInfo->Buf, CALL代码, CALL代码长度);

	DWORD64 pAddr = 0;
	DWORD	returnLegth = 0;

	DeviceIoControl(g_hDrv, IOCTL_IO_INJECT_REMOTE_CALL, pInfo, len, &pAddr, sizeof(pAddr), &returnLegth, NULL);
	free(pInfo);
	return pAddr;

}


DWORD64 Vu驱动::VU_远程执行CALL(DWORD 进程ID, DWORD64 目标地址, DWORD64 参数地址)
{
	DWORD64 pAddr = 0;
	DWORD	returnLegth = 0;
	IOCTL_BUFFER_InjectCode	msgInfo = { 0 };
	msgInfo.PID = 进程ID;
	msgInfo.Size = 参数地址;
	msgInfo.Addr = 目标地址;

	DeviceIoControl(g_hDrv, IOCTL_IO_INJECT_REMOTE_CALLEX, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
	return pAddr;
}

DWORD64 Vu驱动::VU_超级注入CALL(DWORD 进程ID, PBYTE CALL代码, DWORD CALL代码长度, DWORD 线程ID, BOOL 硬件物理执行)
{
	DWORD len = sizeof(IOCTL_BUFFER_InjectCode) + CALL代码长度;
	IOCTL_BUFFER_InjectCode* pInfo = (IOCTL_BUFFER_InjectCode*)malloc(len);
	if (!pInfo)
		return FALSE;
	ZeroMemory(pInfo, len);

	pInfo->PID = 进程ID;
	pInfo->isPhyMem = 硬件物理执行;
	pInfo->Size = CALL代码长度;

	memcpy(pInfo->Buf, CALL代码, CALL代码长度);
	pInfo->Addr = 线程ID;


	DWORD64 pAddr = 0;
	DWORD	returnLegth = 0;


	DeviceIoControl(g_hDrv, IOCTL_IO_INJECT_SUPER_CALL, pInfo, len, &pAddr, sizeof(pAddr), &returnLegth, NULL);
	free(pInfo);
	return pAddr;

}


DWORD64 Vu驱动::VU_超级执行CALL(DWORD 进程ID, DWORD64 目标地址, DWORD64 参数地址, DWORD 线程ID)
{
	DWORD64 pAddr = 0;
	DWORD	returnLegth = 0;
	IOCTL_BUFFER_InjectCode	msgInfo = { 0 };
	msgInfo.PID = 进程ID;
	msgInfo.Addr = 目标地址;
	msgInfo.Size = 参数地址;
	msgInfo.isPhyMem = 线程ID;


	DeviceIoControl(g_hDrv, IOCTL_IO_INJECT_SUPER_CALLEX, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
	return pAddr;
}


BOOL Vu驱动::VU_键鼠_安装()
{
	BOOL				bResult = FALSE;
	DWORD				returnLegth = 0;

	return DeviceIoControl(g_hDrv, IOCTL_IO_INPUT_INIT, 0, 0, 0, 0, &returnLegth, NULL);

}

BOOL Vu驱动::VU_隐藏文件_安装()
{
	DWORD				returnLegth = 0;

	return DeviceIoControl(g_hDrv, IOCTL_IO_FILTER_INIT, 0, 0, 0, 0, &returnLegth, NULL);
}

BOOL Vu驱动::VU_隐藏文件_卸载()
{
	DWORD				returnLegth = 0;

	return DeviceIoControl(g_hDrv, IOCTL_IO_FILTER_UNINIT, 0, 0, 0, 0, &returnLegth, NULL);
}


DWORD64 Vu驱动::VU_隐藏文件_文件(CHAR* 文件路径)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	CHAR strPath[MAX_PATH] = { 0 };
	sprintf_s(strPath, "\\??\\%s", 文件路径);
	msgInfo.Buf = (DWORD64)&strPath;
	DeviceIoControl(g_hDrv, IOCTL_IO_FILTER_FILE, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
	return pAddr;
}

DWORD64 Vu驱动::VU_隐藏文件_目录(CHAR* 目录路径)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };

	CHAR strPath[MAX_PATH] = { 0 };
	sprintf_s(strPath, "\\??\\%s", 目录路径);
	msgInfo.Buf = (DWORD64)&strPath;
	DeviceIoControl(g_hDrv, IOCTL_IO_FILTER_DIR, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
	return pAddr;
}





BOOL Vu驱动::VU_保护_安装()
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.PID = 1;

	return DeviceIoControl(g_hDrv, IOCTL_IO_PROTECT_BEGIN_OR_END, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}

BOOL Vu驱动::VU_保护_卸载()
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.PID = 0;

	return DeviceIoControl(g_hDrv, IOCTL_IO_PROTECT_BEGIN_OR_END, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}

BOOL Vu驱动::VU_保护_进程_开始(DWORD64 进程ID, BOOL 是否保护驱动)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.PID = 进程ID;
	if (是否保护驱动)
		msgInfo.Size = 100;

	return DeviceIoControl(g_hDrv, IOCTL_IO_PROTECT_PROCESS_BEGIN, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}

BOOL Vu驱动::VU_保护_进程_结束(DWORD64 进程ID)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.PID = 进程ID;

	return DeviceIoControl(g_hDrv, IOCTL_IO_PROTECT_PROCESS_END, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}


BOOL Vu驱动::VU_保护_窗口_开始(DWORD64 窗口句柄, DWORD64 进程ID)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.Buf = 窗口句柄;
	msgInfo.PID = 进程ID;

	return DeviceIoControl(g_hDrv, IOCTL_IO_PROTECT_WINDOW_BEGIN, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}

BOOL Vu驱动::VU_保护_窗口_结束(DWORD64 窗口句柄, DWORD64 进程ID)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.Buf = 窗口句柄;
	msgInfo.PID = 进程ID;

	return DeviceIoControl(g_hDrv, IOCTL_IO_PROTECT_WINDOW_END, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}

BOOL Vu驱动::VU_保护_游戏_开始(DWORD64 窗口句柄, DWORD64 进程ID)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.Buf = 窗口句柄;
	msgInfo.PID = 进程ID;

	return DeviceIoControl(g_hDrv, IOCTL_IO_PROTECT_GAME_BEGIN, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}

BOOL Vu驱动::VU_保护_游戏_结束(DWORD64 窗口句柄, DWORD64 进程ID)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.Buf = 窗口句柄;
	msgInfo.PID = 进程ID;

	return DeviceIoControl(g_hDrv, IOCTL_IO_PROTECT_GAME_END, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}



BOOL Vu驱动::VU_硬件_修改硬盘序号(CHAR* 序号, DWORD64 文本长度)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.Buf = (DWORD64)序号;
	msgInfo.Size = 文本长度;

	return DeviceIoControl(g_hDrv, IOCTL_IO_HARDWARE_DISK, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}


BOOL Vu驱动::VU_硬件_修改声卡序号(CHAR* 序号, DWORD64 文本长度)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.Buf = (DWORD64)序号;
	msgInfo.Size = 文本长度;

	return DeviceIoControl(g_hDrv, IOCTL_IO_HARDWARE_VOLUMES, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}


BOOL Vu驱动::VU_硬件_修改网卡序号(CHAR* 序号, DWORD64 文本长度)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.Buf = (DWORD64)序号;
	msgInfo.Size = 文本长度;

	return DeviceIoControl(g_hDrv, IOCTL_IO_HARDWARE_MAC, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}


BOOL Vu驱动::VU_硬件_修改主板序号(CHAR* 序号, DWORD64 文本长度)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER				msgInfo = { 0 };
	msgInfo.Buf = (DWORD64)序号;
	msgInfo.Size = 文本长度;

	return DeviceIoControl(g_hDrv, IOCTL_IO_HARDWARE_SMBOIS, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}


BOOL Vu驱动::VU_硬件_修改显卡序号(CHAR* 序号, DWORD64 文本长度)
{
	DWORD64 pAddr = 0;
	DWORD				returnLegth = 0;
	IOCTL_BUFFER		msgInfo = { 0 };
	msgInfo.Buf = (DWORD64)序号;
	msgInfo.Size = 文本长度;

	return DeviceIoControl(g_hDrv, IOCTL_IO_HARDWARE_GPU, &msgInfo, sizeof(msgInfo), &pAddr, sizeof(pAddr), &returnLegth, NULL);
}