#ifndef YM_LOGGER_HPP
#define YM_LOGGER_HPP
#include<iostream>
#define LINE2STR(x) #x
#define LINE2STRHELP(x) LINE2STR(x)
#define POS (__FILE__ ":line " LINE2STRHELP(__LINE__))

namespace ym {
template<typename T>
inline void log(T t) {
#ifdef YM_DEBUG
    std::cout << t << std::endl;
#endif // YM_DEBUG
}
template<typename T, typename ...Args>
inline void log(T t, Args... args) {
#ifdef YM_DEBUG
    std::cout << t << " ";
    ym::log(args...);
#endif // YM_DEBUG
}
}
#endif // !YM_LOGGER_HPP