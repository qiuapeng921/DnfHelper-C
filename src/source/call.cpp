//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "call.h"
#include "address.h"
#include "read_write.h"

ULONG64 Func_CALL(ULONG64 ADDR_,
                  ULONG64 RCX_,
                  ULONG64 RDX_,
                  ULONG64 R8_,
                  ULONG64 R9_,
                  ULONG64 R10_,
                  ULONG64 R11_,
                  ULONG64 R12_,
                  ULONG64 R13_,
                  ULONG64 R14_,
                  ULONG64 R15_) {
    auto MyFastCall = (_Func_Call)ADDR_;

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

// 取人物指针Call
ULONG64 GetPerPtrCall() {
    return Func_CALL(人物CALL);
}

void BufferCall(ULONG64 packHeader) {
    Func_CALL(缓冲CALL, 发包基址, packHeader);
}

void EncryptCall(ULONG64 packHeader, int len) {
    ULONG64 packParam = 0;
    if (len == 1) { packParam = 加密CALL_1; }
    if (len == 2) { packParam = 加密CALL_2; }
    if (len == 4) { packParam = 加密CALL_3; }
    if (len == 8) { packParam = 加密CALL_4; }
    Func_CALL(packParam, 发包基址, packHeader);
}

void SendCall() {
    Func_CALL(发包CALL);
}


VOID RefreshCall(ULONG64 addr) {
    Func_CALL(刷新CALL, addr, 0);
}


// 地图CALL
ULONG64 MapCall(int mapId) {
    return Func_CALL(地图CALL, mapId);
}

// 标识Call
ULONG64 MarkCall() {
    return Func_CALL(标识CALL);
}

// 技能CALL
void SkillCall(ULONG64 pointer, int code, int harm, int x, int y, int z, float size) {
    ULONG64 array[100] = {0};
    *(ULONG64 *)(ULONG64)array = pointer;
    *(ULONG *)((ULONG64)array + 16) = code;
    *(ULONG *)((ULONG64)array + 20) = harm;
    *(ULONG *)((ULONG64)array + 32) = x;
    *(ULONG *)((ULONG64)array + 36) = y;
    *(ULONG *)((ULONG64)array + 40) = z;
    *(float *)((ULONG64)array + 140) = size;
    *(float *)((ULONG64)array + 144) = 65535;
    *(float *)((ULONG64)array + 148) = 65535;
    Func_CALL(技能CALL, (ULONG64)array, MarkCall());
}

// 坐标CALL
void CoordinateCall(uint64_t pointer, uint32_t X, uint32_t Y, uint32_t Z) {
    Func_CALL(坐标CALL, pointer, X, Y, Z);
}

void 过图Call(int direction) {
    ULONG64 emptyAddr[200] = {0};
    ULONG64 param = ReadLong(ReadLong(ReadLong(房间编号) + 时间基址) + 顺图偏移);
    Func_CALL(过图CALL, param, direction, (ULONG64)emptyAddr, 0xFFFFFFFF);
}

void 整理背包Call(ULONG64 addr, int backpackType) {
    int goodsType = 1;
    if (backpackType == 1) { goodsType = 1; }
    if (backpackType == 11) { goodsType = 20; }
    if (backpackType == 12) { goodsType = 21; }
    Func_CALL(整理CALL, ReadLong(addr), goodsType, backpackType);
}

void SelectMap() {
    Func_CALL(选图CALL, ReadLong(角色指针));
}

void 进图Call(ULONG64 mapId, ULONG64 mapLevel, ULONG64 taskId, ULONG64 深渊模式) {
    if (taskId > 0) {
        Func_CALL(进图CALL, ReadLong(角色指针), taskId, 0, 0, 0, 0xFFFFFFFF);
    } else {
        Func_CALL(进图CALL, ReadLong(角色指针), mapId, mapLevel, 深渊模式, 0, 0xFFFFFFFF);
    }
}

void 回城Call(int param) {
    Func_CALL(回城CALL, ReadLong(回城参数), param, 1, 1);
}