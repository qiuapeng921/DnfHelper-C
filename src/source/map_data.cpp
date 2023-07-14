//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "read_write.h"

#include "map_data.h"
#include "address.h"
#include "struct.h"
#include "helper.h"
#include "call.h"

VOID mapData::Encode(ULONG64 addr, LONG data) {
    WriteLong(addr, data);
}

ULONG64 mapData::Decode(ULONG64 addr) {
    return ReadLong(addr);
}

// 0选角 1城镇 2选图 3图内 5选择频道
ULONG mapData::GetGameStat() {
    return ReadInt(游戏状态);
}

BOOL mapData::IsTown() {
    if (ReadLong(ReadLong(GetPerPtrCall()) + 地图偏移_1) == 0) {
        return true;
    }
    return false;
}

BOOL mapData::IsOpenTheDoor() {
    if (Decode(ReadLong(ReadLong(ReadLong(GetPerPtrCall()) + 地图偏移_1) + 16) + 开门偏移) == 0) {
        return true;
    }
    return false;
}

BOOL 判断_是否对话() {
    if (ReadLong(对话基址) == 1 && ReadLong(对话基址) != 0 && ReadLong(ESC对话基址) != 0) {
        return true;
    }
    return false;
}

BOOL mapData::IsBossRoom() {
    CoordinateType current = GetCutRoom();
    CoordinateType boss = GetBossRoom();
    if (current.X == boss.X && current.Y == boss.Y) {
        return true;
    }
    return false;
}

BOOL mapData::IsPassBoss() {
    ULONG64 roomData = ReadLong(ReadLong(ReadLong(房间编号) + 时间基址) + 门型偏移);
    int result = ReadInt(roomData + 篝火判断);
    if (result == 2 || result == 0) {
        return true;
    }
    return false;
}

CoordinateType mapData::GetBossRoom() {
    CoordinateType result = {};
    ULONG64 roomData = ReadLong(ReadLong(ReadLong(房间编号) + 时间基址) + 门型偏移);
    result.X = Decode(roomData + BOSS房间_X);
    result.Y = Decode(roomData + BOSS房间_Y);
    return result;
}

CoordinateType mapData::GetCutRoom() {
    CoordinateType result = {};
    ULONG64 roomData = ReadLong(ReadLong(ReadLong(房间编号) + 时间基址) + 门型偏移);
    result.X = ReadInt(roomData + 当前房间_X);
    result.Y = ReadInt(roomData + 当前房间_Y);
    return result;
}

ULONG mapData::GetMapNum() {
    return ReadInt(副本编号);
}

ULONG mapData::GetRolePl() {
    return Decode(最大疲劳) - Decode(已用疲劳);
}

ULONG mapData::GetRoleLevel() {
    return ReadInt(角色等级);
}

string mapData::GetMapName() {
    ULONG64 rootData = ReadLong(ReadLong(ReadLong(房间编号) + 时间基址) + 门型偏移);
    vector<BYTE> mapByte = ReadByteArr(ReadLong(rootData + 地图名称), 52);
    return helper::UnicodeToAnsi(mapByte);
}