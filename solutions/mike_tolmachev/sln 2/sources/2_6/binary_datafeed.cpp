#include <fstream>
#include <string>
#include <stdint.h>


struct Data
{
    char stock_name[8];//8?
    char date_time[8];
    double price;
    double vwap;
    uint32_t volume;
    double datas[5];
};


static const size_t DATA_SIZE = 16 + sizeof(uint32_t) + 7*sizeof(double);


void WriteToFile(std::ofstream& out, Data& data)
{
    out.write(data.stock_name, 8);//stock_name 8?
    out.write('\0', 1); 8?
    //write date
	uint32_t day = 0;
	uint32_t month = 0;
	uint32_t year = 0;
	std::sscanf(data.date_time, "%4u%2u%2u", &year, &month, &day);
	uint32_t date = 372*(year - 1) + 31*(month-1) + day;
	out.write(reinterpret_cast<char*>(&date), sizeof(uint32_t));
	//
    out.write(reinterpret_cast<char*>(&data.vwap), sizeof(double));//price=vwap
    out.write(reinterpret_cast<char*>(&data.volume), sizeof(uint32_t));//volume
	out.write(reinterpret_cast<char*>(&data.datas[2]), sizeof(double));//f2
}


int main()
{
    std::ifstream in(BINARY_DIR "/input.txt", std::ifstream::binary);
    std::ofstream out(BINARY_DIR "/output.txt", std::ofstream::binary);
        
    in.seekg(0, std::ios::end);
    size_t file_size = in.tellg();
    in.seekg(0, std::ios::beg);
    
	if (in)
	{
		while(file_size && in.good())
		{
			Data data;
			in.read(data.stock_name, 8);//8?
			in.read(data.date_time, 8);
			in.read(reinterpret_cast<char*>(&data.price), sizeof(double));
			in.read(reinterpret_cast<char*>(&data.vwap), sizeof(double));
			in.read(reinterpret_cast<char*>(&data.volume), sizeof(uint32_t));
			in.read(reinterpret_cast<char*>(data.datas), sizeof(data.datas));

			WriteToFile(out, data);

			file_size -= DATA_SIZE;
		}
	}

    in.close();
    out.close();
}