#include <string.h>
#include <iostream>
#include <fstream>

class binreader
{
	std::ifstream in;
	bool error;

public:

	binreader();
	binreader(const char *);
	
	char get_char();
	unsigned get_unsigned();
	std::string get_line(int);
	double get_double();
	bool good();
	void open(const char *);
	void close();
	bool is_open();
};
