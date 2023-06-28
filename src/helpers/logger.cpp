#include "../common/headers.h"
#include "logger.h"
#include <iostream>

#include <fstream>
#include <cstdlib>

void OutputDebug(const char *msg) {
    string content = "LoveSong";
    content += msg;
    OutputDebugStringA(content.c_str());
}


void WriteLog(const char *msg) {
    // 获取桌面目录的路径
    const char *desktopPath = std::getenv("USERPROFILE");

    if (desktopPath != nullptr) {
        // 构建日志文件路径
        string logFilePath = string(desktopPath) + "\\dll-debug.log";

        // 打开日志文件，以追加模式写入
        ofstream logfile(logFilePath, ios::app);

        if (logfile.is_open()) { // 检查文件是否成功打开
            logfile << msg << std::endl; // 写入日志文件
            logfile.close(); // 关闭文件
        } else {
            OutputDebug("无法打开日志文件");
        }
    } else {
        OutputDebug("无法获取桌面目录路径");
    }
}