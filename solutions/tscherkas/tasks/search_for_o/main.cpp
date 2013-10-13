#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>




int main( int argc, char* argv[] )
{
	std::ifstream input_file( "input.txt" );
	std::string original_text, key;
	std::ofstream output_file("output.txt" );
		char O = '0';

std::string virt_ocean((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
	std::cout<<virt_ocean.c_str();
	std::string::iterator beg_oc_iter = virt_ocean.begin(), end_oc_iter = virt_ocean.end();
	int o_counter=0;
	int base_width = virt_ocean.find('\n')+1;
	std::list<std::string::iterator> o_neighbor; 
	for(std::string::iterator it = beg_oc_iter; it != end_oc_iter; )
	{
		if(o_neighbor.empty())
		{
			it = beg_oc_iter;
			while (it != end_oc_iter && *it != 'o')
				it++;
			if(it==end_oc_iter)
				break;
			else
			{
				beg_oc_iter = it+1;
				*it = ++O;
				o_counter++;
			}
		}
		else
		{
			it = o_neighbor.front(); 
			o_neighbor.pop_front();
		}
		if ( it+1 != end_oc_iter && *(it+1)=='o')
		{
			o_neighbor.push_back(it+1);
			*(it+1)=O;
		}
		if ( it != beg_oc_iter && *(it-1)=='o')
		{
			o_neighbor.push_back(it-1);
			*(it-1) = O;
		}
		if ( it+base_width != end_oc_iter && *(it + base_width)=='o')
		{
			o_neighbor.push_back(it + base_width);
			*(it+base_width) = O;
		}
		if ( it-virt_ocean.begin() > base_width && *(it - base_width)=='o')
		{
			o_neighbor.push_back(it-base_width);
			*(it-base_width) = O;
		}
	}
	std::cout << virt_ocean.c_str() << std::endl;
	output_file << o_counter;
	input_file.close();
	output_file.close();
}
