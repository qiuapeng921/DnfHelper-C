#pragma once
#include "DataType.h"

// 游戏地图

地图数据 寻路_地图数据();

int 寻路_获取走法(vector<int> 参_地图通道, int 参_宽度, int 参_高度, 坐标型 参_地图起点, 坐标型 参_地图终点, vector<坐标型>& 参_真实走法);

void 寻路_生成地图(int 参_宽度, int 参_高度, vector<int> 参_地图通道, vector<vector<游戏地图>>& 参_游戏地图);

void 寻路_显示地图(vector<vector<游戏地图>> 参_地图数组, int 参_宽度, int 参_高度, vector<vector<游戏地图>>& 参_地图标签);

void 寻路_路径算法(vector<vector<游戏地图>> 参_地图标签, 坐标型 参_地图起点, 坐标型 参_地图终点, int 参_宽度, int 参_高度, vector<坐标型>& 参_走法数组);

int 寻路_整理坐标(vector<坐标型> 参_模拟走法, vector<坐标型>& 参_真实走法);

bool  寻路_判断方向(int 参_通向, int 参_方向);

int 寻路_计算方向(坐标型 参_当前房间, 坐标型 参_下个房间);