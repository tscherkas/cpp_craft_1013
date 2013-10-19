#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace binary_writer
{
    class Writer {
        public:
            Writer(const std::string filename);
            void save_int(int);
            void save_double(double);
            bool eof() const;
            void save_string(const std::string&);
            ~Writer();
        private:
            std::ofstream out;
            Writer();
            Writer(const Writer&);
            void operator=(const Writer&);
    };
}
