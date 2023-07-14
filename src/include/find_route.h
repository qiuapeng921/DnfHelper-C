//
// Created by Administrator on 2023/06/28.
//

MapDataType 寻路_地图数据();

DWORD 寻路_获取走法(vector<DWORD> paramMapChannel, DWORD paramWidth, DWORD paramHeight, CoordinateType paramMapStart,
                    CoordinateType paramMapEnd,
                    vector<CoordinateType> &paramRealRoute);

VOID 寻路_生成地图(DWORD paramWidth, DWORD paramHeight, vector<DWORD> paramMapChannel,
                   vector<vector<GameMapType>> &paramGameMap);

VOID 寻路_显示地图(vector<vector<GameMapType>> paramMapArray, DWORD paramWidth, DWORD paramHeight,
                   vector<vector<GameMapType>> &paramMapLabel);

VOID 寻路_路径算法(vector<vector<GameMapType>> paramMapLabel, CoordinateType paramMapStart, CoordinateType paramMapEnd,
                   INT paramWidth, INT paramHeight,
                   vector<CoordinateType> &paramRouteArray);

DWORD 寻路_整理坐标(vector<CoordinateType> paramSimulatedMoves, vector<CoordinateType> &paramRealRoute);

BOOL 寻路_判断方向(DWORD paramChannelDirection, DWORD paramDirection);

DWORD 寻路_计算方向(CoordinateType paramCurrentRoom, CoordinateType paramNextRoom);