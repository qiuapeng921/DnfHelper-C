cmake_minimum_required(VERSION 3.25)
project(DnfHelper_C)

set(CMAKE_CXX_STANDARD 14)

add_library(DnfHelper_C SHARED
        main.cpp
        src/common/headers.h
        src/consts/struct.h
        src/game/address.h
        src/common/config.cpp src/common/config.h
        src/common/read_write.cpp src/common/read_write.h
        src/game/activation.cpp src/game/activation.h
        src/game/call.cpp src/game/call.h
        src/game/notice.cpp src/game/notice.h
        src/game/auto.cpp src/game/auto.h
        src/game/other.cpp src/game/other.h
        src/game/send.cpp src/game/send.h
        src/game/task.cpp src/game/task.h
        src/game/func.cpp src/game/func.h
        src/helpers/string.cpp src/helpers/string.h
        src/helpers/time.cpp src/helpers/time.h
        src/helpers/logger.cpp src/helpers/logger.h)