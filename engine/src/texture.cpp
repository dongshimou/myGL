#include "texture.hpp"
#include "stb_image.h"
#include "glad/glad.h"

namespace ym {
texture::texture(std::string image_path) {
    //翻转图片
    stbi_set_flip_vertically_on_load(true);
    //加载资源
    m_data = stbi_load(image_path.c_str(), &m_width, &m_height, &m_channel, 0);
    if (m_data == nullptr) {
        throw(std::string("open image file error"));
    }
    //生成1个纹理
    glGenTextures(1, &Id);
    //绑定纹理
    glBindTexture(GL_TEXTURE_2D, Id);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //使用载入的图片资源
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
    //自动生成所有需要的多级渐远纹理。
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(m_data);
}
texture::~texture() {
}

int texture::width() const {
    return m_width;
}

int texture::height() const {
    return m_height;
}

int texture::channel() const {
    return m_channel;
}

void texture::use() {
    //绑定纹理
    glBindTexture(GL_TEXTURE_2D, Id);
}

}