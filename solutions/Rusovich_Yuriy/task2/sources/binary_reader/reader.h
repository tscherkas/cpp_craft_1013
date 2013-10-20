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

namespace binary_reader
{
	class Reader
	{
	public:
		Reader(const std::string &nameFile);
		virtual ~Reader();

		bool isOpenedFile();
		bool readTradesData(TradesData *tradesData);
	
	private:
		std::ifstream inputFile;


	};
	void proxy_function_that_was_created_only_for_compiling_goals();
}

#endif // _BINARY_READER_READER_H_
