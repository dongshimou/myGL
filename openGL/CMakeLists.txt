# CMakeList.txt: openGL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

include_directories(${PROJECT_SOURCE_DIR}/includes)
link_directories(${PROJECT_SOURCE_DIR}/libs)
# 将源代码添加到此项目的可执行文件。
add_executable (openGL "main.cpp" "glad.c")

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
# TODO: 如有需要，请添加测试并安装目标。
if(WIN32)
target_link_libraries(openGL glfw3.lib opengl32.lib)
endif(WIN32)