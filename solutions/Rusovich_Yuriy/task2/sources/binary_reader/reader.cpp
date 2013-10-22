#include "reader.h"


namespace binary_reader
{
	Reader::Reader(const std::string &nameFile)
		: inputFile(SOURCE_DIR "/input.txt", std::ifstream::binary)
	{
	}

	Reader::~Reader()
	{
		inputFile.close();
	}

	bool Reader::isOpenedFile()
	{
		return inputFile.is_open();
	}

	bool Reader::readTradesData(TradesData *tradesData)
	{
		if (!inputFile.read(reinterpret_cast<char*>(&tradesData->type), sizeof(unsigned __int32)))
			return false;
		if (!inputFile.read(reinterpret_cast<char*>(&tradesData->time), sizeof(unsigned __int32)))
			return false;
		if (!inputFile.read(reinterpret_cast<char*>(&tradesData->len), sizeof(unsigned __int32)))
			return false;
		char *msg = new char[tradesData->len];
		if (!inputFile.read(reinterpret_cast<char*>(msg), tradesData->len * sizeof(char)))
		{		
			delete [] msg;
			return false;
		}
		tradesData->message.assign(msg, tradesData->len);

		delete [] msg;
		return true;
	}

	bool Reader::readDataFeed(DataFeed *dataFeed)
	{
		if(!inputFile.read(reinterpret_cast<char*>(dataFeed), sizeof(DataFeed)))
		{
			return false;
		}
		return true;
	}
}
