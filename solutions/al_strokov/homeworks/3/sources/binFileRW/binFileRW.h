#ifndef BINFILERW_INCLUDED
#define BINFILERW_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>

struct dataStruct1_t{
	uint32_t type;
	uint32_t time;
	uint32_t len;
	std::string msg;
};

#endif
