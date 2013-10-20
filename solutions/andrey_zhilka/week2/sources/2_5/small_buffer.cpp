#include "Message.h"
#include <sys/stat.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <map>

typedef std::map< unsigned, std::vector< unsigned > >::iterator map_iterator;

void reading_storingProcess( std::map< unsigned, std::vector< unsigned > > );
void init_new_type( std::map< unsigned, std::vector< unsigned > >&, const Message& );

int main()
{
	std::map< unsigned, std::vector< unsigned > > message_report;
	reading_storingProcess( message_report );
	return 0;
}

void reading_storingProcess( std::map< unsigned, std::vector< unsigned > >& message_report) 
{
	const char *input_file_path = SOURCE_DIR "/tests/2_5/2.5_example.in";
	std::ifstream input_file( input_file_path, std::ios::binary );

	struct stat file_statistics;
	stat( input_file_path, &file_statistics );
	unsigned file_size = file_statistics.st_size;

	unsigned new_message_capacity;
	Message newMessage;

	while ( file_size != 0 ) 
	{
		input_file >> newMessage;

		new_message_capacity = 3 * sizeof( unsigned ) + newMessage.getLength();
		file_size -= new_message_capacity;

		map_iterator existing_statistics = message_report.find( newMessage.getType() );
		
		if ( existing_statistics == message_report.end() )
		{
			init_new_type( message_report, newMessage);
			existing_statistics = message_report.find( newMessage.getType() );
		}
		
		if ( existing_statistics->second[1] == newMessage.getTime()
			&& existing_statistics->second[0] < new_message_capacity ) 
		{
			continue;
		}
		
		if ( existing_statistics->second[1] != newMessage.getTime() )
		{
			existing_statistics->second[0] = 2048;
		}

		existing_statistics->second[0] -= new_message_capacity;
		existing_statistics->second[2]++;
	}
	
}

void init_new_type( std::map< unsigned, std::vector< unsigned > >& message_report,
				   const Message& message)
{
	std::vector< unsigned > message_type_statistics;
	message_type_statistics.push_back( 2048 ); // free spac
	message_type_statistics.push_back( message.getTime() );
	message_type_statistics.push_back( 0 );	// total number

	message_report.insert( std::make_pair(message.getType(), message_type_statistics ) );
}