#pragma once

#include <minwindef.h>

typedef ULONG64(_fastcall *_Func_Call)(
        ULONGLONG RCX_,
        ULONGLONG RDX_,
        ULONGLONG R8_,
        ULONGLONG R9_,
        ULONGLONG R10_,
        ULONGLONG R11_,
        ULONGLONG R12_,
        ULONGLONG R13_,
        ULONGLONG R14_,
        ULONGLONG R15_
);

ULONG64 Func_CALL(ULONGLONG ADDR_, ULONGLONG RCX_ = 0, ULONGLONG RDX_ = 0, ULONGLONG R8_ = 0, ULONGLONG R9_ = 0,
                  ULONGLONG R10_ = 0, ULONGLONG R11_ = 0, ULONGLONG R12_ = 0, ULONGLONG R13_ = 0,
                  ULONGLONG R14_ = 0, ULONGLONG R15_ = 0);