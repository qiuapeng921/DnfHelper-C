// 读短整数
BYTE ReadShort(ULONG64 address);

// 读整数
INT ReadInt(ULONG64 address);

// 读长整数
ULONG64 ReadLong(ULONG64 address);

// 读小数
double ReadFloat(ULONG64 address);

// 读字节
BYTE ReadByte(ULONG64 address);

// 读字节数组
vector<BYTE> ReadByteArr(ULONG64 address, DWORD len);


// 写短整数
void WriteShort(ULONG64 address, WORD data);

// 写整数
void WriteInt(ULONG64 address, long data);

// 写长整数
void WriteLong(ULONG64 address, ULONG64 data);

// 写小数
void WriteFloat(ULONG64 address, float data);

// 写字节
void WriteByte(ULONG64 address, BYTE data);

// 写字节数组
void WriteByteArr(ULONG64 address, const vector<BYTE> &byteData);

// 申请内存
ULONG_PTR AllocMem(SIZE_T size);

// 释放内存
bool FreeMem(ULONG addr);