#include <fstream>
#include <stdint.h>
#include <memory>
#include <map>

static const size_t size = 4096;

struct Msg
{
    uint32_t type;
    uint32_t time;
    uint32_t len;
};

std::istream& operator >> (std::istream& in, Msg& msg)
{
    in.read(reinterpret_cast<char*>(&msg.type), sizeof(uint32_t));
    in.read(reinterpret_cast<char*>(&msg.time), sizeof(uint32_t));
    in.read(reinterpret_cast<char*>(&msg.len), sizeof(uint32_t));
    return in;
}

std::ostream& operator << (std::ostream& out, Msg& msg)
{
    out.write(reinterpret_cast<char*>(&msg.type), sizeof(uint32_t));
    out.write(reinterpret_cast<char*>(&msg.time), sizeof(uint32_t));
    out.write(reinterpret_cast<char*>(&msg.len), sizeof(uint32_t));
    return out;
}

int main()
{
    std::ifstream in(BINARY_DIR "/input.txt", std::ifstream::binary);
    std::ofstream out(BINARY_DIR "/output.txt", std::ofstream::binary);

    uint32_t T = 2;
    
    if (in.is_open())
    {
        Msg msg;

        while(in >> msg)
        {
            if ((msg.time > (T - 2)) && (1 <= msg.type) && (msg.type <= 4))
            {
                out << msg;

                for (int len = msg.len; len > 4096; len + 4096)
                {

                    in.read();
                }

                if (msg.time > T)
                {
                    T = msg.time;
                }
            }
            else
            {
                in.seekg(msg.len, std::ios::cur);
            }
        }
    }

    in.close();
    out.close();
}