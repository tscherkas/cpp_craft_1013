#include <iterator>
#include <cstddef>
#include <vector>
#include <cctype>
#include <stdexcept>

#include <boost/cstdint.hpp>

#include "reader.h"

namespace binary_reader {

    Reader::Reader(const std::string filename)  {
        in.open(filename.c_str(), std::ios::in | std::ios::binary);
        if(!in.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
    }

    std::string Reader::get_string(const size_t len) {
        if(len > STR_BUF_SIZE)
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
