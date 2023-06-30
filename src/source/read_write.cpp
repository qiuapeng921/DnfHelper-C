//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "read_write.h"

BYTE ReadShort(ULONG64 address) {
    if (IsBadReadPtr((VOID*)address, 2)) {
        return 0;
    }
    return *(BYTE*)address;
}

INT ReadInt(ULONG64 address) {
    if (address == 0) return 0;
    if (IsBadReadPtr((PVOID)address, sizeof(INT))) return 0;
    return *(INT*)address;
}

ULONG64 ReadLong(ULONG64 address) {
    if (IsBadReadPtr((VOID*)address, 8)) {
        return 0;
    }
    return *(ULONG64*)address;
}

double ReadFloat(ULONG64 address) {
    if (IsBadReadPtr((VOID*)address, 8)) {
        return 0;
    }
    return *(double*)address;
}

BYTE ReadByte(ULONG64 address) {
    if (IsBadReadPtr((VOID*)address, 1)) {
        return 0;
    }
    return *(BYTE*)address;
}

vector<BYTE> ReadByteArr(ULONG64 address, DWORD len) {
    vector<BYTE> result;
    if (IsBadReadPtr((VOID*)address, len)) {
        return {};
    }
    for (size_t i = 0; i < len; i++) {
        result.insert(result.end(), *(BYTE*)address++);
    }
    return result;
}

void WriteShort(ULONG64 address, WORD data) {
    if (IsBadReadPtr((VOID*)address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID)address, 4, 64, &old_protect);
    *(WORD*)address = data;
    VirtualProtect((LPVOID)address, 4, old_protect, &old_protect);
}

void WriteInt(ULONG64 address, long data) {
    if (IsBadReadPtr((VOID*)address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID)address, 4, 64, &old_protect);
    *(DWORD*)address = data;
    VirtualProtect((LPVOID)address, 4, old_protect, &old_protect);
}

void WriteLong(ULONG64 address, ULONG64 data) {
    if (IsBadReadPtr((VOID*)address, 8)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID)address, 8, 64, &old_protect);
    *(ULONG64*)address = data;
    VirtualProtect((LPVOID)address, 8, old_protect, &old_protect);
}

void WriteFloat(ULONG64 address, float data) {
    if (IsBadReadPtr((VOID*)address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID)address, 4, 64, &old_protect);
    *(float*)address = data;
    VirtualProtect((LPVOID)address, 4, old_protect, &old_protect);
}

void WriteByte(ULONG64 address, BYTE data) {
    if (IsBadReadPtr((VOID*)address, 4)) {
        return;
    }
    DWORD old_protect;
    VirtualProtect((LPVOID)address, 1, 64, &old_protect);
    *(BYTE*)address = data;
    VirtualProtect((LPVOID)address, 1, old_protect, &old_protect);
}

void WriteByteArr(ULONG64 address, const vector<BYTE> &byteData) {
    if (IsBadReadPtr((VOID*)address, 1)) {
        return;
    }
    DWORD old_protect;
    // 修改内存属性
    VirtualProtect((LPVOID)address, byteData.size(), 64, &old_protect);
    for (unsigned char i: byteData) {
        *(BYTE*)address++ = i;
    }
    // 还原内存属性
    VirtualProtect((LPVOID)address, byteData.size(), old_protect, &old_protect);
}

ULONG_PTR AllocMem(SIZE_T size) {
    return (ULONG_PTR)VirtualAlloc(nullptr, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
}

bool FreeMem(ULONG addr) {
    return (bool)VirtualFree(nullptr, addr, NULL);
}