// main.cpp: 定义应用程序的入口点。
//

#include "glad/glad.h"

#include "glfw3.h"

#include<iostream>
#include<string>
#include<sstream>
#include<memory>
#include<array>
#include<fstream>
using namespace std;

#define LINE2STR(x) #x
#define LINE2STRHELP(x) LINE2STR(x)
#define POS (__FILE__ ":line " LINE2STRHELP(__LINE__))
template<typename T>
inline void log(T t) {
    std::cout << t << "\n";
}
template<typename T,typename ...Args>
inline void  log(T t,Args... args) {
    std::cout << t << " ";
    log(args...);
}
std::string read_file(std::string path) {
    auto deleter = [](ifstream* ptr) {
        ptr->close();
    };
    auto in = std::unique_ptr<ifstream, decltype(deleter)>(new ifstream(path), deleter);
    if (!in->is_open()) {
        throw std::string("can't open ") + path;
    }
    std::stringstream ss;
    ss << in->rdbuf();
    return ss.str();
}

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
    auto init_shader = [&]()->GLuint {
        try {
            auto vert = glCreateShader(GL_VERTEX_SHADER);
            auto vert_source = read_file("res/shader.vert");
            GLchar const*vs[] = { vert_source.data() };
            glShaderSource(vert, 1, vs, nullptr);
            glCompileShader(vert);
            int success;
            glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
            if (!success) {
                char err_str[256];
                glGetShaderInfoLog(vert, 256, nullptr, err_str);
                log(POS, err_str);
                return 0;
            }

            auto frag = glCreateShader(GL_FRAGMENT_SHADER);
            auto frag_source = read_file("res/shader.frag");
            GLchar const*fs[] = { frag_source.data() };
            glShaderSource(frag, 1, fs, nullptr);
            glCompileShader(frag);
            glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
            if (!success) {
                char err_str[256];
                glGetShaderInfoLog(frag, 256, nullptr, err_str);
                log(POS, err_str);
                return 0;
            }

            auto shader = glCreateProgram();
            glAttachShader(shader, vert);
            glAttachShader(shader, frag);
            glLinkProgram(shader);
            glGetShaderiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                char err_str[256];
                glGetShaderInfoLog(shader, 256, nullptr, err_str);
                log(POS, err_str);
                return 0;
            }

            glDeleteShader(vert);
            glDeleteShader(frag);

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
            log(POS, str);
        }
        return 0;
    };

    auto shader=init_shader();

    

    while (!glfwWindowShouldClose(window)) {
        [](GLFWwindow* w){
            if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(w, true);
        }(window);

        
        [&]() {
            log(POS, "redraw shader");
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shader);
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
