#include "Message.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

void filterMessages(std::istream*);

static const size_t max_file_number = 999;

int main()
{
	boost::thread_group filters;
	std::stringstream strim;
	for ( size_t i = 0; i < max_file_number; i++ )
	{
		strim.width( 3 );
		strim << std::setfill( '0' );
		strim << i;
		
		std::string number;
		strim >> number;

		char input_file_path[] = SOURCE_DIR "/tests/2_4/input_";
		strcat( input_file_path, number.c_str() );
		strcat( input_file_path, ".txt");

		boost::filesystem2::path next_file(input_file_path);

		if ( boost::filesystem2::exists( next_file ) )
		{
			std::ifstream input( input_file_path, std::ios::in | std::ios::binary );
			filters.add_thread( new boost::thread( &filterMessages, &input ) );
		}
		else 
		{
			break;
		}

		filters.join_all();
		

		strim.clear();
	}

	return 0;
}

void filterMessages(std::istream* input) {
	unsigned maxT = 0;
	
	Message new_message;
	std::ofstream output;

	while ( true ) {
		*input >> new_message;

		if ( input->eof() )
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
}