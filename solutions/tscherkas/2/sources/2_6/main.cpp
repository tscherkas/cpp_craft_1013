#include "fstream"
#include "boost/cstdint.hpp"
#include "iostream"
#include "cstring"
#include "stdio.h"

using namespace std;

struct Data_block
{
        char stock_name[8];
        char date_time[8];
        double price;
        double vwap;
        boost::uint32_t volume;
        double f1;
        double t1;
        double f2;
        double f3;
        double f4;
};
static const size_t DOUBLE_SIZE = sizeof(double);
static const size_t UINT32_SIZE = sizeof(boost::uint32_t);

ostream& operator <<(ostream& out,const Data_block& obj)
{
    const size_t BUF_SIZE = 7*DOUBLE_SIZE+UINT32_SIZE+16;
    char buf[BUF_SIZE],*buf_ptr=buf;
    memcpy(buf_ptr,&obj.stock_name,8);buf_ptr+=8;
    memcpy(buf_ptr,&obj.date_time,8);buf_ptr+=8;
    memcpy(buf_ptr,&obj.price,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(buf_ptr,&obj.vwap,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(buf_ptr,&obj.volume,UINT32_SIZE);buf_ptr+=UINT32_SIZE;
    memcpy(buf_ptr,&obj.f1,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(buf_ptr,&obj.t1,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(buf_ptr,&obj.f2,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(buf_ptr,&obj.f3,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(buf_ptr,&obj.f4,DOUBLE_SIZE);
    out.write(buf,BUF_SIZE);return out;
}
istream& operator >>(istream& in,Data_block& obj)
{
    const size_t BUF_SIZE = 7*DOUBLE_SIZE+UINT32_SIZE+16;
    char buf[BUF_SIZE],*buf_ptr=buf;
    in.read(buf,BUF_SIZE);
    if(in.eof())
        return in;
    memcpy(&obj.stock_name,buf_ptr,8);buf_ptr+=8;
    memcpy(&obj.date_time,buf_ptr,8);buf_ptr+=8;
    memcpy(&obj.price,buf_ptr,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(&obj.vwap,buf_ptr,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(&obj.volume,buf_ptr,UINT32_SIZE);buf_ptr+=UINT32_SIZE;
    memcpy(&obj.f1,buf_ptr,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(&obj.t1,buf_ptr,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(&obj.f2,buf_ptr,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(&obj.f3,buf_ptr,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(&obj.f4,buf_ptr,DOUBLE_SIZE);
    return in;
}
void write_interpritated(ostream& out,const Data_block& obj)
{
    int month,day,year;
    std::sscanf(obj.date_time, "%4d%2d%2d", &year, &month, &day);
    boost::uint32_t date = --year*372 + --month*31 + day;
    const size_t BUF_SIZE = 2*DOUBLE_SIZE+2*UINT32_SIZE+9;
    char buf[BUF_SIZE],*buf_ptr=buf;
    memcpy(buf_ptr,&obj.stock_name,8);buf_ptr+=9;
    memcpy(buf_ptr,&date,UINT32_SIZE);buf_ptr+=UINT32_SIZE;
    memcpy(buf_ptr,&obj.vwap,DOUBLE_SIZE);buf_ptr+=DOUBLE_SIZE;
    memcpy(buf_ptr,&obj.volume,UINT32_SIZE);buf_ptr+=UINT32_SIZE;
    memcpy(buf_ptr,&obj.f2,DOUBLE_SIZE);
    out.write(buf,BUF_SIZE);
}

int main()
{
    ifstream input_file (SOURCE_DIR "/tests/input_261.txt",ios::in|ios::binary);
    if(!input_file.is_open())
    {
        cout << "Error by opening input file";
        return 0;
    }
    ofstream output_file(SOURCE_DIR "/tests/2.6_example.out",ios::out|ios::binary);
    if(!output_file.is_open())
    {
        cout << "Error by creating output file";
        return 0;
    }
    while(!input_file.eof())
    {
        Data_block block;
        input_file>>block;
        if(input_file.eof())
            break;
        write_interpritated(output_file,block);
    }
    input_file.close();
    output_file.close();
	return 0;
}
