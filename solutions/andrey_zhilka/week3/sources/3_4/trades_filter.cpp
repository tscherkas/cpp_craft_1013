#include "Message.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

void filterMessages(const std::ifstream&);

static const size_t max_file_number = 999;

int main()
{
	boost::thread_group filters;
	std::ostringstream strim;
	for ( size_t i = 0; i < max_file_number; i++ )
	{
		strim << std::setfill('0') << std::ios::width(3);
		strim << i;
		
		const char *input_file_path = SOURCE_DIR "/tests/2_4/input_" strim.str().c_str() ".txt";

		boost::filesystem2::path next_file(input_file_path);

		if ( boost::filesystem2::exists( next_file ) )
		{

		}
		else 
		{
			break;
		}

		strim.clear();
	}
	
	filterMessages();

	return 0;
}

void filterMessages(const std::ifstream& input) {
	unsigned maxT = 0;
	
	Message new_message;

	while ( true ) {
		input >> new_message;

		if ( input.eof() )
		{
			break;
		}

		if ( !new_message.isOk() )
		{
			continue;
		}

		if ( maxT < 2 || new_message.getTime() > maxT - 2 ) {
			output << new_message;
			maxT = ( maxT < new_message.getTime() ) ? new_message.getTime() : maxT;
		}
	}

	input.close();
	output.close();
}