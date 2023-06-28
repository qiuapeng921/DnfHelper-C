cmake_minimum_required(VERSION 3.25)
project(DnfHelper_C)

project(DnfHelper_C VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)

# 指定源文件和生成的库文件名称
add_library(DnfHelper_C SHARED
        main.cpp
        src/common/headers.h
        src/consts/struct.h
        src/game/address.h
        src/common/config.cpp src/common/config.h
        src/common/read_write.cpp src/common/read_write.h
        src/helpers/string.cpp src/helpers/string.h
        src/helpers/time.cpp src/helpers/time.h
        src/helpers/logger.cpp src/helpers/logger.h
        src/game/activation.cpp src/game/activation.h
        src/game/call.cpp src/game/call.h
        src/game/notice.cpp src/game/notice.h
        src/game/auto.cpp src/game/auto.h
        src/game/other.cpp src/game/other.h
        src/game/send.cpp src/game/send.h
        src/game/task.cpp src/game/task.h
        src/game/func.cpp src/game/func.h
        src/game/find_route.cpp src/game/find_route.h
        src/game/map_data.cpp src/game/map_data.h
        versioninfo.rc)

# 移除库文件名称的前缀 "lib"
set_target_properties(DnfHelper_C PROPERTIES PREFIX "")
# 设置库文件的输出名称为"version"
set_target_properties(DnfHelper_C PROPERTIES OUTPUT_NAME "cscapi")


configure_file(
        versioninfo.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/versioninfo.rc
        COPYONLY
)