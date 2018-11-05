
#ifndef YM_TEXTURE_HPP
#define YM_TEXTURE_HPP

#include <string>
namespace ym {
class texture {
public:
    uint32_t Id;
    explicit texture(std::string image_path);
    texture(const texture&) = delete;
    texture(texture&&) = default;
    texture&operator=(const texture&) = delete;
    texture&operator=(texture&&) = default;
    virtual ~texture();

    int width()const;
    int height()const;
    int channel()const;
    void use();
private:
    int m_width = 0;
    int m_height = 0;
    int m_channel = 0;
    unsigned char* m_data = nullptr;
};
}
#endif // !YM_TEXTURE_HPP
