#include <windows.h>

double 读小数型(u_int64 address);

INT 读整数型(u_int64 address);

ULONG64 读长整数(u_int64 address);

BYTE 读字节型(u_int64 address);

BYTE 读短整数(u_int64 address);

void 写长整数(u_int64 address, u_int64 data);

void 写字节型(u_int64 address, byte data);

void 写整数型(u_int64 address, u_int data);

void 写小数型(u_int64 address, float data);

void 写短整数(u_int64 address, short data);
