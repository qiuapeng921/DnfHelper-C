#pragma once
#include "公用.h"
using namespace std;

void 汇编执行(vector<BYTE> 汇编代码);

void 技能Call(INT64 触发指针, int 技能代码, int 技能伤害, int x, int y, int z, float 大小);

void  透明Call(INT64 对象指针);

INT64 取人物指针Call(INT64 空白地址);

INT64 取人物基质();

void 区域Call(int 地图编号);

void 坐标Call(int 对象横轴, int 对象纵轴, int 对象竖轴);

void 漂移Call(int X, int Y, int Z, int 速度);