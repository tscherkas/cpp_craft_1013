#include <stdint.h>
#include <fstream>

const static uint32_t max_type = 100000;
const static size_t size_buffer = 2048;

class NetMessage
{
private:
	uint32_t type;
	uint32_t time;
	uint32_t len;
	char *msg;

public:
	NetMessage();
	~NetMessage();
	void set_data(std::ifstream&);
	uint32_t get_type();
	uint32_t get_time();
	uint32_t get_len();
};

class Result
{
private:
	uint32_t type;
	uint32_t count;
	uint32_t time;
public:
	Result();
	~Result();
	void set_result(NetMessage&);
	void get_result(std::ofstream&);
};