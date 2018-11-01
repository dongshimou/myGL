# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("openGL")


if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
set(CMAKE_CXX_STANDAND 17)
endif(MSVC)

# 包含子项目。
add_subdirectory ("openGL")
