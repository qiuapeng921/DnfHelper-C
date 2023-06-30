//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "send.h"
#include "address.h"
#include "call.h"
#include "read_write.h"

void Send::BufferCall(ULONG64 packHeader) {
    Func_CALL(缓冲CALL, 发包基址, packHeader);
}

void Send::EncryptCall(ULONG64 packHeader, int len) {
    ULONG64 packParam = 0;
    if (len == 1) { packParam = 加密CALL_1; }
    if (len == 2) { packParam = 加密CALL_2; }
    if (len == 4) { packParam = 加密CALL_3; }
    if (len == 8) { packParam = 加密CALL_4; }
    Func_CALL(packParam, 发包基址, packHeader);
}

void Send::SendCall() {
    Func_CALL(发包CALL);
}