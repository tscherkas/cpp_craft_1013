#include <iostream>
#include <boost/shared_ptr.hpp>
#include "trades_filter.h"

int main()
{
	std::ifstream input_file( BINARY_DIR "/input.txt", std::ios::binary );
	if ( !input_file.is_open() )
		return -1;
	std::ofstream output_file( BINARY_DIR "/output.txt", std::ios::binary );
	if ( !output_file.is_open() )
		return -1;
	{
		boost::shared_ptr<Trades> data(new Trades());

		while(!input_file.eof())
		{
			data->set_trade(input_file);
			data->get_trade(output_file);
		}
	}
	input_file.close();
	output_file.close();
	return 0;
}
