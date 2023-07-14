//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "automatic.h"
#include "notice.h"
#include "map_data.h"
#include "helper.h"
#include "read_write.h"

void automatic::SwitchFunc() {
    autoSwitch = !autoSwitch;
    autoSwitch = !autoSwitch;
    if (autoSwitch) {
        SetTimer(nullptr, 1000, 200, (TIMERPROC)AutoThread);
        ColorfulNotice(L"自动刷图 - 启动", 2);
        return;
    }
    KillTimer(nullptr, 1000);
    ColorfulNotice(L"自动刷图 - 关闭", 2);
}

void automatic::StartFunc() {

}

void automatic::AutoThread() {
    static bool firstMap = false;

    // 进入城镇
    if (mapData::GetGameStat() == 0) {
        Sleep(200);
        //进入城镇();
        return;
    }

    // 城镇处理
    if (mapData::GetGameStat() == 1 && mapData::IsTown()) {
        //城镇处理();
        return;
    }

    // 进入副本
    if (mapData::GetGameStat() == 2) {
        //进入副本(全局_自动.副本编号);
        return;
    }

    // 在地图内
    if (mapData::GetGameStat() == 3) {
        Sleep(2000);
        if (!firstMap && !mapData::IsTown()) {
            const wchar_t *mapName = helper::FormatString(L"进入副本 [ %s ]", mapData::GetMapName().c_str());
            ColorfulNotice(mapName, 1);
            // 透明Call(读整数型(取人物基质()));
            Sleep(100);
            // WriteLong(ReadLong(评分基址) + 评分偏移, 999999);
            Sleep(100);
            // 开启功能
            StartFunc();
            firstMap = true;
        }


        // 跟随怪物
        // FollowMonster()

        // 过图
        if (mapData::IsOpenTheDoor() && !mapData::IsBossRoom()) {
            Sleep(300);
            PassMap();
            return;
        }

        // 通关
        if (mapData::IsBossRoom()) {
            if (mapData::IsPassBoss()) {
                // 捡物
                // PackPickup()

                // 关闭功能
                // startFunc()

                Sleep(300);
                QuitMap();
                firstMap = false;
            }
        }
    }
}

void automatic::EnterTown() {

}

void automatic::TownHandle() {

}

void automatic::EnterSelectMap() {

}

void automatic::BackToRole() {

}

void automatic::EnterMap() {

}

void automatic::PassMap() {

}

void automatic::QuitMap() {

}
