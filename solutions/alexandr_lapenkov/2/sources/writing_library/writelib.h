#include <string.h>
#include <iostream>
#include <fstream>

class binwriter
{
	std::ofstream out;
	bool error;

public:

	binwriter();
	binwriter(const char *);
	
	void write_unsigned(const unsigned);
	void write_double(const double);
	void write_line(const char *, int = -1);
	void open(const char *);
	void close();
	bool is_open();
	bool good();
};