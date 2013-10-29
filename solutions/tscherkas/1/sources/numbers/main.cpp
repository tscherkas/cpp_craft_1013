#include <iostream>
#include <fstream>
#include <list>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>




int main( int argc, char* argv[] )
{
	std::ifstream input_file( SOURCE_DIR "/tests/numbers/input.txt" );
	if(!input_file.is_open())
		return 0;
	std::ofstream output_file("output.txt" );
	if(!output_file.is_open())
		return 0;
	std::list <double> mas_keys, mas_pass;
	int number_of_keys;
	if( !input_file.eof() )
	{
		std::string readed_string;
		std::getline( input_file, readed_string);
		number_of_keys = atoi(readed_string.c_str());
	}
	for(int i = 0; i < number_of_keys&&!input_file.eof() ; i++)
	{	
		std::string readed_string;
		std::getline( input_file, readed_string);
		if(readed_string.empty())
			continue;
		mas_keys.push_back(
			atof( readed_string.c_str() )
			);
	}
    	while( !input_file.eof() )
	{
		std::string readed_string;
		std::getline( input_file, readed_string);
		if(readed_string.empty())
			continue;
		mas_pass.push_back(
			atof( readed_string.c_str() )
			);
	}
	for(
		std::list<double>::iterator pass_it = mas_pass.begin();
		pass_it != mas_pass.end();
		pass_it++
	)
	{
		bool check = false;
		for(	
			std::list<double>::iterator key_it = mas_keys.begin();
			key_it != mas_keys.end();
			key_it ++
		)
		{
		        uint64_t var1, var2;
			double buf_p = (*pass_it)*10000;
			double buf_k = (*key_it)*10000;
			var1 = buf_p;
			var2 = buf_k;
			if( var1 == var2)
			{
				
				check = true;
				break;
			}
		}		
		check ?	output_file << "YES" << std::endl : output_file << "NO" << std::endl;
				
	}
	std::cout<<sizeof(long long int);
	input_file.close();
	output_file.close();
}
