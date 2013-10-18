#include <fstream>
#include <string>
#include <stdint.h>

//Формат файла: <stock_name>, <date_time>, <price>,<vwap>,<volume>,<f1>,<t1>,<f2>,<f3>,<f4>.
//Где stock_name – string (длинна строки не более 8 char), date_time: дата в формате YYYYMMDD, price:
//double, vwap: double, volume: uint32, (f1, t1, f2, f3, f4) данные о торгах за день типа double.
struct Data
{
    char stock_name[8];
    char date_time[8];
    double price;
    double vwap;
    uint32_t volume;
    double datas[5];
};

static const size_t DATA_SIZE = 16 + sizeof(uint32_t) + 7*sizeof(double);

//[ stock_name, date, price, volume, f2 ]. При этом поля описываются следующими форматами: 
//stock_name: char[9]; date: uint32 (количество дней от начала 01.01.0001 принимая, что длительность 
//года 372 дня, длительность месяцев 31 день); price: double (содержит значение поля vwap); volume: 
//uint32; f1: double; f4: double; f3 double.
void WriteToFile(std::ofstream& out, Data& data)
{
    out.write(data.stock_name, 8);//stock_name
    out.write('\0', 1);
    //write date
    out.write(reinterpret_cast<char*>(&data.vwap), sizeof(double));//price=vwap
    out.write(reinterpret_cast<char*>(&data.volume), sizeof(uint32_t));//volume
    out.write(reinterpret_cast<char*>(&data.datas[0]), sizeof(double));//f1
    out.write(reinterpret_cast<char*>(&data.datas[4]), sizeof(double));//f4
    out.write(reinterpret_cast<char*>(&data.datas[3]), sizeof(double));//f3
}

int main()
{
    std::ifstream in(BINARY_DIR "/input.txt", std::ifstream::binary);
    std::ofstream out(BINARY_DIR "/output.txt", std::ofstream::binary);
        
    in.seekg(0, std::ios::end);
    size_t file_size = in.tellg();
    in.seekg(0, std::ios::beg);
    
    while(file_size)
    {
        Data data;
        in.read(data.stock_name, 8);
        in.read(data.date_time, 8);
        in.read(reinterpret_cast<char*>(&data.price), sizeof(double));
        in.read(reinterpret_cast<char*>(&data.vwap), sizeof(double));
        in.read(reinterpret_cast<char*>(&data.volume), sizeof(uint32_t));
        in.read(reinterpret_cast<char*>(data.datas), sizeof(data.datas));

        WriteToFile(out, data);

        file_size -= DATA_SIZE;
    }

    in.close();
    out.close();
}