#include "pch.h"
#include "公用.h"

DWORD 取进程ID(TCHAR 进程[]) {
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnap) {
		return 0;
	}

	if (Process32First(hSnap, &pe))
	{
		while (Process32Next(hSnap, &pe)) {
			if (lstrcmpi(进程, pe.szExeFile) == 0) {
				return pe.th32ProcessID;
			}
		}
	}
	CloseHandle(hSnap);
	return 0;
}

CString 整数到文本(int 值)
{
	CString str;
	str.Format(L"%d", 值);
	return str;
}

char* AnsiToUnicode(char* str)
{
	DWORD64 dwNum = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	char* pwText;
	pwText = new char[dwNum * 2];
	MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)pwText, dwNum);
	return pwText;
}

CString Unicode转Ansi(vector<byte> vby)
{
	__int64 length = (int)vby.size();
	byte* str = new byte[vby.size()]();
	for (int i = 0; i < length; ++i)
	{
		str[i] = vby[i];
	}
	length = length / 2;
	length = ::WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)str, length, NULL, 0, NULL, NULL);
	char* resultCha = new char[length + 1]();
	::WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)str, length, resultCha, length, NULL, NULL);
	CString result(resultCha);
	return result;
}

CString 取桌面目录()
{
	char desktop[MAX_PATH];
	::SHGetSpecialFolderPathA(0, desktop, CSIDL_DESKTOPDIRECTORY, 0);
	CString path(desktop);
	return path + L"\\";
}
VOID 写配置项(CString 节, CString 项, CString 值)
{
	::WritePrivateProfileString(节, 项, 值, 取桌面目录() + L"WeGame.ini");
}
DWORD 读配置项(CString 节, CString 项)
{
	DWORD  result;
	result = GetPrivateProfileIntW(节, 项, 0, 取桌面目录() + L"WeGame.ini");
	return result;
}

VOID 初始化配置()
{
	写配置项(L"自动配置", L"刷图方式", L"1");
	写配置项(L"自动配置", L"角色数量", L"1");
	写配置项(L"自动配置", L"副本编号", L"104");
	写配置项(L"自动配置", L"副本等级", L"4");
	写配置项(L"自动配置", L"顺图方式", L"1");


	写配置项(L"全屏配置", L"技能代码", L"70231");
	写配置项(L"全屏配置", L"技能伤害", L"5201314");
	写配置项(L"全屏配置", L"技能频率", L"500");
	写配置项(L"全屏配置", L"技能个数", L"3");
}

void intToByte(int i, byte* bytes)
{
	size_t length = sizeof(int);
	// 初始化数组
	memset(bytes, 0, sizeof(byte) * length);
	bytes[0] = (byte)(0xff & i);
	bytes[1] = (byte)((0xff00 & i) >> 8);
	bytes[2] = (byte)((0xff0000 & i) >> 16);
	bytes[3] = (byte)((0xff000000 & i) >> 24);
	return;
}

VOID long64ToBytes(DWORD64 i, BYTE *bytes)
{
	size_t length = sizeof(DWORD64);
	memset(bytes, 0, sizeof(BYTE) * length);
	bytes[0] = (BYTE)(0xff & i);
	bytes[1] = (BYTE)((0xff00 & i) >> 8);
	bytes[2] = (BYTE)((0xff0000 & i) >> 16);
	bytes[3] = (BYTE)((0xff000000 & i) >> 24);
	bytes[4] = (BYTE)((0xff00000000 & i) >> 32);
	bytes[5] = (BYTE)((0xff0000000000 & i) >> 40);
	bytes[6] = (BYTE)((0xff000000000000 & i) >> 48);
	bytes[7] = (BYTE)((0xff00000000000000 & i) >> 56);
}

HANDLE 创建线程(PVOID 线程子程序)
{
	HANDLE 线程句柄 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)线程子程序, NULL, 0, 0);
	return 线程句柄;
}
BOOL 销毁线程(HANDLE 线程句柄)
{
	//CloseHandle(线程句柄);
	return ::TerminateThread(线程句柄, 0);
}

//转换16进制
BYTE ConvertHexChar(BYTE ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else
		return -1;
}

//随机数，最小值-最大值
int 取随机数(int min, int max)
{
	int m;
	m = (max - min);
	m = min + (int)double(rand()) / RAND_MAX * m;
	return m;
}

CString 取现行时间() {
	CString str;
	CTime tm(CTime::GetCurrentTime());
	return tm.Format(L"WeGame：%Y年%m月%d日 %X");
}
