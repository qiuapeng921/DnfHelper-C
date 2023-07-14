//
// Created by Administrator on 2023/06/30.
//

namespace helper {
    // 获取桌面路径
    wstring GetDesktopPath();

    vector<BYTE> AnsiToUnicode(const string &str);

    string UnicodeToAnsi(const vector<BYTE> &byteArr);

    // 字节相加
    vector<BYTE> AddByte(vector<BYTE> oldData, vector<BYTE> newData);

    // 整数转字节数组
    vector<BYTE> IntToByte(ULONG64 data);

    // 取文本长度
    size_t GetTextLength(const string &text);

    // 取模块地址
    ULONG64 GetModuleAddr(const char moduleName[]);

    // 取随机数
    ULONG64 GetRandNum(ULONG64 mix, ULONG64 max);

    // 整数到文本
    wstring IntToString(int number);

    // 取空白字节集
    vector<BYTE> GetEmptyByte(int num);

    // 取文本右边
    wstring GetStrRight(const wstring &str, size_t len);

    // 取文本左边
    wstring GetStrLeft(const wstring &str, size_t len);

    // 分割文本
    void SplitStr(const wstring &str, vector<wstring> &tokens, const wstring &delimiters);
}