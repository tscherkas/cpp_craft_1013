#include <fstream>
#include <string>
#include <stdint.h>
#include <map>


static const uint32_t MSG_SIZE = 2048;
static const uint32_t DATA_SIZE = 3*sizeof(uint32_t);


int main()
{
    std::ifstream in(BINARY_DIR "/input.txt", std::ifstream::binary);
    std::ofstream out(BINARY_DIR "/output.txt", std::ofstream::binary);

    if (in)
    {
        in.seekg(0, std::ios::end);
        size_t file_size = in.tellg();
        in.seekg(0, std::ios::beg);
    
        std::map<uint32_t, std::map<uint32_t, uint32_t>> msgs;//<TYPE,<TIME,LEN>>

        while(file_size)
        {
            uint32_t msg[3];//TYPE,TIME,LEN
            in.read(reinterpret_cast<char*>(msg), DATA_SIZE);
            in.seekg(msg[2], std::ios::cur);

            uint32_t msg_size = DATA_SIZE + msg[2];

            auto it = msgs[msg[0]].find(msg[1]);
            if (it == msgs[msg[0]].end())
            {
                msgs[msg[0]][msg[1]] = 0;
                auto new_elem = msgs[msg[0]].insert(std::make_pair(msg[1], 0));
                it = new_elem.first;
            }

            if ((it->second + msg_size) <= MSG_SIZE)
            {
                it->second += msg_size;
            }

            file_size -= msg_size;
        }

        for (auto it = msgs.begin(); it != msgs.end(); ++it)
        {
            uint32_t type = it->first;
            out.write(reinterpret_cast<char*>(&type), sizeof(uint32_t));
            uint32_t count = it->second.size();
            out.write(reinterpret_cast<char*>(&count), sizeof(uint32_t));
        }
    }

    in.close();
    out.close();
}