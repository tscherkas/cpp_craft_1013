#include "trades_filter.h"

void Trades::set_trade(std::ifstream& file)
{
	file.read((char*) &this->type, sizeof(this->type));
	file.read((char*) &this->time, sizeof(this->time));
	file.read((char*) &this->len, sizeof(this->len));
	if(this->len > 0)
	{
		this->msg = new char [this->len];
		file.read((char*) this->msg, this->len);
	}
}

void Trades::get_trade(std::ofstream &file)
{
	if(this->type > 4)
		return;
	static uint32_t maxTime = 0;
	if((this->time+2) <= maxTime)
		return;
	if(this->time > maxTime)
		maxTime = this->time;

	file.write((char*) &this->type, sizeof(this->type));
	file.write((char*) &this->time, sizeof(this->time));
	file.write((char*) &this->len, sizeof(this->len));
	file.write((char*) this->msg, this->len);
	delete [] msg;
}