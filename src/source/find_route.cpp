//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "struct.h"
#include "read_write.h"
#include "map_data.h"
#include "address.h"

#include "find_route.h"

MapDataType 寻路_地图数据() {
    MapDataType localMapData;
    ULONG64 localRoomData = ReadLong(ReadLong(ReadLong(房间编号) + 时间基址) + 门型偏移);
    ULONG64 localRoomIndex = 解密(localRoomData + 索引偏移);

    localMapData.Width = ReadInt(ReadLong(localRoomData + 宽高偏移) + localRoomIndex * 8 + 0);
    localMapData.Height = ReadInt(ReadLong(localRoomData + 宽高偏移) + localRoomIndex * 8 + 4);
    localMapData.Tmp = ReadLong(ReadLong(localRoomData + 数组偏移) + 32 * localRoomIndex + 8);
    localMapData.ChannelNum = localMapData.Width * localMapData.Height;
    for (ULONG i = 0; i < localMapData.ChannelNum; i++) {
        localMapData.MapChannel.insert(localMapData.MapChannel.begin() + i, ReadInt(localMapData.Tmp + i * 4));
    }
    localMapData.StartZb.X = mapData::GetCutRoom().X + 1;
    localMapData.StartZb.Y = mapData::GetCutRoom().Y + 1;
    localMapData.EndZb.X = mapData::GetBossRoom().X + 1;
    localMapData.EndZb.Y = mapData::GetBossRoom().Y + 1;
    if (localMapData.StartZb.X == localMapData.EndZb.X && localMapData.StartZb.Y == localMapData.EndZb.Y) {
        return localMapData;
    }
    localMapData.ConsumeFatigue = 寻路_获取走法(localMapData.MapChannel, localMapData.Width, localMapData.Height,
                                                localMapData.StartZb,
                                                localMapData.EndZb, localMapData.MapRoute);
    return localMapData;
}

DWORD 寻路_获取走法(vector<DWORD> paramMapChannel, DWORD paramWidth, DWORD paramHeight, CoordinateType paramMapStart,
                    CoordinateType paramMapEnd,
                    vector<CoordinateType> &paramRealRoute) {
    CoordinateType start_coordinate = {};
    CoordinateType end_coordinate = {};
    vector<vector<GameMapType>> map_flag;
    vector<vector<GameMapType>> map_array;
    vector<CoordinateType> cross_way;

    if (paramMapStart.X == paramMapEnd.X && paramMapStart.Y == paramMapEnd.Y) {
        paramRealRoute.clear();
        paramRealRoute.resize(0);
        return 0;
    }
    寻路_生成地图(paramWidth, paramHeight, paramMapChannel, map_array);
    寻路_显示地图(map_array, paramWidth, paramHeight, map_flag);
    start_coordinate.X = paramMapStart.X * 3 - 2;
    start_coordinate.Y = paramMapStart.Y * 3 - 2;
    end_coordinate.X = paramMapEnd.X * 3 - 2;
    end_coordinate.Y = paramMapEnd.Y * 3 - 2;
    寻路_路径算法(map_flag, start_coordinate, end_coordinate, paramWidth * 3, paramHeight * 3, cross_way);
    return 寻路_整理坐标(cross_way, paramRealRoute);

}

VOID 寻路_生成地图(DWORD paramWidth, DWORD paramHeight, vector<DWORD> paramMapChannel,
                   vector<vector<GameMapType>> &paramGameMap) {
    paramGameMap.clear();
    paramGameMap.resize(paramWidth);
    for (DWORD x = 0; x < paramWidth; x++) {
        paramGameMap[x].resize(paramHeight);
    }
    int i = 0;
    for (DWORD y = 0; y < paramHeight; y++) {
        for (DWORD x = 0; x < paramWidth; x++) {
            paramGameMap[x][y].MapCoordinates.X = x;
            paramGameMap[x][y].MapCoordinates.Y = y;
            paramGameMap[x][y].MapChannel = paramMapChannel[i];
            paramGameMap[x][y].Left = 寻路_判断方向(paramMapChannel[i], 0);
            paramGameMap[x][y].Right = 寻路_判断方向(paramMapChannel[i], 1);
            paramGameMap[x][y].Up = 寻路_判断方向(paramMapChannel[i], 2);
            paramGameMap[x][y].Down = 寻路_判断方向(paramMapChannel[i], 3);
            paramGameMap[x][y].BackgroundColor = 0xFFFFFF;
            i++;
            if (paramGameMap[x][y].MapChannel == 0)
                paramGameMap[x][y].BackgroundColor = 0x000000;
        }
    }
}

VOID 寻路_显示地图(vector<vector<GameMapType>> paramMapArray, DWORD paramWidth, DWORD paramHeight,
                   vector<vector<GameMapType>> &paramMapLabel) {
    paramMapLabel.clear();
    paramMapLabel.resize(paramWidth * (DWORD64)3);
    for (DWORD x = 0; x < paramWidth * 3; x++) {
        paramMapLabel[x].resize(paramHeight * 3);
    }
    for (DWORD y = 0; y < paramHeight; y++) {
        for (DWORD x = 0; x < paramWidth; x++) {
            paramMapLabel[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)2][(y + (DWORD64)1) * (DWORD64)3 -
                                                                      (DWORD64)2].BackgroundColor = 0xFFFFFF;
            if (paramMapArray[x][y].Left)
                paramMapLabel[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)3][(y + (DWORD64)1) * (DWORD64)3 -
                                                                          (DWORD64)2].BackgroundColor = 0xFFFFFF;
            if (paramMapArray[x][y].Right)
                paramMapLabel[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)1][(y + (DWORD64)1) * (DWORD64)3 -
                                                                          (DWORD64)2].BackgroundColor = 0xFFFFFF;
            if (paramMapArray[x][y].Up)
                paramMapLabel[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)2][(y + (DWORD64)1) * (DWORD64)3 -
                                                                          (DWORD64)3].BackgroundColor = 0xFFFFFF;
            if (paramMapArray[x][y].Down)
                paramMapLabel[(x + (DWORD64)1) * (DWORD64)3 - (DWORD64)2][(y + (DWORD64)1) * (DWORD64)3 -
                                                                          (DWORD64)1].BackgroundColor = 0xFFFFFF;
        }
    }
}

VOID 寻路_路径算法(vector<vector<GameMapType>> paramMapLabel, CoordinateType paramMapStart, CoordinateType paramMapEnd,
                   INT paramWidth, INT paramHeight,
                   vector<CoordinateType> &paramRouteArray) {
    BOOL 已存在开放列表, 已存在关闭列表;
    CoordinateType 待检测坐标;
    MapNodeType 待检测节点, 临时节点;
    vector<MapNodeType> 开放列表, 关闭列表;
    DWORD 最短编号 = 0;
    DWORD 最小F值, 预测G值;
    DWORD x, y;

    临时节点.CurrentCoordinates.X = paramMapStart.X;
    临时节点.CurrentCoordinates.Y = paramMapStart.Y;
    paramMapLabel[paramMapStart.X][paramMapStart.Y].BackgroundColor = 0x00FF00;
    paramMapLabel[paramMapEnd.X][paramMapEnd.Y].BackgroundColor = 0x0000FF;
    开放列表.insert(开放列表.begin(), 临时节点);
    do {
        最小F值 = 0;
        for (y = 0; y < 开放列表.size(); y++) {
            if (最小F值 == 0) {
                最小F值 = 开放列表[0].F;
                最短编号 = y;
            }
            if (开放列表[y].F < 最小F值) {
                最小F值 = 开放列表[y].F;
                最短编号 = y;
            }
        }
        临时节点 = 开放列表[最短编号];
        开放列表.erase(开放列表.begin() + 最短编号);
        关闭列表.insert(关闭列表.begin(), 临时节点);
        if (临时节点.CurrentCoordinates.X != paramMapStart.X || 临时节点.CurrentCoordinates.Y != paramMapStart.Y) {
            if (临时节点.CurrentCoordinates.X != paramMapEnd.X || 临时节点.CurrentCoordinates.Y != paramMapEnd.Y) {
                paramMapLabel[临时节点.CurrentCoordinates.X][临时节点.CurrentCoordinates.Y].BackgroundColor = 0x0080FF;
            }
        }
        for (y = 0; y < 关闭列表.size(); y++) {
            if (关闭列表[y].CurrentCoordinates.X == paramMapEnd.X &&
                关闭列表[y].CurrentCoordinates.Y == paramMapEnd.Y) {
                待检测节点 = 关闭列表[y];
                do {
                    for (unsigned int x = 0; x < 关闭列表.size(); x++) {
                        if (关闭列表[x].CurrentCoordinates.X == 待检测节点.FinalCoordinates.X &&
                            关闭列表[x].CurrentCoordinates.Y == 待检测节点.FinalCoordinates.Y) {
                            待检测节点 = 关闭列表[x];
                            break;
                        }
                    }
                    if (待检测节点.CurrentCoordinates.X != paramMapStart.X ||
                        待检测节点.CurrentCoordinates.Y != paramMapStart.Y) {
                        paramMapLabel[待检测节点.CurrentCoordinates.X][待检测节点.CurrentCoordinates.Y].BackgroundColor = 0x00D8D8;
                        paramRouteArray.insert(paramRouteArray.begin(), 待检测节点.CurrentCoordinates);
                    }
                } while (待检测节点.CurrentCoordinates.X != paramMapStart.X ||
                         待检测节点.CurrentCoordinates.Y != paramMapStart.Y);
                paramRouteArray.insert(paramRouteArray.begin(), paramMapStart);
                paramRouteArray.insert(paramRouteArray.end(), paramMapEnd);
                return;
            }
        }
        for (y = 0; y < 4; y++) {
            if (y == 0) {
                待检测坐标.X = 临时节点.CurrentCoordinates.X;
                待检测坐标.Y = 临时节点.CurrentCoordinates.Y - 1;
            } else if (y == 1) {
                待检测坐标.X = 临时节点.CurrentCoordinates.X - 1;
                待检测坐标.Y = 临时节点.CurrentCoordinates.Y;
            } else if (y == 2) {
                待检测坐标.X = 临时节点.CurrentCoordinates.X + 1;
                待检测坐标.Y = 临时节点.CurrentCoordinates.Y;
            } else {
                待检测坐标.X = 临时节点.CurrentCoordinates.X;
                待检测坐标.Y = 临时节点.CurrentCoordinates.Y + 1;
            }
            if (待检测坐标.X<0 || 待检测坐标.X>(paramWidth - 1) || 待检测坐标.Y<0 || 待检测坐标.Y>(paramHeight - 1))
                continue;
            if (paramMapLabel[待检测坐标.X][待检测坐标.Y].BackgroundColor == 0x000000)
                continue;
            已存在关闭列表 = false;
            for (x = 0; x < 关闭列表.size(); x++) {
                if (关闭列表[x].CurrentCoordinates.X == 待检测坐标.X &&
                    关闭列表[x].CurrentCoordinates.Y == 待检测坐标.Y) {
                    已存在关闭列表 = true;
                    break;
                }
            }
            if (已存在关闭列表)
                continue;
            已存在开放列表 = false;
            for (x = 0; x < 开放列表.size(); x++) {
                if (开放列表[x].CurrentCoordinates.X == 待检测坐标.X &&
                    开放列表[x].CurrentCoordinates.Y == 待检测坐标.Y) {
                    if (待检测坐标.X != 临时节点.CurrentCoordinates.X || 待检测坐标.Y != 临时节点.CurrentCoordinates.Y)
                        预测G值 = 14;
                    else
                        预测G值 = 10;
                    if (临时节点.G + 预测G值 < 开放列表[x].G)
                        开放列表[x].FinalCoordinates = 临时节点.CurrentCoordinates;
                    已存在开放列表 = true;
                    break;
                }
            }
            if (已存在开放列表 == false) {
                if (待检测坐标.X == 临时节点.CurrentCoordinates.X || 待检测坐标.Y == 临时节点.CurrentCoordinates.Y)
                    预测G值 = 10;
                else
                    预测G值 = 14;
                待检测节点.G = 临时节点.G + 预测G值;
                待检测节点.H = (paramMapEnd.X - 待检测坐标.X) * 10 + (paramMapEnd.Y - 待检测坐标.Y) * 10;
                待检测节点.F = 待检测节点.G + 待检测节点.H;
                待检测节点.CurrentCoordinates = 待检测坐标;
                待检测节点.FinalCoordinates = 临时节点.CurrentCoordinates;
                开放列表.insert(开放列表.begin(), 待检测节点);
            }
        }
    } while (开放列表.size() != 0);
}


DWORD 寻路_整理坐标(vector<CoordinateType> paramSimulatedMoves, vector<CoordinateType> &paramRealRoute) {
    DWORD x, y;
    DWORD k = 0;
    CoordinateType tmpCoordinateType = {};
    for (size_t i = 0; i < paramSimulatedMoves.size(); i++) {
        x = (paramSimulatedMoves[i].X + 2) % 3;
        y = (paramSimulatedMoves[i].Y + 2) % 3;
        if (x == 0 && y == 0) {
            tmpCoordinateType.X = (paramSimulatedMoves[i].X + 2) / 3 - 1;
            tmpCoordinateType.Y = (paramSimulatedMoves[i].Y + 2) / 3 - 1;
            paramRealRoute.insert(paramRealRoute.begin() + k, tmpCoordinateType);
            k++;
        }
    }
    return (k);
}

BOOL 寻路_判断方向(DWORD paramChannelDirection, DWORD paramDirection) {
    unsigned char localDirectionArray[4];
    unsigned char localDirectionCollection[16][4] = {{0, 0, 0, 0},
                                                     {0, 1, 0, 0},
                                                     {0, 0, 1, 0},
                                                     {0, 1, 1, 0},
                                                     {1, 0, 0, 0},
                                                     {1, 1, 0, 0},
                                                     {1, 0, 1, 0},
                                                     {1, 1, 1, 0},
                                                     {0, 0, 0, 1},
                                                     {0, 1, 0, 1},
                                                     {0, 0, 1, 1},
                                                     {0, 1, 1, 1},
                                                     {1, 0, 0, 1},
                                                     {1, 1, 0, 1},
                                                     {1, 0, 1, 1},
                                                     {1, 1, 1, 1}};
    if (paramChannelDirection >= 0 && paramChannelDirection <= 15)
        for (int i = 0; i < 4; i++) {
            localDirectionArray[i] = localDirectionCollection[paramChannelDirection][i];
        }
    else
        for (int i = 0; i < 4; i++) {
            localDirectionArray[i] = 0;
        }
    if (localDirectionArray[paramDirection] == 1)
        return TRUE;
    else
        return FALSE;
}

DWORD 寻路_计算方向(CoordinateType paramCurrentRoom, CoordinateType paramNextRoom) {
    DWORD direction = 0;
    DWORD x, y;
    x = paramCurrentRoom.X - paramNextRoom.X;
    y = paramCurrentRoom.Y - paramNextRoom.Y;
    if (x == 0 && y == 0) {
        return 4;
    }

    if (x == 0) {
        if (y == 1) {
            direction = 2;
        } else {
            direction = 3;
        }
    } else if (y == 0) {
        if (x == 1) {
            direction = 0;
        } else {
            direction = 1;
        }
    }
    return direction;
}