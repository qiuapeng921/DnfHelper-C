#pragma once

#include "headers.h"

// 写配置数据
void WriteConfigData(string item, string data);

// 读配置数据
int ReadConfigData(string item);

// 加载配置文件
void LoadConfigIni();

// 配置文件是否存在
bool ConfigIniExist();

// 写出配置文件
void WriteConfigIni();