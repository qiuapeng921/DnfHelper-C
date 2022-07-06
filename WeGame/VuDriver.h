#pragma once

#include "Ioc.h"

class Vu驱动
{
public:
	template<class T>
	T 读内存(DWORD 进程ID, DWORD64 进程地址)
	{
		T buffer;
		VU_内存_读字节集(进程ID, 进程地址, &buffer, sizeof(T));
		return buffer;
	}

	template <class T>
	BOOL 写内存(DWORD 进程ID, DWORD64 进程地址, T 写入数据) {
		return VU_内存_写字节集(进程ID, 进程地址, &写入数据, sizeof(T));
	}


	VOID 设置驱动句柄(HANDLE hDrv);
	ULONG64 效验有效性(const char* key);
	ULONG64 VU_内存_置读写模式(DWORD 模式, DWORD 类型);
	//枚举指定进程模块 
	DWORD64	VU_内存_取模块基址(DWORD pid, const char* moduleName);
	//读内存函数，自己封装
	BOOL VU_内存_读字节集(DWORD pid, PVOID addr, PVOID pBuf, INT32 size);
	//写内存函数，自己封装
	BOOL VU_内存_写字节集(DWORD pid, PVOID addr, PVOID pBuf, INT32 size);
	DWORD64 VU_内存_申请(DWORD 进程ID, DWORD64 进程地址, DWORD64 申请长度, DWORD64 内存属性, BOOL 是否物理);
	DWORD64 VU_内存_释放(DWORD 进程ID, DWORD64 进程地址, DWORD64 内存长度, BOOL 是否物理);
	DWORD64 VU_内存_修改属性(DWORD 进程ID, DWORD64 地址, DWORD64 长度, DWORD64 内存属性);
	DWORD64 VU_内存_查询属性(DWORD 进程ID, DWORD64 地址);


	DWORD64 VU_超级注入CALL_置主线程获取模式(DWORD64 模式);
	DWORD64 VU_远程注入CALL(DWORD 进程ID, PBYTE CALL代码, DWORD CALL代码长度, BOOL 硬件物理执行);
	DWORD64 VU_远程执行CALL(DWORD 进程ID, DWORD64 目标地址, DWORD64 参数地址);
	DWORD64 VU_超级注入CALL(DWORD 进程ID, PBYTE CALL代码, DWORD CALL代码长度, DWORD 线程ID, BOOL 硬件物理执行);
	DWORD64 VU_超级执行CALL(DWORD 进程ID, DWORD64 目标地址, DWORD64 参数地址, DWORD 线程ID);

	BOOL VU_键鼠_安装();

	BOOL VU_隐藏文件_安装();
	BOOL VU_隐藏文件_卸载();
	DWORD64 VU_隐藏文件_文件(CHAR* 文件路径);
	DWORD64 VU_隐藏文件_目录(CHAR* 目录路径);


	BOOL VU_保护_安装();
	BOOL VU_保护_卸载();
	BOOL VU_保护_进程_开始(DWORD64 进程ID, BOOL 是否保护驱动);
	BOOL VU_保护_进程_结束(DWORD64 进程ID);


	BOOL VU_保护_窗口_开始(DWORD64 窗口句柄, DWORD64 进程ID);
	BOOL VU_保护_窗口_结束(DWORD64 窗口句柄, DWORD64 进程ID);
	BOOL VU_保护_游戏_开始(DWORD64 窗口句柄, DWORD64 进程ID);
	BOOL VU_保护_游戏_结束(DWORD64 窗口句柄, DWORD64 进程ID);

	BOOL VU_硬件_修改硬盘序号(CHAR* 序号, DWORD64 文本长度);
	BOOL VU_硬件_修改声卡序号(CHAR* 序号, DWORD64 文本长度);
	BOOL VU_硬件_修改网卡序号(CHAR* 序号, DWORD64 文本长度);
	BOOL VU_硬件_修改主板序号(CHAR* 序号, DWORD64 文本长度);
	BOOL VU_硬件_修改显卡序号(CHAR* 序号, DWORD64 文本长度);	
};