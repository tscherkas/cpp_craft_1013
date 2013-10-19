#ifndef _BINARY_READER_READER_H_
#define _BINARY_READER_READER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>


namespace binary_reader
{
	typedef struct stock_ex_dat
	{
		uint32_t TYPE;
		uint32_t TIME; 
		uint32_t LEN;
		std::string MSG;
	} stock_ex_dat;

	int read_binary();
}

#endif // _BINARY_READER_READER_H_
