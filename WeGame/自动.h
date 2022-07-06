#pragma once

using namespace std;

class 自动
{
protected:
	// 自动开关
	bool automaticSwitch;

public:
	VOID 自动开关();
	VOID 自动线程();
	VOID 进入城镇();
	VOID 城镇处理();
	VOID 进入选图();
	VOID 返回角色();
	VOID 进入副本();
	VOID 模拟顺图();
	VOID 退出副本();
};

extern 自动 automatic;
