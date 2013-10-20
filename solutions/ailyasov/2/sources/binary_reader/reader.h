#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace binary_reader {
    class Reader {
        public:
            Reader(const std::string filename);
            int get_int();
            double get_double();
            bool eof() const;
            std::string get_string(unsigned int);
            std::string get_string2(unsigned int);
            ~Reader();
        private:
			static const size_t STR_BUF_SIZE = 102400;
            std::ifstream in;
            Reader();
            Reader(const Reader&);
            void operator=(const Reader&);
    }; 
}
