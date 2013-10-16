#include <fstream>
#include <string>
#include <stdint.h>
#include <memory>
#include <map>


#pragma pack(push, 1)
struct Data
{
    uint32_t type;
    uint32_t time;
    uint32_t len;
    std::unique_ptr<char> msg;
};
#pragma pack(pop)


int main()
{
    std::ifstream in(BINARY_DIR "/input.txt", std::ifstream::binary);
    std::ofstream out(BINARY_DIR "/output.txt", std::ofstream::binary);

    uint32_t T = 2;
    std::multimap<uint32_t, std::shared_ptr<Data>> msgs;
    
    in.seekg(0, std::ios::end);
    size_t file_size = in.tellg();
    in.seekg(0, std::ios::beg);

    size_t data_size = sizeof(Data) - sizeof(std::unique_ptr<char>);


    while(file_size)
    {
        std::shared_ptr<Data> data(new Data);
        data->len = 0;
        in.read(reinterpret_cast<char*>(data.get()), data_size);
        data->msg = std::unique_ptr<char>(new char[data->len]);
        in.read(data->msg.get(), data->len);
        file_size -= data_size + data->len;


        if ((data->time > (T - 2)) && (1 <= data->type) && (data->type <= 4))
        {
            msgs.insert(std::make_pair(data->time, data));

            if (data->time > T)
            {
                T = data->time;
            }
        }
    }

    for (auto it = msgs.begin(); it != msgs.end(); ++it)
    {
        out.write(reinterpret_cast<char*>(it->second.get()), data_size);
        out.write(it->second->msg.get(), it->second->len);
    }

    in.close();
    out.close();
}