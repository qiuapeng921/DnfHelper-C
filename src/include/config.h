#pragma once

#include "headers.h"

void WriteConfigData(string item, string data);

int ReadConfigData(string item);

// 加载配置文件
void LoadConfigIni();

// 配置文件是否存在
bool ConfigIniExist();

// 写出配置文件
void WriteConfigIni();