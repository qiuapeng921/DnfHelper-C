#include "pch.h"
#include "Common.h"

DWORD _GetProcessId(LPCWSTR 进程) {
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

CString _IntToCString(int value)
{
	CString str;
	str.Format(L"%d", value);
	return str;
}

char* _AnsiToUnicode(char* str)
{
	int dwNum = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	char* pwText;
	pwText = new char[(__int64)dwNum * 2];
	MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)pwText, dwNum);
	return pwText;
}

CString _UnicodeToAnsi(vector<byte> vby)
{
	int length = (int)vby.size();
	byte* str = new byte[vby.size()]();
	for (int i = 0; i < length; ++i)
	{
		str[i] = vby[i];
	}
	length = length / 2;
	length = ::WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)str, length, NULL, 0, NULL, NULL);
	char* resultCha = new char[(__int64)length + 1]();
	::WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)str, length, resultCha, length, NULL, NULL);
	CString result(resultCha);
	return result;
}

CString _GetDesktopPath()
{
	char desktop[MAX_PATH];
	::SHGetSpecialFolderPathA(0, desktop, CSIDL_DESKTOPDIRECTORY, 0);
	CString path(desktop);
	return path + L"\\";
}
VOID _WriteConfig(CString 节, CString 项, CString 值)
{
	::WritePrivateProfileString(节, 项, 值, _GetDesktopPath() + L"WeGame.ini");
}
DWORD _ReadConfig(CString 节, CString 项)
{
	DWORD  result;
	result = GetPrivateProfileIntW(节, 项, 0, _GetDesktopPath() + L"WeGame.ini");
	return result;
}

VOID _InitConfig()
{
	_WriteConfig(L"自动配置", L"刷图方式", L"1");
	_WriteConfig(L"自动配置", L"角色数量", L"1");
	_WriteConfig(L"自动配置", L"副本编号", L"104");
	_WriteConfig(L"自动配置", L"副本等级", L"4");
	_WriteConfig(L"自动配置", L"顺图方式", L"1");


	_WriteConfig(L"全屏配置", L"技能代码", L"70231");
	_WriteConfig(L"全屏配置", L"技能伤害", L"5201314");
	_WriteConfig(L"全屏配置", L"技能频率", L"500");
	_WriteConfig(L"全屏配置", L"技能个数", L"3");
}

HANDLE _CreateThread(PVOID 线程子程序)
{
	HANDLE handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)线程子程序, NULL, 0, 0);
	return handle;
}
BOOL _DeleteThread(HANDLE 线程句柄)
{
	if (CloseHandle(线程句柄)) {
		::TerminateThread(线程句柄, 0);
	}
	return true;
}

//转换16进制
BYTE _ConvertHexChar(BYTE ch)
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
INT _Rand(int min, int max)
{
	int m;
	m = (max - min);
	m = min + (int)double(rand()) / RAND_MAX * m;
	return m;
}

// 获取当前时间
CString _GetCurrentTime() 
{
	CString str;
	CTime tm(CTime::GetCurrentTime());
	return tm.Format(L"WeGame：%Y年%m月%d日 %X");
}



//使用示例：_DebugStringA("%d,%s",123,"hello");
VOID _DebugStringA(const char* lpcszOutputString, ...) {
	string strResult;
	if (NULL != lpcszOutputString)
	{
		va_list marker = NULL;
		va_start(marker, lpcszOutputString); //初始化变量参数
		size_t nLength = (__int64)_vscprintf(lpcszOutputString, marker) + 1; //获取格式化字符串长度
		std::vector<char> vBuffer(nLength, '\0'); //创建用于存储格式化字符串的字符数组
		int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, lpcszOutputString, marker);
		if (nWritten > 0)
		{
			strResult = &vBuffer[0];
		}
		va_end(marker); //重置变量参数
	}
	if (!strResult.empty())
	{
		string strFormated = "[WeGame] ";
		strFormated.append(strResult);
		OutputDebugStringA(strFormated.c_str());
	}
}

//使用示例：MyOutputDebugStringW(L"%d,%s",456,L"world!");
VOID _DebugStringW(const wchar_t* lpcwszOutputString, ...) {
	wstring strResult;
	if (NULL != lpcwszOutputString)
	{
		va_list marker = NULL;
		va_start(marker, lpcwszOutputString); //初始化变量参数
		size_t nLength = (__int64)_vscwprintf(lpcwszOutputString, marker) + 1; //获取格式化字符串长度
		std::vector<wchar_t> vBuffer(nLength, '\0'); //创建用于存储格式化字符串的字符数组
		int nWritten = _vsnwprintf_s(&vBuffer[0], vBuffer.size(), nLength, lpcwszOutputString, marker);
		if (nWritten > 0)
		{
			strResult = &vBuffer[0];
		}
		va_end(marker); //重置变量参数
	}
	if (!strResult.empty())
	{
		wstring strFormated = L"[WeGame] ";
		strFormated.append(strResult);
		OutputDebugStringW(strFormated.c_str());
	}
}

// _IntToBytes(5527029768);
vector<byte> _IntToBytes(DWORD64 num,int lenght)
{
	vector<byte>bytes;
	for (int i = 0; i < lenght; i++)
	{
		int offset = i * 8;
		byte byteTmp = (num >> offset) & 0xFF;
		bytes.push_back(byteTmp);
	}
	return bytes;
}

// byte数组转int：
DWORD64 _BytesToInt64(const BYTE* bytes, int lenght)
{
	DWORD64 num = 0;
	for (int i = 0; i < lenght; i++)
	{
		DWORD64 offset = i * 8;
		num |= (bytes[i] & 0xFF) << offset;
	}
	return num;
}

// byte数组转16进制字符串：
string _BytesToHexStr(const unsigned char* bytes, const int length)
{
	string buff = "";
	for (int i = 0; i < length; i++)
	{
		int high = bytes[i] / 16;
		int low = bytes[i] % 16;
		buff += (high < 10) ? ('0' + high) : ('A' + high - 10);
		buff += (low < 10) ? ('0' + low) : ('A' + low - 10);
	}
	return buff;
}


// 16进制字符串转byte数组：
void _HexToBytes(const string hex, unsigned char* bytes)
{
	int len = (int)hex.length() / 2;
	string strByte;
	unsigned int num;
	for (__int64 i = 0; i < len; i++)
	{
		strByte = hex.substr(i * 2, 2);
		sscanf_s(strByte.c_str(), "%x", &num);
		bytes[i] = num;
	}
}

// 追加字节集 
// vector<byte> oldBytes = { 255, 37, 0, 0, 0, 0 };
// vector<byte> newBytes = { 144, 144, 144, 144, 144 };
// vector<byte> Bytes = _AppendToBytes(oldBytes, newBytes);
// vector<byte> Bytes1 = _AppendToBytes(Bytes, _IntToBytes(1111111111111, 4));
ByteArr _AppendToBytes(ByteArr oldBytes, ByteArr newBytes)
{
	ByteArr bytes = oldBytes;
	if (oldBytes.size() == 0)
	{
		return bytes;
	}
	if (newBytes.size() == 0)
	{
		return bytes;
	}

	for (int i = 1; i <= newBytes.size(); i++)
	{
		bytes.push_back(newBytes[i - 1]);
	}

	return bytes;
}