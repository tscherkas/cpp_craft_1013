#ifndef _BINARY_READER_READER_H_
#define _BINARY_READER_READER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct TradesData
{
	unsigned __int32 type;
	unsigned __int32 time; 
	unsigned __int32 len;
	std::string message;
 };

struct DataFeed
{
	char stockName[9];
	char year[4];
	char month[2];
	char day[2];

	double price;
	double vwap;
	
	unsigned __int32 volume;
	
	double f1;
	double t1;
	double f2;
	double f3;
	double f4;
};

namespace binary_reader
{
	class Reader
	{
	public:
		Reader(const std::string &nameFile);
		virtual ~Reader();

		bool isOpenedFile();
		bool readTradesData(TradesData *tradesData);
		bool readDataFeed(DataFeed *dataFeed);
	
	private:
		std::ifstream inputFile;
	};
}

#endif // _BINARY_READER_READER_H_
