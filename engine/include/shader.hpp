
#ifndef YM_SHADER_HPP
#define YM_SHADER_HPP

#include <string_view>
#include <string>
#include <any>

namespace ym {

class shader {
public:
    uint32_t Id;
    explicit shader(std::string vert_path, std::string frag_path);
    shader(const shader&) = delete;
    shader(shader&&) = default;
    shader& operator=(const shader&) = delete;
    shader& operator=(shader&&) = default;
    virtual ~shader();
    void use();
    template<typename T>
    void set(std::string_view name, T &&value) {
        set(name.data(), std::forward<T>(value));
    }
    template<typename T>
    void set(const char* name, T&& value) {
        if constexpr  (std::is_same_v<T, bool>) {
            glUniform1i(glGetUniformLocation(Id, name), value);
        } else if constexpr (std::is_same_v<T, int>) {
            glUniform1i(glGetUniformLocation(Id, name), value);
        }else if constexpr (std::is_same_v<T, float>) {
            glUniform1f(glGetUniformLocation(Id, name), value);
        }else if constexpr (std::is_same_v<T, unsigned int>) {
            glUniform1ui(glGetUniformLocation(Id, name), value);
        }
        log(POS, value);
    }
private:
    uint32_t compile(std::string_view source, int flag);
    uint32_t link(uint32_t vert, uint32_t frag);
    static void check_throw(uint32_t id);
};

}

#endif // !YM_SHADER_HPP
