#pragma once

#include "headers.h"

// CoordinateType 坐标型
struct CoordinateType {
    uint32_t X;
    uint32_t Y;
    uint32_t Z;
};

// MapDataType 地图数据
struct MapDataType {
    string MapName;                     // 地图名称
    uint32_t MapNum;                    // 地图编号
    vector<uint32_t> MapChannel;        // 地图通道
    CoordinateType StartZb;             // 起始坐标
    CoordinateType EndZb;               // 终点坐标
    uint32_t Width;                     // 宽
    uint32_t Height;                    // 高
    vector<CoordinateType> MapRoute;    // 地图走法
    uint32_t ConsumeFatigue;            // 消耗疲劳
    uint32_t ChannelNum;                // 通道数量
    uint64_t Tmp;                       // 临时变量
};

// GameMapType 游戏地图
struct GameMapType {
    CoordinateType MapCoordinates;      // 地图坐标
    bool Left;                          // 地图左边
    bool Right;                         // 地图右边
    bool Up;                            // 地图上边
    bool Down;                          // 地图下边
    uint32_t MapChannel;                // 地图通道
    uint32_t BackgroundColor;           // 背景颜色
};

// MapNodeType 地图节点
struct MapNodeType {
    uint64_t F;                         // 地图F点
    uint64_t G;                         // 地图G点
    uint64_t H;                         // 地图H点
    CoordinateType CurrentCoordinates;  // 当前坐标
    CoordinateType FinalCoordinates;    // 最终坐标
};