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
            bool eof() const;
            std::string get_string(int);
            ~Reader();
        private:
			static const size_t STR_BUF_SIZE = 102400;
            std::ifstream in;
            Reader();
            Reader(const Reader&);
            void operator=(const Reader&);
    }; 
}
