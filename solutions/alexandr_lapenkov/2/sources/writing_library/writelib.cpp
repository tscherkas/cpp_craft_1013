#include "writelib.h"

binwriter::binwriter(): error(0){}

binwriter::binwriter(const char* filename)
{
	binwriter();
	open(filename);
}

void binwriter::write_line(const char *line, int len)
{
	if(len<0)len = std::strlen(line);
	if(!out.write(line, len))
		error = 1;
}

void binwriter::write_unsigned(const unsigned x)
{
	if(!out.write(reinterpret_cast<const char*>(&x), sizeof(x)))
		error = 1;
}

void binwriter::write_double(const double x)
{
	if(!out.write(reinterpret_cast<const char*>(&x), sizeof(x)))
		error = 1;
}

void binwriter::open(const char *filename)
{
	out.open(filename,std::ios_base::out|std::ios_base::binary);
}

void binwriter::close()
{
	out.close();
}

bool binwriter::is_open()
{
	return out.is_open();
}

bool binwriter::good()
{
	return !error;
}