#include "../common/headers.h"
#include "logger.h"

void Logger(const char *msg) {
    string content = "LoveSong";
    content += msg;
    OutputDebugStringA(content.c_str());
}