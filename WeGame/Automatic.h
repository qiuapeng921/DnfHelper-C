#pragma once

using namespace std;

class Automatic
{
protected:
	// 自动开关
	bool automaticSwitch;

public:
	VOID AutomaticSwitch();
	VOID AutomaticThread();
	VOID 进入城镇();
	VOID 城镇处理();
	VOID 进入选图();
	VOID 返回角色();
	VOID 进入副本();
	VOID 模拟顺图();
	VOID 退出副本();
};

extern Automatic automatic;
