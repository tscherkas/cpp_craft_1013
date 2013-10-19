#include <iterator>
#include <cstddef>
#include <vector>
#include <stdexcept>
#include "writer.h"

namespace binary_writer {

    Writer::Writer(const std::string filename) {
        out.open(filename.c_str(), std::ios::out | std::ios::binary);
        if(!out.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
    }

    void Writer::save_int(int v) {
        out.write(reinterpret_cast<char*>(&v), sizeof(v));
    }

    void Writer::save_double(double v) {
        out.write(reinterpret_cast<char*>(&v), sizeof(v));
    }

    void Writer::save_string(const std::string& s) {
        out.write(s.c_str(), s.size());
    }

    bool Writer::eof() const {
        return out.eof();
    }

    Writer::~Writer() {
        out.close();
    }

}
