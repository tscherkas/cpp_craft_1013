#include <map>
#include "reader.h"
#include <stdint.h>

#define BUF_SIZE 2048

void count(std::map<uint32_t, uint32_t> &Msg_cnt, uint32_t Type)
{
	std::map<uint32_t, uint32_t>::iterator it;
	
	it = Msg_cnt.find(Type);
	if(it != Msg_cnt.end())
		it->second ++;
	else
		Msg_cnt.insert(std::pair<uint32_t,uint32_t>(Type, 1));
}

int main()
{
	std::fstream InFile;
	std::fstream OutFile;
	std::map<uint32_t, uint32_t> Msg_cnt;
	std::map<uint32_t, uint32_t>::iterator it;
	binary_reader::stock_ex_dat Data;
	uint32_t CurTime = 0;
	uint32_t StartTime = -1;
	uint32_t NumBytes = 0;
	double rate;


	InFile.open(BINARY_DIR"/Input.txt",std::ios_base::binary|std::ios_base::in);
	OutFile.open(BINARY_DIR"/Output.txt", std::ios_base::binary|std::ios_base::out|std::ios_base::trunc);

	if(InFile)
	{
		//Read and count messages
		while((binary_reader::read_binary(InFile, Data))==0)
		{
			if(Data.TIME < StartTime) 
			{
					StartTime = Data.TIME;
					CurTime = Data.TIME;
			}
			if(Data.TIME!=CurTime)
			{
				CurTime = Data.TIME;
				NumBytes = 3*sizeof(uint32_t) + Data.LEN;	
			}
			else
				NumBytes += 3*sizeof(uint32_t) + Data.LEN; 

			if (NumBytes < BUF_SIZE)
				count(Msg_cnt, Data.TYPE);
		}

		//Evaluate rate
		for (it = Msg_cnt.begin(); it != Msg_cnt.end(); ++it)
		{
			rate = (double(it->second))/(double (CurTime - StartTime + 1));
			OutFile.write((const char*)(&(it->first)), sizeof(uint32_t));
			OutFile.write((const char*)(&rate), sizeof(double));
		}
	}
	else 
	{
		std::cout << "Could not read Input.txt file" << std::endl;
	}

	InFile.close();
	OutFile.close();

	//system("pause");
	return 0;
}


