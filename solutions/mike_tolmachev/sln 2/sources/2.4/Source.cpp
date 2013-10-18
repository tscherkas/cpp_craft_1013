#include <fstream>
#include <stdint.h>
#include <map>


static const uint32_t DATA_SIZE = 3*sizeof(uint32_t);


int main()
{
    std::ifstream in(BINARY_DIR "/input.txt", std::ifstream::binary);
    std::ofstream out(BINARY_DIR "/output.txt", std::ofstream::binary);

    uint32_t T = 2;
    
    if (in)
    {
        in.seekg(0, std::ios::end);
        size_t file_size = in.tellg();
        in.seekg(0, std::ios::beg);
    
        while(file_size)
        {
            uint32_t data[3];//TYPE,TIME,LEN
            in.read(reinterpret_cast<char*>(data), DATA_SIZE);
            std::unique_ptr<char> msg = std::unique_ptr<char>(new char[data[2]]);
            in.read(msg.get(), data[2]);
        

            if ((data[1] > (T - 2)) && (1 <= data[0]) && (data[0] <= 4))
            {
                out.write(reinterpret_cast<char*>(data), DATA_SIZE);
                out.write(msg.get(), data[2]);

                if (data[1] > T)
                {
                    T = data[1];
                }
            }

            file_size -= DATA_SIZE + data[2];
        }
    }

    in.close();
    out.close();
}