// main.cpp: 定义应用程序的入口点。
//

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "logger.hpp"
#include "shader.hpp"

#include<iostream>
#include<array>
using namespace std;


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    auto window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window,[](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    uint32_t vao, vbo;
    auto init_shader = [&]() {
        try {
            auto shader = std::make_unique<ym::shader>(ym::shader(
                "res/shader.vert",
                "res/shader.frag"));
            std::array<float,3*3> vertices = {
                -0.5f,-0.5f,0.0f,
                0.5f,-0.5f,0.0f,
                0.0f,0.5f,0.0f,
            };
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices.size()/3 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            return shader;
        } catch (const std::string& str) {
            ym::log(POS, str);
        }
    };

    auto shader=init_shader();
    float myvalue = 0.0f;
    ym::log(POS, myvalue);

    while (!glfwWindowShouldClose(window)) {
        [](GLFWwindow* w){
            if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(w, true);
        }(window);

        [&]() {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            shader->use();
            shader->set("myvalue", std::move(myvalue++));
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }();


        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return 0;
}
