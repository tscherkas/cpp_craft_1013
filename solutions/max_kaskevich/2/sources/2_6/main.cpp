#include <stdint.h>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
#include <boost/spirit/include/qi.hpp>

struct message
{
    char stock_name[9];
    char date_time[8];

    double price;        
    double vwap;

    uint32_t volume;

    double f1; 
    double t1;
    double f2; 
    double f3;
    double f4;
}; 
// 9 + 8
// + 8 * 2
// + 4
// + 8 * 5
// = 77

std::istream& operator >> (std::istream& input, message& m)
{
    input.read(m.stock_name, sizeof(m.stock_name));
    input.read(m.date_time, sizeof(m.date_time));
    input.read(reinterpret_cast<char*>(&m.price), sizeof(m.price));
    input.read(reinterpret_cast<char*>(&m.vwap), sizeof(m.vwap));
    input.read(reinterpret_cast<char*>(&m.volume), sizeof(m.volume));
    input.read(reinterpret_cast<char*>(&m.f1), sizeof(m.f1));
    input.read(reinterpret_cast<char*>(&m.t1), sizeof(m.t1));
    input.read(reinterpret_cast<char*>(&m.f2), sizeof(m.f2));
    input.read(reinterpret_cast<char*>(&m.f3), sizeof(m.f3));
    input.read(reinterpret_cast<char*>(&m.f4), sizeof(m.f4));
    return input;
}

std::ostream& operator << (std::ostream& output, message& m)
{
    output.write(reinterpret_cast<char*>(&m.stock_name), sizeof(m.stock_name));

    uint32_t year, month, day;
    using boost::spirit::qi::int_parser;
    int_parser<uint32_t, 10U, 4, 4> year_parser;
    int_parser<uint32_t, 10U, 2, 2> month_day_parser;
    std::string text(m.date_time, 8);

    if (!boost::spirit::qi::parse(text.begin(), text.end(),
        year_parser >> month_day_parser >> month_day_parser,
        year, month, day))
    {
        output.flags( std::ios::badbit);
        return output;
    }
    uint32_t all_days = (year - 1) * 372 + (month - 1) * 31 + day;
    output.write(reinterpret_cast<char*>(&all_days), sizeof(all_days));

    output.write(reinterpret_cast<char*>(&m.vwap), sizeof(m.vwap));
    output.write(reinterpret_cast<char*>(&m.volume), sizeof(m.volume));
    output.write(reinterpret_cast<char*>(&m.f1), sizeof(m.f1));
    output.write(reinterpret_cast<char*>(&m.f4), sizeof(m.f4));
    output.write(reinterpret_cast<char*>(&m.f3), sizeof(m.f3));
    return output;
}

int main( int argc, char* argv[] )
{
    std::ifstream input(BINARY_DIR "/input.txt", std::ios::binary);
    std::ofstream output(BINARY_DIR "/output.txt", std::ios::binary);
    if(!input || !output)
    {
        return 1;
    }
    message m;
    while (input >> m && output << m)
    {}

}