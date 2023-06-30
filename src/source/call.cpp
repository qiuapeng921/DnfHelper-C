//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "call.h"
#include "address.h"

ULONG64 Func_CALL(ULONGLONG ADDR_, ULONGLONG RCX_, ULONGLONG RDX_, ULONGLONG R8_, ULONGLONG R9_, ULONGLONG R10_,
                  ULONGLONG R11_, ULONGLONG R12_, ULONGLONG R13_, ULONGLONG R14_, ULONGLONG R15_) {
    _Func_Call MyFastCall = (_Func_Call) ADDR_;

    return MyFastCall(RCX_,
                      RDX_,
                      R8_,
                      R9_,
                      R10_,
                      R11_,
                      R12_,
                      R13_,
                      R14_,
                      R15_);
}


// 地图CALL
uint64_t MapCall(int 地图编号) {
    return Func_CALL(地图CALL, 地图编号);
}

// 标识Call
int MarkCall() {
    return (int) Func_CALL(标识CALL);
}

// 技能CALL
void SkillCall(ULONG64 pointer, int code, int harm, int x, int y, int z, float size) {
    ULONG64 array[100] = {0};
    *(ULONG64 *) (ULONG64) array = pointer;
    *(ULONG *) ((ULONG64) array + 16) = code;
    *(ULONG *) ((ULONG64) array + 20) = harm;
    *(ULONG *) ((ULONG64) array + 32) = x;
    *(ULONG *) ((ULONG64) array + 36) = y;
    *(ULONG *) ((ULONG64) array + 40) = z;
    *(float *) ((ULONG64) array + 140) = size;
    *(float *) ((ULONG64) array + 144) = 65535;
    *(float *) ((ULONG64) array + 148) = 65535;
    Func_CALL(结构技能CALL, (ULONG64) array, MarkCall());
}

// 坐标CALL
void CoordinateCall(uint64_t pointer, uint32_t X, uint32_t Y, uint32_t Z) {
    Func_CALL(坐标CALL, pointer, X, Y, Z);
}