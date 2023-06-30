//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "read_write.h"

double 读小数型(ULONG64 address) {
    if (IsBadReadPtr((VOID *) address, 8)) {
        return 0;
    }
    return *(double *) address;
}

INT 读整数型(ULONG64 address) {
    if (address == 0) return 0;
    if (IsBadReadPtr((PVOID) address, sizeof(INT))) return 0;
    return *(INT *) address;
}

ULONG64 读长整数(ULONG64 address) {
    if (IsBadReadPtr((VOID *) address, 8)) {
        return 0;
    }
    return *(ULONG64 *) address;
}

BYTE 读字节型(ULONG64 address) {
    if (IsBadReadPtr((VOID *) address, 1)) {
        return 0;
    }
    return *(BYTE *) address;
}

BYTE 读短整数(ULONG64 address) {
    if (IsBadReadPtr((VOID *) address, 2)) {
        return 0;
    }
    return *(BYTE *) address;
}

void 写长整数(ULONG64 address, ULONG64 data) {
    if (IsBadReadPtr((VOID *) address, 8)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 8, 64, &old_protect);
    *(ULONG64 *) address = data;
    VirtualProtect((LPVOID) address, 8, old_protect, &old_protect);
}

void 写字节型(ULONG64 address, BYTE data) {
    if (IsBadReadPtr((VOID *) address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 1, 64, &old_protect);
    *(BYTE *) address = data;
    VirtualProtect((LPVOID) address, 1, old_protect, &old_protect);
}

void 写整数型(ULONG64 address, long data) {
    if (IsBadReadPtr((VOID *) address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 4, 64, &old_protect);
    *(DWORD *) address = data;
    VirtualProtect((LPVOID) address, 4, old_protect, &old_protect);
}

void 写小数型(ULONG64 address, float data) {
    if (IsBadReadPtr((VOID *) address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 4, 64, &old_protect);
    *(float *) address = data;
    VirtualProtect((LPVOID) address, 4, old_protect, &old_protect);
}

void 写短整数(ULONG64 address, WORD data) {
    if (IsBadReadPtr((VOID *) address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 4, 64, &old_protect);
    *(WORD *) address = data;
    VirtualProtect((LPVOID) address, 4, old_protect, &old_protect);
}
