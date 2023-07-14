//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "address.h"
#include "notice.h"
#include "read_write.h"
#include "helper.h"
#include "call.h"

// 静态变量初始化
static ULONG64 emptyAddrOne = AllocMem(4096);
static ULONG64 emptyAddrTwo = AllocMem(4096);

// 七彩公告
void ColorfulNotice(const wchar_t *message, int msgType) {
    std::wstring content = L"DnfHelper √ " + std::wstring(message);
    LPCWSTR TempStr = content.c_str();

    WriteLong(emptyAddrOne + 8, (ULONG64)TempStr);
    WriteByteArr(emptyAddrTwo, helper::AnsiToUnicode("Interface/newstyle/windows/Chatting/raid_partyicon.img"));
    WriteLong(emptyAddrOne + 24, 0);
    WriteLong(emptyAddrOne + 28, -1);

    if (msgType == 0) {
        WriteLong(emptyAddrOne + 32, 12615935);
        WriteLong(emptyAddrOne + 36, 38);
        WriteLong(emptyAddrOne + 116, 65535);
    } else if (msgType == 1) {
        WriteLong(emptyAddrOne + 32, 12615935);
        WriteLong(emptyAddrOne + 36, 17);
        WriteLong(emptyAddrOne + 116, 16776960);
    }

    WriteLong(emptyAddrOne + 40, 16);
    WriteLong(emptyAddrOne + 44, emptyAddrTwo);
    WriteLong(emptyAddrOne + 56, emptyAddrTwo);

    Func_CALL(神话CALL, emptyAddrOne);
}

void OrdinaryNotice(const wchar_t *message, int msgType) {

}