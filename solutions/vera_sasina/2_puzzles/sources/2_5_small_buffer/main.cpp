#include <iostream>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include "small_buffer.h"

int main()
{
	std::ifstream input_file( BINARY_DIR "/input.txt",  std::ios::binary|std::ios::ate );
	if ( !input_file.is_open() )
		return -1;
	std::ofstream output_file( BINARY_DIR "/output.txt",  std::ios::binary );
	if ( !output_file.is_open() )
		return -1;
	size_t file_size;
	file_size = static_cast<size_t>(input_file.tellg());
	input_file.seekg (0, std::ios::beg);
	{
		boost::shared_ptr<NetMessage> net_data(new NetMessage());
		boost::shared_array<Result> results(new Result [max_type]);
		size_t read_size = 0;
		while(read_size < file_size)
		{
			net_data->set_data(input_file);
			read_size = static_cast<size_t>(input_file.tellg());
			results[net_data->get_type()-1].set_result(*net_data);
		}
		
		for(uint32_t i = 0; i < max_type; i++)
		{
			results[i].get_result(output_file);
		}
	}
	input_file.close();
	output_file.close();
	return 0;
}