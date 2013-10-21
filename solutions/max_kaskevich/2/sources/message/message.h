#include <fstream>
#include <stdint.h>


struct message
{
    uint32_t type;
    uint32_t time;
	uint32_t len;
};

std::istream& operator >> (std::istream& input, message& m);
std::ostream& operator << (std::ostream& output, message& m);
