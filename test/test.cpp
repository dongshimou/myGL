
#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "logger.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include "window.hpp"

#include "stb_image.h"

#include<iostream>
#include<array>

using namespace std;


int main() {

    try {
        auto window = new ym::window("learn openGL", 800, 600);

        uint32_t vao, vbo, ebo;
        auto init_texture = [&]() {
            auto texture = std::make_unique<ym::texture>(ym::texture(
                "res/container.jpg"));
            return texture;
        };
        auto texture = init_texture();
        auto init_shader = [&]() {
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
                8 * sizeof(float), (void*)(6 * sizeof(float))
            );
            glEnableVertexAttribArray(2);

            return shader;
        };
        auto shader = init_shader();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        while (!window->closed()) {
            [&]() {
                window->clear();
                texture->use();

                shader->use();

                glBindVertexArray(vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            }();


            window->update();
        }
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);

        glfwTerminate();
    } catch (std::string err_str) {
        ym::log(err_str);
    }
    return 0;
}
