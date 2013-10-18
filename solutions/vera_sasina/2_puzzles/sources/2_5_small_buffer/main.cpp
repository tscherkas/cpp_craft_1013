#include <iostream>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include "small_buffer.h"

int main()
{
	std::ifstream input_file( BINARY_DIR "/input.txt",  std::ios::binary );
	if ( !input_file.is_open() )
		return -1;
	std::ofstream output_file( BINARY_DIR "/output.txt",  std::ios::binary );
	if ( !output_file.is_open() )
		return -1;
	{
		boost::shared_ptr<NetMessage> net_data(new NetMessage());
		boost::shared_array<Result> results(new Result [max_type]);

		while(!input_file.eof())
		{
			net_data->set_data(input_file);
			results[net_data->get_type()-1].set_result(*net_data);
		}

		for(uint32_t i; i < max_type; i++)
		{
			results[i].get_result(output_file);
		}
	}
	input_file.close();
	output_file.close();
	return 0;
}