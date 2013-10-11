#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main( int argc, char* argv[] )
{
	//open files for read and write
	ifstream input_file( "input.txt" );
	ofstream output_file( "output.txt" );
	int count_array, pos;
	input_file >> count_array;	// read size of array
	if(count_array < 1)
		return 0;
	vector<float>array_numb;	// vector for rational numbers
	float num;					// temp variables
	bool check;
	string line;

	//read values of array
	for(; array_numb.size() < count_array; )
	{
		getline( input_file, line );		//read line from file
		if(line.empty())					//skipp emty line
			continue;
		pos = line.find('.');				//set the precision
		if(line.size() > pos+5)
			line.erase(pos+5);	
		num = stod(line, string::size_type());
		array_numb.push_back(num);
	}
	//read passwords for array from file
	for( ; !input_file.eof(); )
	{
		getline( input_file, line );		//read line from file
		if(line.empty())					//skipp emty line
			continue;
		pos = line.find('.');				//set the precision
		if(line.size() > pos+5)
			line.erase(pos+5);	
		num = stod(line, string::size_type());

		array_numb.begin();					//go to begin of array
		//comparison of numbers and passwords
		for(int i = 0; i < count_array; i++)
		{
			if(array_numb.at(i) == num)
			{
				check = true;
				break;
			}
			else
				check = false;
		}
		//output to file
		if(check)
			output_file << "YES" << endl;
		else
			output_file << "NO" << endl;
		
	}
	//close of files
	input_file.close();
	output_file.close();
	return 0;
}
