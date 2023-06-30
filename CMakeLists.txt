cmake_minimum_required(VERSION 3.25)
project(DnfHelper)

project(DnfHelper VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)

file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/src/include/*.h)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/source/*.cpp)

# 链接头文件路径
include_directories(DnfHelper PRIVATE ${PROJECT_SOURCE_DIR}/src/include)

# 指定源文件和生成的库文件名称
add_library(DnfHelper SHARED main.cpp ${HEADER_FILES} ${SOURCE_FILES})


# 移除库文件名称的前缀 "lib"
set_target_properties(DnfHelper PROPERTIES PREFIX "")
# 设置库文件的输出名称为"version"
set_target_properties(DnfHelper PROPERTIES OUTPUT_NAME "TPHelperBase")

# 设置构建类型 Debug Release
set(CMAKE_BUILD_TYPE Release)