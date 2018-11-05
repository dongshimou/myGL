// main.cpp: 定义应用程序的入口点。
//

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "logger.hpp"
#include "shader.hpp"
#include "texture.hpp"


#include "stb_image.h"

#include<iostream>
#include<array>
using namespace std;


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    auto window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    uint32_t vao, vbo, ebo;


    auto init_texture = [&]() {
        try {
            auto texture = std::make_unique<ym::texture>(ym::texture(
                "res/container.jpg"));
            return texture;
        } catch (std::string err_str) {
            ym::log(POS, err_str);
        }
    };
    auto texture = init_texture();

    auto init_shader = [&]() {
        try {
            auto shader = std::make_unique<ym::shader>(ym::shader(
                "res/shader.vert",
                "res/shader.frag"));

            std::array<float, 4 * 8> vertices = {
                //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
                     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
                     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
                    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
                    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
            };
            std::array<uint32_t, 3 * 2> indices = {
                    0, 1, 3, // first triangle
                    1, 2, 3  // second triangle
            };
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

            //0
            glVertexAttribPointer(
                0, 3, GL_FLOAT, GL_FALSE,
                8 * sizeof(float), (void*)0
            );
            glEnableVertexAttribArray(0);

            //1
            glVertexAttribPointer(
                1, 3, GL_FLOAT, GL_FALSE,
                8 * sizeof(float), (void*)(3 * sizeof(float))
            );
            glEnableVertexAttribArray(1);

            //2
            glVertexAttribPointer(
                2, 2, GL_FLOAT, GL_FALSE,
                8 * sizeof(float),(void*)(6 * sizeof(float))
            );
            glEnableVertexAttribArray(2);

            return shader;
        } catch (const std::string& str) {
            ym::log(POS, str);
        }
    };

    auto shader = init_shader();


    while (!glfwWindowShouldClose(window)) {
        [](GLFWwindow* w) {
            if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(w, true);
        }(window);

        [&]() {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            texture->use();

            shader->use();

            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }();


        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();
    return 0;
}
