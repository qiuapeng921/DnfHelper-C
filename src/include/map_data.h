#include "struct.h"

namespace mapData {

    VOID Encode(ULONG64 addr, LONG data);

    ULONG64 Decode(ULONG64 addr);

    ULONG GetGameStat();

    BOOL IsTown();

    BOOL IsOpenTheDoor();

    BOOL IsBossRoom();

    CoordinateType GetBossRoom();

    BOOL IsPassBoss();

    CoordinateType GetCutRoom();

    ULONG GetMapNum();

    ULONG GetRolePl();

    ULONG GetRoleLevel();

    string GetMapName();
}