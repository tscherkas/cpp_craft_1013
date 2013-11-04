#include "b_message.h"

#include <sstream>

task4_4::b_message::b_message( std::istream& inp )
{
	inp.seekg(0, inp.beg);

	inp >> length_;
	if(inp.eof()){
		throw std::logic_error("bad input stream, a_message cannot be readed");
	}

	content_ = new char[ length_ ];
	inp.read( content_, length_ );
	std::cout << "readed [" << inp.gcount() << "]charz; need lenght:" << length_ << "str:"<< content_ << std::endl;
	if(inp.gcount() < length_){
		throw std::logic_error("bad input stream, not enough data");
	}
}

task4_4::message_ptr task4_4::b_message::create_message( std::istream& inp )
{
	return message_ptr( new b_message( inp ) );
}

task4_4::b_message::~b_message()
{
	delete [] content_;
}

const char task4_4::b_message::type() const
{
	return 'B';
}
const std::string task4_4::b_message::str() const
{
	//b_message(16|0123456789123456)
	std::stringstream sBuff;
	sBuff << "b_message(" << length_ << "|" << std::string(content_, length_) << ")";
	std::cout << sBuff.str() << std::endl;
	return sBuff.str();
}
