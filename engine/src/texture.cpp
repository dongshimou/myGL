#include "texture.hpp"
#include "stb_image.h"
#include "glad/glad.h"

namespace ym {
texture::texture(std::string image_path) {
    //��תͼƬ
    stbi_set_flip_vertically_on_load(true);
    //������Դ
    m_data = stbi_load(image_path.c_str(), &m_width, &m_height, &m_channel, 0);
    if (m_data == nullptr) {
        throw(std::string("open image file error"));
    }
    //����1������
    glGenTextures(1, &Id);
    //������
    glBindTexture(GL_TEXTURE_2D, Id);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //ʹ�������ͼƬ��Դ
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
    //�Զ�����������Ҫ�Ķ༶��Զ����
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
    //������
    glBindTexture(GL_TEXTURE_2D, Id);
}

}