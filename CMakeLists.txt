# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (GeometricCorrection)

find_package(OpenCV  REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(./include)

# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./src DIR_SRCS)

# 指定生成目标
add_executable(run ${DIR_SRCS})

target_link_libraries(run ${OpenCV_LIBRARIES})