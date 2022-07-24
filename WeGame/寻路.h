#pragma once
#include "结构.h"

// 游戏地图

地图数据 寻路_地图数据();

DWORD 寻路_获取走法(vector<DWORD> 参_地图通道, DWORD 参_宽度, DWORD 参_高度, 坐标型 参_地图起点, 坐标型 参_地图终点, vector<坐标型>& 参_真实走法);

VOID 寻路_生成地图(DWORD 参_宽度, DWORD 参_高度, vector<DWORD> 参_地图通道, vector<vector<游戏地图>>& 参_游戏地图);

VOID 寻路_显示地图(vector<vector<游戏地图>> 参_地图数组, DWORD 参_宽度, DWORD 参_高度, vector<vector<游戏地图>>& 参_地图标签);

VOID 寻路_路径算法(vector<vector<游戏地图>> 参_地图标签, 坐标型 参_地图起点, 坐标型 参_地图终点, DWORD 参_宽度, DWORD 参_高度, vector<坐标型>& 参_走法数组);

DWORD 寻路_整理坐标(vector<坐标型> 参_模拟走法, vector<坐标型>& 参_真实走法);

BOOL  寻路_判断方向(DWORD 参_通向, DWORD 参_方向);

DWORD 寻路_计算方向(坐标型 参_当前房间, 坐标型 参_下个房间);

VOID 坐标_顺图(int 顺图方向);

VOID 组包_顺图(int 方向ID);