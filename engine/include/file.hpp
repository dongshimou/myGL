
#ifndef YM_FILE_HPP
#define YM_FILE_HPP

#include<string>
#include<memory>
#include<sstream>
#include<fstream>

namespace ym {

std::string read_file(std::string path) {
    auto deleter = [](std::ifstream* ptr) {
        ptr->close();
    };
    auto in = std::unique_ptr<std::ifstream, decltype(deleter)>(new std::ifstream(path), deleter);
    if (!in->is_open()) {
        throw std::string("can't open ") + path;
    }
    std::stringstream ss;
    ss << in->rdbuf();
    return ss.str();
}
class file {
    //file(std::string path);
    //file(const char*path);
    //file(std::string_view path);

};

}

#endif // YM_FILE_HPP

