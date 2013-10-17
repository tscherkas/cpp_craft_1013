#include <stdint.h>
#include <fstream>

class Trades
{
private:
	uint32_t type;
	uint32_t time;
	uint32_t len;
	char *msg;

public:
	Trades() {};
	~Trades() {};
	void set_trade(std::ifstream&);
	void get_trade(std::ofstream&);
};