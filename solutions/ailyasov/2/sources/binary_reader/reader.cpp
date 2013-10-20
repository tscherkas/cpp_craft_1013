#include <iterator>
#include <cstddef>
#include <vector>
#include <cctype>
#include <stdexcept>
#include "reader.h"

namespace binary_reader {
    Reader::Reader(const std::string filename)  {
        in.open(filename.c_str(), std::ios::in | std::ios::binary);
        if(!in.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
    }

    int Reader::get_int() {
        int v;
        in.read(reinterpret_cast<char*>(&v), sizeof(v));
        return v;
    }

    double Reader::get_double() {
        double v;
        in.read(reinterpret_cast<char*>(&v), sizeof(v));
        return v;
    }

    std::string Reader::get_string2(const unsigned int len) {
        if(len >= STR_BUF_SIZE)
            throw std::runtime_error("Length is too big");
        char c;
        unsigned int chars_read = 0;
        std::string str;
        str.reserve(len);
        while(chars_read++ <= len) {
            in.read(&c, sizeof(c));
            if(std::isalnum(c)) {
                str.push_back(c);
            }
        }
        return str;
    }

    std::string Reader::get_string(const unsigned int len) {
        if(len >= STR_BUF_SIZE)
            throw std::runtime_error("Length is too big");

        char str_msg[STR_BUF_SIZE];
        in.read(str_msg, len);        
        std::string s(str_msg, len);
        return s;
    }

	bool Reader::eof() const {
        return in.eof();
    }

    Reader::~Reader() {
        in.close();
    }
}
