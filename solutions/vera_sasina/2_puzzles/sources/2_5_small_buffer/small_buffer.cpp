#include "small_buffer.h"
#include <boost/array.hpp>

void NetMessage::set_data(std::ifstream& file)
{
	file.read((char*) &this->type, sizeof(this->type));
	if(this->type > max_type)
		exit(1);
	file.read((char*) &this->time, sizeof(this->time));
	file.read((char*) &this->len, sizeof(this->len));
	if(this->len > 0)
	{
		this->msg = new char [this->len];
		file.read((char*) this->msg, this->len);
		delete [] this->msg;
	}
}

uint32_t NetMessage::get_type()
{
	return this->type;
}
uint32_t NetMessage::get_time()
{
	return this->time;
}
uint32_t NetMessage::get_len()
{
	return this->len;
}
NetMessage::NetMessage() { }
NetMessage::~NetMessage() { }

void Result::set_result(NetMessage &msg)
{
	static boost::array<uint32_t, max_type> current_time = {0};
	static boost::array<uint32_t, max_type> current_buffer = {0};

	this->type = msg.get_type();
	if(msg.get_time()+1 != current_time[this->type])
	{
		this->time++;
		current_buffer[this->type] = 0;
		current_time[this->type] = msg.get_time()+1;
	}
	current_buffer[this->type] += msg.get_len() + sizeof(uint32_t)*3;
	if(current_buffer[this->type] <= size_buffer)
		this->count++;
}

void Result::get_result(std::ofstream &file)
{
	if(this->time > 0)
	{
		double temp;
		temp = static_cast<double>(this->count) / static_cast<double>(this->time);
		file.write((char*) &this->type, sizeof(this->type));
		file.write((char*) &temp, sizeof(temp));
	}
	else
		return;
}

Result::Result() 
{
	this->time = 0; 
	this->count = 0; 
}
Result::~Result() {}