#include <fstream>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <memory>
#include <vector>
#include <map>
#include <iterator>

enum msg_type: uint32_t
{
    MARKET_OPEN = 1u,
    TRADE = 2u,
    QUOTE = 3u,
    MARKET_CLOSE = 4u    
};

struct message
{
    uint32_t type;
    uint32_t time;
};

std::istream& operator >> (std::istream& input, message& m)
{
    input.read(reinterpret_cast<char*>(&m.type), sizeof(m.type));
    input.read(reinterpret_cast<char*>(&m.time), sizeof(m.time));
    return input;
}

std::ostream& operator << (std::ostream& output, message& m)
{
    output.write(reinterpret_cast<char*>(&m.type), sizeof(m.type));
    output.write(reinterpret_cast<char*>(&m.time), sizeof(m.time));
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

    uint32_t T = 0;
    message m;
    while(input >> m)
    {
        if(m.type >= MARKET_OPEN && m.type <= MARKET_CLOSE && m.time + 2 > T )
        {
            if( !(output << m ) )
            {
                return 1;
            }
            // redirect msg to output
            int32_t len;
            input.read(reinterpret_cast<char*>(&len), sizeof(len));
            if (input && len)
            {
                std::istreambuf_iterator<char> it(input);
                while(output.write(*(it), sizeof(*(it))) && --len)
                {
                    ++it;
                }
            }

            T = std::max(T, m.time);
        }
        else
        {
            // miss msg
            int32_t len;
            input.read(reinterpret_cast<char*>(&len), sizeof(len));
            if (input)
            {
                input.seekg(len, std::ios::cur);
            }
        }
    }
}
