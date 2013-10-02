#include <iostream>
#include <fstream>
#include <string>

int main( int argc, char* argv[] )
{
	std::ofstream output_file( BINARY_DIR "/output_example.txt" );
	output_file << "out put file" << std::endl;
}
