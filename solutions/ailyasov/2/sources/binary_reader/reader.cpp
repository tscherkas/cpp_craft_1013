#include <iterator>
#include <cstddef>
#include <vector>
#include <stdexcept>
#include "reader.h"

namespace binary_reader {
    Reader::Reader(const std::string filename) {
        in.open(filename.c_str(), std::ios::in | std::ios::binary);
        if(!in.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
    }

    int Reader::get_int() {
        int v;
        in.read(reinterpret_cast<char*>(&v), sizeof(int));
        return v;
    }

	std::string Reader::get_string(const int len) {
        char str_msg[STR_BUF_SIZE];
        in.read(str_msg, sizeof(char) * len);        
        std::string s(str_msg, len);
		std::cout << s << std::endl;
		return s;
	}

	bool Reader::eof() const {
        return in.eof();
    }

    Reader::~Reader() {
        in.close();
    }
}
