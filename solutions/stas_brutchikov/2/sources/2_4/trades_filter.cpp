// puzzle_2.cpp : Defines the entry point for the console application.
//
#include <fstream>
#include <stdint.h>

#include <boost\noncopyable.hpp>

#include "../base/base.hpp"

namespace task24
{
    using namespace task2;

    enum MessageType : uint32_t
    {
        MarketOpen = 1,
        Trade = 2,
        Quote = 3,
        MarketClose = 4
    };

    struct Data : boost::noncopyable
    {
        uint32_t type;
        uint32_t time;
        uint32_t length;        

        explicit Data(){}

        friend std::istream& operator >> (std::istream& in, Data& m);
        friend std::ostream& operator << (std::ostream& ou, Data& m);
    };

    std::istream& operator >> (std::istream& in, Data& m)
    {
        ReadValue(in, m.type);
        ReadValue(in, m.time);
        ReadValue(in, m.length);        
        return in;
    }

    std::ostream& operator << (std::ostream& out, Data& m)
    {
        WriteValue(out, m.type);
        WriteValue(out, m.time);
        WriteValue(out, m.length);    
        return out;
    }

    void SortData(std::istream& in, std::ostream& out, uint32_t current_time)
    {
        Data d;
        while (in >> d)
        {
            if (((d.time+2) > current_time) 
                && ((d.type >= MarketOpen)
                    && (d.type <= MarketClose)))
            {
                out << d;
                std::copy_n(std::istreambuf_iterator<char>(in), d.length, std::ostreambuf_iterator<char>(out));
                in.ignore(1); //copy_n not put first(source) iterator on next element, destination is ok (MSVC2010)
            }
            else
            {
                in.ignore(d.length);
            }
            if (current_time < d.time)
                current_time = d.time;
        }
    };

 
} // task24
    

int main()
{
    std::ifstream in (BINARY_DIR "/input.txt", std::ios::binary);
    std::ofstream out (BINARY_DIR "/ouput.txt", std::ios::binary);
    if (!in.is_open() || !out.is_open())
    {
        return 1;
    }
    task24::SortData(in, out, 0);
	return 0;
}

