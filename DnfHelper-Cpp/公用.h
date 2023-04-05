// winsdk
#include "Windows.h"
// win驱动
#include <winsvc.h>
// 进程
#include "tlhelp32.h"

// 打印输出
#include <iostream>

#include <string>
// 字符串转换
#include <codecvt>

// 集合
#include <vector>

// 随机种子
#include <cstdlib>

using namespace std;

DWORD GetProcessIdByName(LPCWSTR 进程);

vector<byte> 字节集追加(vector<byte> oldByteArr, vector<vector<byte>> newByteArrs);

// 整数转字节数组
vector<byte>& IntToByteArr(DWORD64 num, int length);

vector<byte> MakeByteArr(int num);

vector<byte> AnsiToUnicode(string str);

string UnicodeToAnsi(const vector<byte>& vby);

wstring GetDesktopPath();


void 写配置(wstring 节, wstring 项, wstring 值);

DWORD 读配置(wstring 节, wstring 项);

const wchar_t* format_string(const wchar_t* format, ...);

wstring get_current_time_string();

wstring get_running_time_string();