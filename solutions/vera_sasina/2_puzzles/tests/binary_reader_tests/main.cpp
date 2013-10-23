#include <reader.h>

#include <iostream>
#include <fstream>

#define test_no_throw( action ) \
{ \
	try \
	{ \
		action; \
	} \
	catch( ... ) \
	{ \
		std::cout << "test_no_throw failed: " <<  __FILE__ << ":" << __LINE__ << std::endl; \
	} \
} \


int main()
{
	std::ifstream file( BINARY_DIR "/input.txt",  std::ios::binary|std::ios::ate );
	if ( !file.is_open() )
		return -1;
	binary_reader::Data net_data;

	test_no_throw( binary_reader::read_bin_file(std::ifstream& file, Data &data; );
	file.close();
	return 0;
}