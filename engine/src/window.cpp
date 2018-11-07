#include "..\include\window.hpp"
#include "..\include\window.hpp"
#include "window.hpp"

#include "logger.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include<string>
#include<functional>
namespace ym {
window::window(const char * title, int width, int height) {
    m_title = title;
    this->setWidth(width);
    this->setHeight(height);

    this->init();
}
void window::update() {
    [&](GLFWwindow* w) {
        if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(w, true);
    }(this->m_window);
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}
void window::clear() const {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
bool window::closed() const {
    return glfwWindowShouldClose(m_window);
}
window::~window() {
    glfwTerminate();
}
void window::OnWidthUpdate() {
    ym::log(POS, m_width);
}
void window::OnHeightUpdate() {
    ym::log(POS, m_height);
}
void window::init() {
    if (!glfwInit()) {
        ym::log(POS, "Failed to init glfw");
        glfwTerminate();
        throw(std::string("init glfw failed!"));
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    auto window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
    if (window == nullptr) {
        ym::log(POS, "Failed to create GLFW window");
        glfwTerminate();
        throw(std::string("init opengl windows failed!"));
    }
    m_window = window;
    glfwMakeContextCurrent(m_window);
    auto static resize= [=](GLFWwindow* window, int width, int height) {
        this->setWidth(width);
        this->setHeight(height);
        glViewport(0, 0, width, height);
    };
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow*a, int b, int c) {
        resize(a,b,c);
    });
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ym::log(POS,"Failed to initialize GLAD");
        glfwTerminate();
        throw(std::string("Failed to initialize GLAD"));
    }
    ym::log("opengl version : ",glGetString(GL_VERSION));
}
void window::setWidth(int width) {
    if (m_width == width)return;
    m_width = width;
    OnWidthUpdate();
}
void window::setHeight(int height) {
    if(m_height == height)return;
    m_height = height;
    OnHeightUpdate();
}
}