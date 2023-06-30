//
// Created by Administrator on 2023/06/30.
//

#include "headers.h"
#include "helper.h"

// 获取桌面路径
wstring GetDesktopPath() {
    // 获取用户目录的路径
    const wchar_t *userProfilePath = _wgetenv(L"USERPROFILE");

    if (userProfilePath != nullptr) {
        // 构建桌面路径
        wstring desktopPath = wstring(userProfilePath) + L"\\Desktop";
        return desktopPath;
    }

    return L"";
}


vector<BYTE> AnsiToUnicode(const string &str) {
    vector<BYTE> Ret;
    DWORD dwNum = MultiByteToWideChar(936, 0, str.c_str(), -1, nullptr, 0);
    BYTE *pwText;
    pwText = new BYTE[dwNum * 2];
    MultiByteToWideChar(936, 0, str.c_str(), -1, (LPWSTR)pwText, dwNum * 2);

    for (size_t i = 0; i < dwNum * 2; i++) {
        Ret.push_back(pwText[i]);
    }
    Ret.push_back(0);
    Ret.push_back(0);
    return Ret;
}

string UnicodeToAnsi(const vector<BYTE> &byteArr) {
    const size_t byteLen = byteArr.size();
    const unique_ptr<wchar_t[]> unicode(new wchar_t[byteLen]);
    for (size_t i = 0; i < byteLen; i++) {
        unicode[i] = byteArr[i];
    }

    const int charLen = WideCharToMultiByte(936, 0, unicode.get(), -1, nullptr, 0, nullptr, nullptr);
    string buffer(charLen, '\0');
    WideCharToMultiByte(936, 0, unicode.get(), -1, &buffer[0], charLen, nullptr, nullptr);

    return buffer;
}

// 字节相加
vector<BYTE> AddByte(vector<BYTE> oldData, vector<BYTE> newData) {
    vector<BYTE> addr(oldData.size() + newData.size());
    for (size_t i = 0; i < oldData.size(); i++) {
        addr[i] = oldData[i];
    }
    for (size_t i = 0; i < newData.size(); i++) {
        addr[oldData.size() + i] = newData[i];
    }
    return addr;
}

// 整数转字节数组
vector<BYTE> IntToByte(ULONG64 data) {
    size_t size = sizeof(data);
    vector<BYTE> ret(size);
    memcpy(ret.data(), &data, size);
    return ret;
}

// 取文本长度
size_t GetTextLength(const string &text) {
    return text.length();
}

// 取模块地址
ULONG64 GetModuleAddr(const char moduleName[]) {
    return (UINT64)GetModuleHandleA(moduleName);
}

// 取随机数
ULONG64 GetRandNum(ULONG64 mix, ULONG64 max) {
    srand((int)time(nullptr));
    return rand() % (max - mix) + mix;
}

// 整数到文本
wstring IntToString(int number) {
    return to_wstring(number);
}

// 取空白字节集
vector<BYTE> GetEmptyByte(int num) {
    vector<BYTE> res;
    for (size_t i = 0; i < num; i++) {
        res.push_back(0);
    }
    return res;
}

// 取文本右边
wstring GetStrRight(const wstring &str, size_t len) {
    wstring result;
    if (len > str.size()) {
        len = 0;
    } else {
        len = str.size() - len;
    }
    result = str.substr(len);
    return result;
}

// 取文本左边
wstring GetStrLeft(const wstring &str, size_t len) {
    wstring result;
    if (len > str.size()) {
        len = str.size();
    }
    result = str.substr(0, len);
    return result;
}

// 分割文本
void SplitStr(const wstring &str, vector<wstring> &tokens, const wstring &delimiters) {
    wstring::size_type lastPos = str.find_first_not_of(delimiters, 0);
    wstring::size_type pos = str.find_first_of(delimiters, lastPos);
    while (wstring::npos != pos || wstring::npos != lastPos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}