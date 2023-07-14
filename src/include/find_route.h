//
// Created by Administrator on 2023/06/28.
//

MapDataType MapData();

DWORD getRoute(vector<DWORD> paramMapChannel, DWORD paramWidth, DWORD paramHeight, CoordinateType paramMapStart,
               CoordinateType paramMapEnd,
               vector<CoordinateType> &paramRealRoute);

VOID genMap(DWORD paramWidth, DWORD paramHeight, vector<DWORD> paramMapChannel,
            vector<vector<GameMapType>> &paramGameMap);

VOID displayMap(vector<vector<GameMapType>> paramMapArray, DWORD paramWidth, DWORD paramHeight,
                vector<vector<GameMapType>> &paramMapLabel);

VOID routeCalculate(vector<vector<GameMapType>> paramMapLabel, CoordinateType paramMapStart, CoordinateType paramMapEnd,
                    DWORD paramWidth, DWORD paramHeight,
                    vector<CoordinateType> &paramRouteArray);


DWORD tidyCoordinate(const vector<CoordinateType> &paramSimulatedMoves, vector<CoordinateType> &paramRealRoute);

BOOL judgeDirection(DWORD paramChannelDirection, DWORD paramDirection);

DWORD GetDirection(CoordinateType paramCurrentRoom, CoordinateType paramNextRoom);