#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
typedef unsigned long long ull;

int main( int argc, char* argv[] )
{
	ifstream input_file( BINARY_DIR "/input.txt" );
	ofstream output_file( BINARY_DIR "/output.txt" );
	int size_array, pos;
	input_file >> size_array;	// read size of array
	if(size_array < 1)
		return 0;
	vector<ull>array_numb;	// vector for rational numbers
	double num;					// temp variables
	ull temp;
	bool check;

	//read values of array
	for(int i = 0; i < size_array; i++)
	{	
		input_file >> num;
		temp = num*10000;
		array_numb.push_back(temp);
	}
	//read passwords for array from file
	while(!input_file.eof())
	{
		input_file >> num;
		for(vector<ull>::iterator it = array_numb.begin(); it != array_numb.end(); it++)
		{
			temp = num*10000;
			check = *it == temp;
			if(check)
				break;
		}

		if(check)
			output_file << "YES" << endl;
		else
			output_file << "NO" << endl;
		
	}
	input_file.close();
	output_file.close();
	return 0;
}
