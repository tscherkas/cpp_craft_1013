#include "message.h"


std::istream& operator >> (std::istream& input, message& m)
{
    input.read(reinterpret_cast<char*>(&m.type), sizeof(m.type));
    input.read(reinterpret_cast<char*>(&m.time), sizeof(m.time));
    input.read(reinterpret_cast<char*>(&m.len), sizeof(m.len));
    return input;
}

std::ostream& operator << (std::ostream& output, message& m)
{
    output.write(reinterpret_cast<char*>(&m.type), sizeof(m.type));
    output.write(reinterpret_cast<char*>(&m.time), sizeof(m.time));
    output.write(reinterpret_cast<char*>(&m.len), sizeof(m.len));
    return output;
}