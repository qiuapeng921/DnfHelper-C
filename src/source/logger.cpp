//
// Created by Administrator on 2023/06/28.
//

#include "headers.h"
#include "logger.h"

void OutputDebug(const char *msg) {
    string content = "LoveSong";
    content += msg;
    OutputDebugStringA(content.c_str());
}


void WriteLog(const char *msg) {
    // 获取用户目录的路径
    const char *userProfilePath = getenv("USERPROFILE");

    if (userProfilePath != nullptr) {
        // 构建桌面路径
        string desktopPath = string(userProfilePath) + "\\Desktop";

        // 构建日志文件路径
        string logFilePath = desktopPath + "\\dll-debug.log";

        // 打开日志文件，以追加模式写入
        ofstream logfile(logFilePath, ios::app);

        if (logfile.is_open()) { // 检查文件是否成功打开
            logfile << msg << endl; // 写入日志文件
            logfile.close(); // 关闭文件
        } else {
            OutputDebug("无法打开日志文件");
        }
    } else {
        OutputDebug("无法获取桌面目录路径");
    }
}