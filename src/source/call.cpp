//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "call.h"
#include "address.h"
#include "read_write.h"

ULONG64 Func_CALL(ULONG64 ADDR_,
                  ULONG64 RCX_,
                  ULONG64 RDX_,
                  ULONG64 R8_,
                  ULONG64 R9_,
                  ULONG64 R10_,
                  ULONG64 R11_,
                  ULONG64 R12_,
                  ULONG64 R13_,
                  ULONG64 R14_,
                  ULONG64 R15_) {
    auto MyFastCall = (_Func_Call)ADDR_;

    return MyFastCall(RCX_,
                      RDX_,
                      R8_,
                      R9_,
                      R10_,
                      R11_,
                      R12_,
                      R13_,
                      R14_,
                      R15_);
}

// 取人物指针Call
ULONG64 GetPerPtrCall() {
    return Func_CALL(人物CALL);
}

void BufferCall(ULONG64 packHeader) {
    Func_CALL(缓冲CALL, 发包基址, packHeader);
}

void EncryptCall(ULONG64 packHeader, int len) {
    ULONG64 packParam = 0;
    if (len == 1) { packParam = 加密CALL_1; }
    if (len == 2) { packParam = 加密CALL_2; }
    if (len == 4) { packParam = 加密CALL_3; }
    if (len == 8) { packParam = 加密CALL_4; }
    Func_CALL(packParam, 发包基址, packHeader);
}

void SendCall() {
    Func_CALL(发包CALL);
}


VOID RefreshCall(ULONG64 addr) {
    Func_CALL(刷新CALL, addr, 0);
}


// 地图CALL
ULONG64 MapCall(int mapId) {
    return Func_CALL(地图CALL, mapId);
}

// 标识Call
ULONG64 MarkCall() {
    return Func_CALL(标识CALL);
}

// 技能CALL
void SkillCall(ULONG64 pointer, int code, int harm, int x, int y, int z, float size) {
    ULONG64 array[100] = {0};
    *(ULONG64 *)(ULONG64)array = pointer;
    *(ULONG *)((ULONG64)array + 16) = code;
    *(ULONG *)((ULONG64)array + 20) = harm;
    *(ULONG *)((ULONG64)array + 32) = x;
    *(ULONG *)((ULONG64)array + 36) = y;
    *(ULONG *)((ULONG64)array + 40) = z;
    *(float *)((ULONG64)array + 140) = size;
    *(float *)((ULONG64)array + 144) = 65535;
    *(float *)((ULONG64)array + 148) = 65535;
    Func_CALL(技能CALL, (ULONG64)array, MarkCall());
}

// 坐标CALL
void CoordinateCall(uint64_t pointer, uint32_t X, uint32_t Y, uint32_t Z) {
    Func_CALL(坐标CALL, pointer, X, Y, Z);
}

void 过图Call(int direction) {
    ULONG64 emptyAddr[200] = {0};
    ULONG64 param = ReadLong(ReadLong(ReadLong(房间编号) + 时间基址) + 顺图偏移);
    Func_CALL(过图CALL, param, direction, (ULONG64)emptyAddr, 0xFFFFFFFF);
}

void 整理背包Call(ULONG64 addr, int backpackType) {
    int goodsType = 1;
    if (backpackType == 1) { goodsType = 1; }
    if (backpackType == 11) { goodsType = 20; }
    if (backpackType == 12) { goodsType = 21; }
    Func_CALL(整理CALL, ReadLong(addr), goodsType, backpackType);
}

void SelectMap() {
    Func_CALL(选图CALL, ReadLong(角色指针));
}

void 进图Call(ULONG64 mapId, ULONG64 mapLevel, ULONG64 taskId, ULONG64 深渊模式) {
    if (taskId > 0) {
        Func_CALL(进图CALL, ReadLong(角色指针), taskId, 0, 0, 0, 0xFFFFFFFF);
    } else {
        Func_CALL(进图CALL, ReadLong(角色指针), mapId, mapLevel, 深渊模式, 0, 0xFFFFFFFF);
    }
}

void 回城Call(int param) {
    Func_CALL(回城CALL, ReadLong(回城参数), param, 1, 1);
}

void 物品Call(__int64 触发地址, __int32 物品编号) {
    Func_CALL(*(__int64 *)(*(__int64 *)触发地址 + 物品CALL), 触发地址, 物品编号);
}

//0=个人信息   1=物品栏   2=任务手册   3=技能栏   4=副职业   5=冒险团 6=心情状态 7=伙伴 8=队伍信息 9=社交 10=邮件 11决斗场
//13=拍卖行  14=金币寄售 15=游戏指南 16=百科词典 17=视频录制 19=游戏设置 20=键盘设置 22=返回角色界面 23=频道选择 24=回城
//26=武器租聘 27=活动日历 29=结束游戏 31=团队频道 32=寻找攻坚队 33=客服专区 36=重播 37=交流论坛 38=史诗图签 39=工会 40=收集箱
//42=无尽难度信息 45=移动再战魔界频道 46=攻坚商店 47=装备指南 48=皮肤仓库 49=最小化游戏 51=人物词典 52=切换普通大区 59=侠客行
//60=呼唤朋友 61=频道移动
VOID 界面Call(int 参数) {
    Func_CALL(界面CALL, *(ULONG64 *)界面基址, 参数);
}

void 跳过Call() {
    Func_CALL(跳过CALL, *(ULONG64 *)任务基址, 1, -1);
}

void 进入角色Call(int 角色位置) {
    Func_CALL(选择角色CALL, *(ULONG64 *)(*(ULONG64 *)角色基址 + 角色初始指针), 角色位置, 0, 0);
}

void 退出角色Call() {
    Func_CALL(返回角色CALL);
}

void 放弃Call(int 任务编号) {
    Func_CALL(放弃CALL, *(ULONG64 *)任务基址, 任务编号);
}

void 提交Call(int 任务编号) {
    Func_CALL(提交CALL_1, *(ULONG64 *)任务基址, 任务编号, 0xFFFFFFFF, 1);
}

void 接受Call(int 任务编号) {
    Func_CALL(接受CALL_1, *(ULONG64 *)任务基址, 任务编号);
}

void 完成Call(int 任务编号, int 任务次数) {
    if (任务次数 == NULL) {
        任务次数 = 1;
    }
    for (size_t i = 0; i < 任务次数; ++i) {
        Func_CALL(完成CALL, *(ULONG64 *)任务基址, 任务编号, 0xFF, 0xFF);
    }
}


void 漂移Call(ULONG64 怪物指针, int X, int Y, int Z, int 移动速度) {
    if (X <= 0 || Y <= 0) {
        return;
    }
    ULONG64 对象指针 = 怪物指针;// 全局_收包数据.参_人物指针;
    ULONG64 空白地址 = AllocMem(512);
    ULONG64 rsi = Func_CALL(申请内存CALL, 0xF1);
    ULONG64 rdi = Func_CALL(漂移CALL_1, rsi);
    *(ULONG *)(rdi + 0) = X;
    *(ULONG *)(rdi + 4) = Y;
    *(ULONG *)(rdi + 8) = Z;
    ULONG64 rcx = rdi + 0x18;
    *(ULONG *)(rcx + 0) = 移动速度;
    *(ULONG *)(rcx + 4) = 移动速度;
    *(ULONG *)(rcx + 8) = 移动速度;
    Func_CALL(写入内存CALL, (ULONG64)空白地址, 0);
    Func_CALL(移动CALL, rsi, 对象指针, 对象指针, 0, (ULONG64)空白地址, 0, 0xFFFFFFFF);
}

VOID 奔跑Call(int x, int y, int z, int 速度) {
    ULONG64 参_人物指针 = GetPerPtrCall();
    __int64 空白地址[50] = {0}, 空白地址1[50] = {0};
    __int64 rbx = Func_CALL(*(__int64 *)(*(__int64 *)(参_人物指针) + 奔跑偏移_1), 参_人物指针, (__int64)空白地址);
    __int64 rax = Func_CALL(*(__int64 *)(*(__int64 *)(参_人物指针) + 奔跑偏移_2), 参_人物指针, (__int64)空白地址1);
    Func_CALL(奔跑CALL, 参_人物指针, 参_人物指针, rax, rbx, z, 速度, x, y);
}

VOID 城镇移动Call(int 城镇区域, int 城镇编号, int 城镇横轴, int 城镇纵轴) {
    ULONG64 触发指针 = ReadLong(角色指针);
    ULONG64 城镇指针 = 城镇基址;
    WriteInt(城镇指针, 城镇区域);
    WriteInt(城镇指针 + 4, 城镇编号);
    WriteInt(城镇指针 + 8, 城镇横轴);
    WriteInt(城镇指针 + 12, 城镇纵轴);
    Func_CALL(城镇CALL, 触发指针, 城镇指针);
}

void 区域Call(int 副本) {
    int 大区域, 小区域, X, Y;
    大区域 = *(int *)(*(ULONG64 *)(区域基址) + 区域偏移);
    小区域 = *(int *)(*(ULONG64 *)(区域基址) + 区域偏移 + 4);
    X = *(int *)(*(ULONG64 *)(区域基址) + 区域偏移 + 8);
    Y = *(int *)(*(ULONG64 *)(区域基址) + 区域偏移 + 12);
    城镇移动Call(大区域, 小区域, X, Y);
}
