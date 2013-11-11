#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct symbols_to_remove
{
	bool operator() (char c) 
	{ 
		return (c=='\\'||c==' '||c=='-'); 
	}
};

int main( int argc, char* argv[] )
{
	std::ifstream input_file( SOURCE_DIR "/tests/strings/input.txt" );
	if(!input_file.is_open())
		return 0;
	std::ofstream output_file("output.txt" );
	if(!output_file.is_open())
		return 0;
	std::string original_text, key, original_text_transformed, key_transformed;
	if( !input_file.eof() )
	{
		std::getline( input_file, original_text );
		original_text_transformed.resize(original_text.size());
		std::transform(original_text.begin(),
			original_text.end(),
			original_text_transformed.begin(),
			::tolower);
		std::string::iterator e = std::remove_if(original_text_transformed.begin(),
			original_text_transformed.end(),
			symbols_to_remove());
		original_text_transformed.resize(e-original_text_transformed.begin());
	}
    while( !input_file.eof() )
	{
		std::getline( input_file, key );
		if(!key.empty())
		{
			key_transformed.resize(key.size());
			std::transform(key.begin(),
                        	key.end(),
                        	key_transformed.begin(),
                        	::tolower);  		
			std::string::iterator e = std::remove_if(key_transformed.begin(),
				key_transformed.end(), symbols_to_remove());
			key_transformed.resize(e-key_transformed.begin());
			std::reverse(key_transformed.begin(),
				key_transformed.end());
			std::string::iterator it = std::search(original_text_transformed.begin(),
				original_text_transformed.end(),
				key_transformed.begin(),
				key_transformed.end());
			if(it==original_text_transformed.end())
				output_file << "NO"  << std::endl;
			else
				output_file << "YES"  << std::endl;
		
		}
	}
	input_file.close();
	output_file.close();
}
