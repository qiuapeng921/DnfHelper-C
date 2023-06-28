#include "../common/headers.h"
#include "read_write.h"

double 读小数型(uint64_t address) {
    if (IsBadReadPtr((VOID *) address, 8)) {
        return 0;
    }
    return *(double *) address;
}

INT 读整数型(uint64_t address) {
    if (address == 0) return 0;
    if (IsBadReadPtr((PVOID) address, sizeof(INT))) return 0;
    return *(INT *) address;
}

uint64_t 读长整数(uint64_t address) {
    if (IsBadReadPtr((VOID *) address, 8)) {
        return 0;
    }
    return *(uint64_t *) address;
}

BYTE 读字节型(uint64_t address) {
    if (IsBadReadPtr((VOID *) address, 1)) {
        return 0;
    }
    return *(BYTE *) address;
}

BYTE 读短整数(uint64_t address) {
    if (IsBadReadPtr((VOID *) address, 2)) {
        return 0;
    }
    return *(BYTE *) address;
}

void 写长整数(uint64_t address, uint64_t data) {
    if (IsBadReadPtr((VOID *) address, 8)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 8, 64, &old_protect);
    *(uint64_t *) address = data;
    VirtualProtect((LPVOID) address, 8, old_protect, &old_protect);
}

void 写字节型(uint64_t address, BYTE data) {
    if (IsBadReadPtr((VOID *) address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 1, 64, &old_protect);
    *(BYTE *) address = data;
    VirtualProtect((LPVOID) address, 1, old_protect, &old_protect);
}

void 写整数型(uint64_t address, long data) {
    if (IsBadReadPtr((VOID *) address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 4, 64, &old_protect);
    *(DWORD *) address = data;
    VirtualProtect((LPVOID) address, 4, old_protect, &old_protect);
}

void 写小数型(uint64_t address, float data) {
    if (IsBadReadPtr((VOID *) address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 4, 64, &old_protect);
    *(float *) address = data;
    VirtualProtect((LPVOID) address, 4, old_protect, &old_protect);
}

void 写短整数(uint64_t address, WORD data) {
    if (IsBadReadPtr((VOID *) address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID) address, 4, 64, &old_protect);
    *(WORD *) address = data;
    VirtualProtect((LPVOID) address, 4, old_protect, &old_protect);
}
