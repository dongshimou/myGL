#ifndef YM_WINDOW_HPP
#define YM_WINDOW_HPP

struct GLFWwindow;
namespace ym {
class window {
public:
    explicit window(const char*title,int width,int height);
    inline int width()const { return m_width; }
    inline int height()const { return m_height; }
    void update();
    void clear()const;
    bool closed()const;
    virtual ~window();
    virtual void OnWidthUpdate();
    virtual void OnHeightUpdate();
private:
    void init();
    void setWidth(int width);
    void setHeight(int height);
private:
    const char *m_title;
    int m_height, m_width;
    GLFWwindow* m_window;
};
}
#endif // !YM_WINDOW_HPP
