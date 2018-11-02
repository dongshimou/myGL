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

set(ENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine CACHE STRING "engin dir")

# 包含子项目。
add_subdirectory ("engine/src")

add_subdirectory ("test")


