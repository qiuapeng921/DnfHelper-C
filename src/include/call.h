//
// Created by Administrator on 2023/06/28.
//

#pragma once

typedef ULONG64(_fastcall *_Func_Call)(
        ULONG64 RCX_,
        ULONG64 RDX_,
        ULONG64 R8_,
        ULONG64 R9_,
        ULONG64 R10_,
        ULONG64 R11_,
        ULONG64 R12_,
        ULONG64 R13_,
        ULONG64 R14_,
        ULONG64 R15_
);

ULONG64 Func_CALL(ULONG64 ADDR_,
                  ULONG64 RCX_ = 0,
                  ULONG64 RDX_ = 0,
                  ULONG64 R8_ = 0,
                  ULONG64 R9_ = 0,
                  ULONG64 R10_ = 0,
                  ULONG64 R11_ = 0,
                  ULONG64 R12_ = 0,
                  ULONG64 R13_ = 0,
                  ULONG64 R14_ = 0,
                  ULONG64 R15_ = 0);

ULONG64 GetPerPtrCall();

// 刷新call
VOID RefreshCall(ULONG64 addr);

// HcCall 缓冲call
void BufferCall(ULONG64 param);

// JmCall 加密call
void EncryptCall(ULONG64 param, int len);

// FbCall 发包call
void SendCall();