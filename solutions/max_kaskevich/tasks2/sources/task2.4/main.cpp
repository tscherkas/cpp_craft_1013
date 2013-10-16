#include <fstream>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <memory>
#include <vector>
#include <map>

enum msg_type: uint32_t
{
    MARKET_OPEN = 1u,
    TRADE = 2u,
    QUOTE = 3u,
    MARKET_CLOSE = 4u,
    msg_type_end
};

struct message
{
    msg_type type;
    uint32_t time;
    uint32_t len;
    std::vector<char> msg;
};

std::ifstream& operator >> (std::ifstream& input, message& m)
{
    input.read(reinterpret_cast<char*>(&m.type), sizeof(m.type));
    input.read(reinterpret_cast<char*>(&m.time), sizeof(m.time));
    input.read(reinterpret_cast<char*>(&m.len), sizeof(m.len));
    if(m.len)
    {
        m.msg.resize(m.len);
        input.read(m.msg.data(), m.len);
    }
    return input;
}

std::ofstream& operator << (std::ofstream& output, message& m)
{
    output.write(reinterpret_cast<char*>(&m.type), sizeof(m.type));
    output.write(reinterpret_cast<char*>(&m.time), sizeof(m.time));
    output.write(reinterpret_cast<char*>(&m.len), sizeof(m.len));
    if(m.len)
    {
        output.write(m.msg.data(), m.len);
    }
    return output;
}

int main( int argc, char* argv[] )
{
    std::ifstream input(BINARY_DIR "/2.4_example.in", std::ios::binary);
    std::ofstream output(BINARY_DIR "/2.4_example.out", std::ios::binary);
    if(!input || !output)
    {
        return 1;
    }

    typedef std::multimap<uint32_t, std::shared_ptr< message > > message_map;
    message_map my_map;
    uint32_t T = 0;
    while(1)
    {
        std::shared_ptr< message > m(new message());
        input >> *m;
        if(input)
        {
            if(m->type < msg_type_end && m->time + 2 > T )
            {
                my_map.insert(message_map::value_type(m->time, m));
                T = std::max(T, m->time);
            }

        }
        else
        {
            break;
        }
    }

    std::for_each(my_map.begin(), my_map.end(), [&output](message_map::value_type& msg_pair)
    {
        output << *(msg_pair.second);

    });
}
