#pragma once

#include "headers.h"

// 全局数据
struct GlobalData {
    HWND GameHandle;
    WNDPROC WinMessage;
};
extern GlobalData global;

// CoordinateType 坐标型
struct CoordinateType {
    INT X;
    INT Y;
    INT Z;
};

// MapDataType 地图数据
struct MapDataType {
    CHAR *MapName;                      // 地图名称
    ULONG MapNum;                       // 地图编号
    vector<ULONG> MapChannel;           // 地图通道
    CoordinateType StartZb;             // 起始坐标
    CoordinateType EndZb;               // 终点坐标
    ULONG Width;                        // 宽
    ULONG Height;                       // 高
    vector<CoordinateType> MapRoute;    // 地图走法
    ULONG ConsumeFatigue;               // 消耗疲劳
    ULONG ChannelNum;                   // 通道数量
    ULONG64 Tmp;                        // 临时变量
};

// GameMapType 游戏地图
struct GameMapType {
    CoordinateType MapCoordinates;      // 地图坐标
    bool Left;                          // 地图左边
    bool Right;                         // 地图右边
    bool Up;                            // 地图上边
    bool Down;                          // 地图下边
    ULONG MapChannel;                   // 地图通道
    ULONG BackgroundColor;              // 背景颜色
};

// MapNodeType 地图节点
struct MapNodeType {
    ULONG F;                            // 地图F点
    ULONG G;                            // 地图G点
    DWORD H;                            // 地图H点
    CoordinateType CurrentCoordinates;  // 当前坐标
    CoordinateType FinalCoordinates;    // 最终坐标
};