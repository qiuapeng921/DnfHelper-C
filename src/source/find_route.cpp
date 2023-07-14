//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "struct.h"
#include "read_write.h"
#include "map_data.h"
#include "address.h"

#include "find_route.h"

MapDataType MapData() {
    MapDataType localMapData;
    ULONG64 localRoomData = ReadLong(ReadLong(ReadLong(房间编号) + 时间基址) + 门型偏移);
    ULONG64 localRoomIndex = mapData::Decode(localRoomData + 索引偏移);

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
    localMapData.ConsumeFatigue = getRoute(localMapData.MapChannel, localMapData.Width, localMapData.Height,
                                           localMapData.StartZb,
                                           localMapData.EndZb, localMapData.MapRoute);
    return localMapData;
}

DWORD getRoute(vector<DWORD> paramMapChannel, DWORD paramWidth, DWORD paramHeight, CoordinateType paramMapStart,
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
    genMap(paramWidth, paramHeight, paramMapChannel, map_array);
    displayMap(map_array, paramWidth, paramHeight, map_flag);
    start_coordinate.X = paramMapStart.X * 3 - 2;
    start_coordinate.Y = paramMapStart.Y * 3 - 2;
    end_coordinate.X = paramMapEnd.X * 3 - 2;
    end_coordinate.Y = paramMapEnd.Y * 3 - 2;
    routeCalculate(map_flag, start_coordinate, end_coordinate, paramWidth * 3, paramHeight * 3, cross_way);
    return tidyCoordinate(cross_way, paramRealRoute);

}

VOID genMap(DWORD paramWidth, DWORD paramHeight, vector<DWORD> paramMapChannel,
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
            paramGameMap[x][y].Left = judgeDirection(paramMapChannel[i], 0);
            paramGameMap[x][y].Right = judgeDirection(paramMapChannel[i], 1);
            paramGameMap[x][y].Up = judgeDirection(paramMapChannel[i], 2);
            paramGameMap[x][y].Down = judgeDirection(paramMapChannel[i], 3);
            paramGameMap[x][y].BackgroundColor = 0xFFFFFF;
            i++;
            if (paramGameMap[x][y].MapChannel == 0)
                paramGameMap[x][y].BackgroundColor = 0x000000;
        }
    }
}

VOID displayMap(vector<vector<GameMapType>> paramMapArray, DWORD paramWidth, DWORD paramHeight,
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

VOID routeCalculate(vector<vector<GameMapType>> paramMapLabel, CoordinateType paramMapStart, CoordinateType paramMapEnd,
                    DWORD paramWidth, DWORD paramHeight,
                    vector<CoordinateType> &paramRouteArray) {
    BOOL existOpenList, existCloseList;
    CoordinateType waitHandleCoordinate = {};
    MapNodeType waitHandleNode = {};
    MapNodeType tmpNode = {};
    vector<MapNodeType> openList, closeList;
    DWORD shortEstNum = 0;
    DWORD minF, guessG;

    tmpNode.CurrentCoordinates.X = paramMapStart.X;
    tmpNode.CurrentCoordinates.Y = paramMapStart.Y;
    paramMapLabel[paramMapStart.X][paramMapStart.Y].BackgroundColor = 0x00FF00;
    paramMapLabel[paramMapEnd.X][paramMapEnd.Y].BackgroundColor = 0x0000FF;
    openList.insert(openList.begin(), tmpNode);
    do {
        minF = 0;
        for (unsigned int y = 0; y < openList.size(); y++) {
            if (minF == 0) {
                minF = openList[0].F;
                shortEstNum = y;
            }
            if (openList[y].F < minF) {
                minF = openList[y].F;
                shortEstNum = y;
            }
        }
        tmpNode = openList[shortEstNum];
        openList.erase(openList.begin() + shortEstNum);
        closeList.insert(closeList.begin(), tmpNode);
        if (tmpNode.CurrentCoordinates.X != paramMapStart.X || tmpNode.CurrentCoordinates.Y != paramMapStart.Y) {
            if (tmpNode.CurrentCoordinates.X != paramMapEnd.X || tmpNode.CurrentCoordinates.Y != paramMapEnd.Y) {
                paramMapLabel[tmpNode.CurrentCoordinates.X][tmpNode.CurrentCoordinates.Y].BackgroundColor = 0x0080FF;
            }
        }
        for (unsigned int y = 0; y < closeList.size(); y++) {
            if (closeList[y].CurrentCoordinates.X == paramMapEnd.X &&
                closeList[y].CurrentCoordinates.Y == paramMapEnd.Y) {
                waitHandleNode = closeList[y];
                do {
                    for (auto &x: closeList) {
                        if (x.CurrentCoordinates.X == waitHandleNode.FinalCoordinates.X &&
                            x.CurrentCoordinates.Y == waitHandleNode.FinalCoordinates.Y) {
                            waitHandleNode = x;
                            break;
                        }
                    }
                    if (waitHandleNode.CurrentCoordinates.X != paramMapStart.X ||
                        waitHandleNode.CurrentCoordinates.Y != paramMapStart.Y) {
                        paramMapLabel[waitHandleNode.CurrentCoordinates.X][waitHandleNode.CurrentCoordinates.Y].BackgroundColor = 0x00D8D8;
                        paramRouteArray.insert(paramRouteArray.begin(), waitHandleNode.CurrentCoordinates);
                    }
                } while (waitHandleNode.CurrentCoordinates.X != paramMapStart.X ||
                         waitHandleNode.CurrentCoordinates.Y != paramMapStart.Y);
                paramRouteArray.insert(paramRouteArray.begin(), paramMapStart);
                paramRouteArray.insert(paramRouteArray.end(), paramMapEnd);
                return;
            }
        }
        for (unsigned int y = 0; y < 4; y++) {
            if (y == 0) {
                waitHandleCoordinate.X = tmpNode.CurrentCoordinates.X;
                waitHandleCoordinate.Y = tmpNode.CurrentCoordinates.Y - 1;
            } else if (y == 1) {
                waitHandleCoordinate.X = tmpNode.CurrentCoordinates.X - 1;
                waitHandleCoordinate.Y = tmpNode.CurrentCoordinates.Y;
            } else if (y == 2) {
                waitHandleCoordinate.X = tmpNode.CurrentCoordinates.X + 1;
                waitHandleCoordinate.Y = tmpNode.CurrentCoordinates.Y;
            } else {
                waitHandleCoordinate.X = tmpNode.CurrentCoordinates.X;
                waitHandleCoordinate.Y = tmpNode.CurrentCoordinates.Y + 1;
            }
            if (waitHandleCoordinate.X<0 || waitHandleCoordinate.X>(paramWidth - 1) ||
                waitHandleCoordinate.Y<0 || waitHandleCoordinate.Y>(paramHeight - 1))
                continue;
            if (paramMapLabel[waitHandleCoordinate.X][waitHandleCoordinate.Y].BackgroundColor == 0x000000)
                continue;
            existCloseList = false;
            for (auto &x: closeList) {
                if (x.CurrentCoordinates.X == waitHandleCoordinate.X &&
                    x.CurrentCoordinates.Y == waitHandleCoordinate.Y) {
                    existCloseList = true;
                    break;
                }
            }
            if (existCloseList)
                continue;
            existOpenList = false;
            for (auto &x: openList) {
                if (x.CurrentCoordinates.X == waitHandleCoordinate.X &&
                    x.CurrentCoordinates.Y == waitHandleCoordinate.Y) {
                    if (waitHandleCoordinate.X != tmpNode.CurrentCoordinates.X ||
                        waitHandleCoordinate.Y != tmpNode.CurrentCoordinates.Y)
                        guessG = 14;
                    else
                        guessG = 10;
                    if (tmpNode.G + guessG < x.G)
                        x.FinalCoordinates = tmpNode.CurrentCoordinates;
                    existOpenList = true;
                    break;
                }
            }
            if (existOpenList == false) {
                if (waitHandleCoordinate.X == tmpNode.CurrentCoordinates.X ||
                    waitHandleCoordinate.Y == tmpNode.CurrentCoordinates.Y)
                    guessG = 10;
                else
                    guessG = 14;
                waitHandleNode.G = tmpNode.G + guessG;
                waitHandleNode.H =
                        (paramMapEnd.X - waitHandleCoordinate.X) * 10 + (paramMapEnd.Y - waitHandleCoordinate.Y) * 10;
                waitHandleNode.F = waitHandleNode.G + waitHandleNode.H;
                waitHandleNode.CurrentCoordinates = waitHandleCoordinate;
                waitHandleNode.FinalCoordinates = tmpNode.CurrentCoordinates;
                openList.insert(openList.begin(), waitHandleNode);
            }
        }
    } while (!openList.empty());
}


DWORD tidyCoordinate(const vector<CoordinateType> &paramSimulatedMoves, vector<CoordinateType> &paramRealRoute) {
    DWORD x, y;
    DWORD k = 0;
    CoordinateType tmpCoordinateType = {};
    for (auto &paramSimulatedMove: paramSimulatedMoves) {
        x = (paramSimulatedMove.X + 2) % 3;
        y = (paramSimulatedMove.Y + 2) % 3;
        if (x == 0 && y == 0) {
            tmpCoordinateType.X = (paramSimulatedMove.X + 2) / 3 - 1;
            tmpCoordinateType.Y = (paramSimulatedMove.Y + 2) / 3 - 1;
            paramRealRoute.insert(paramRealRoute.begin() + k, tmpCoordinateType);
            k++;
        }
    }
    return (k);
}

BOOL judgeDirection(DWORD paramChannelDirection, DWORD paramDirection) {
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
        for (unsigned char &i: localDirectionArray) {
            i = 0;
        }
    if (localDirectionArray[paramDirection] == 1)
        return TRUE;
    else
        return FALSE;
}

DWORD GetDirection(CoordinateType paramCurrentRoom, CoordinateType paramNextRoom) {
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