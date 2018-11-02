

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

include_directories(${ENGINE_DIR}/include)
link_directories(${ENGINE_DIR}/lib)

add_executable (openGL "test.cpp")

target_link_libraries(openGL glfw3 opengl32 engine)

