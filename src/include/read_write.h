BYTE ReadShort(ULONG64 address);

INT ReadInt(ULONG64 address);

ULONG64 ReadLong(ULONG64 address);

double ReadFloat(ULONG64 address);

BYTE ReadByte(ULONG64 address);


void WriteShort(ULONG64 address, WORD data);

void WriteInt(ULONG64 address, long data);

void WriteLong(ULONG64 address, ULONG64 data);

void WriteFloat(ULONG64 address, float data);

void WriteByte(ULONG64 address, BYTE data);
