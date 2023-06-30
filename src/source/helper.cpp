//
// Created by Administrator on 2023/06/30.
//

#include "headers.h"
#include "helper.h"

vector<BYTE> AnsiToUnicode(const string &str) {
    vector<BYTE> Ret;
    DWORD dwNum = MultiByteToWideChar(936, 0, str.c_str(), -1, nullptr, 0);
    BYTE*pwText;
    pwText = new BYTE[dwNum * 2];
    MultiByteToWideChar(936, 0, str.c_str(), -1, (LPWSTR)pwText, dwNum * 2);

    for (size_t i = 0; i < dwNum * 2; i++) {
        Ret.push_back(pwText[i]);
    }
    Ret.push_back(0);
    Ret.push_back(0);
    return Ret;
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
string IntToString(int number) {
    return to_string(number);
}

// 取空白字节集
vector<BYTE> GetEmptyByte(int num) {
    vector<BYTE> res;
    for (size_t i = 0; i < num; i++) {
        res.push_back(0);
    }
    return res;
}