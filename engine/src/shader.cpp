
#include "file.hpp"
#include "logger.hpp"
#include "shader.hpp"

#include "glad/glad.h"
namespace ym {

void shader::check_throw(uint32_t id) {
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char err_str[256];
        glGetShaderInfoLog(id, 256, nullptr, err_str);
        throw(std::string(POS) + std::string(err_str));
    }
}

uint32_t shader::compile(std::string_view source,int flag) {
    auto id = glCreateShader(flag);
    GLchar const*vs[] = { source.data() };
    glShaderSource(id, 1, vs, nullptr);
    glCompileShader(id);
    check_throw(id);
    return id;
}
uint32_t shader::link(uint32_t vert, uint32_t frag) {
    auto shader = glCreateProgram();
    glAttachShader(shader, vert);
    glAttachShader(shader, frag);
    glLinkProgram(shader);
    check_throw(shader);
    glDeleteShader(vert);
    glDeleteShader(frag);
    return shader;
}

shader::shader(std::string vert_path, std::string frag_path) {
    auto vs = read_file(vert_path);
    auto fs = read_file(frag_path);
    auto vert = compile(vs, GL_VERTEX_SHADER);
    auto frag = compile(fs, GL_FRAGMENT_SHADER);

    Id = link(vert, frag);
}

shader::~shader() {

}


void shader::use() {
    glUseProgram(Id);
}

}