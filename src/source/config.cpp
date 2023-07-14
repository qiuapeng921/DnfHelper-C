//
// Created by Administrator on 2023/06/28.
//

#include "config.h"
#include "helper.h"

wstring HelperName = L"DnfHelper";


void WriteConfigData(const wstring &itemName, const wstring &data) {
    wstring filePath = helper::GetDesktopPath() + L"\\" + HelperName + L".ini";
    WritePrivateProfileStringW(L"配置", itemName.c_str(), data.c_str(), filePath.c_str());
}

UINT ReadConfigData(const wstring &itemName) {
    wstring filePath = helper::GetDesktopPath() + L"\\" + HelperName + L".ini";
    return GetPrivateProfileIntW(L"配置", itemName.c_str(), 0, filePath.c_str());
}

// 加载配置文件
void LoadConfigIni() {

}

// 配置文件是否存在
bool ConfigIniExist() {
    // 获取桌面路径
    wstring desktopPath = helper::GetDesktopPath();

    if (!desktopPath.empty()) {
        // 构建 ini 文件路径
        wstring iniPath = desktopPath + L"\\" + HelperName + L".ini";

        // 尝试打开 ini 文件
        ifstream file(iniPath);

        // 检查文件是否成功打开
        if (file.good()) {
            file.close();
            return true;
        }
    }

    return false;
}

// 写出配置文件
void WriteConfigIni() {
    WriteConfigData(L"技能代码", L"15442");
    WriteConfigData(L"技能伤害", L"85000000");
    WriteConfigData(L"技能频率", L"300");
    WriteConfigData(L"技能个数", L"2");
    WriteConfigData(L"技能大小", L"5\n");

    WriteConfigData(L"自动模式", L"2		={1}指定地图 ={2}剧情升级");
    WriteConfigData(L"副本编号", L"100000002");
    WriteConfigData(L"副本难度", L"5		={0}普通级 ={1}冒险级 ={2}勇士级 ={3}王者级 ={4}噩梦级 ={5}取最高\n");

    WriteConfigData(L"预留疲劳", L"0");

    WriteConfigData(L"跟随方式", L"1		={0}不执行 ={1}坐标跟随 ={2}漂移跟随");
    WriteConfigData(L"拾取方式", L"3		={0}不执行 ={1}按键入包 ={2}落地入包 ={3}空中入包");
    WriteConfigData(L"顺图方式", L"2		={0}不执行 ={1}坐标顺图 ={2}漂移顺图 ={3}强制顺图\n");
}
