#include <iostream>
#include <boost/shared_ptr.hpp>
#include "trades_filter.h"

int main()
{
	std::ifstream input_file( BINARY_DIR "/input.txt", std::ios::binary|std::ios::ate );
	if ( !input_file.is_open() )
		return -1;
	std::ofstream output_file( BINARY_DIR "/output.txt", std::ios::binary );
	if ( !output_file.is_open() )
		return -1;
	size_t file_size;
	file_size = static_cast<size_t>(input_file.tellg());
	input_file.seekg (0, std::ios::beg);
	{
		size_t read_size = 0;
		boost::shared_ptr<Trades> data(new Trades());

		while(read_size < file_size)
		{
			data->set_trade(input_file);
			read_size = static_cast<size_t>(input_file.tellg());
			data->get_trade(output_file);
		}
	}
	input_file.close();
	output_file.close();
	return 0;
}
