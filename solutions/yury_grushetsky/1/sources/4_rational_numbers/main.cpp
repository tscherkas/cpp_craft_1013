#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
#define PRECISION 1E-4

bool mycomp(float v1, float v2)
{
	return v2-v1>PRECISION;
}

int main( int argc, char* argv[] )
{
	ifstream input_file( SOURCE_DIR "/tests/4_rational_numbers/input.txt" );
	ofstream output_file( "output.txt");
	int N;
	input_file >> N;
	vector<float> codes (N);
	for(vector<float>::iterator it = codes.begin(); it!=codes.end(); ++it)
		input_file >> *it;
	sort(codes.begin(), codes.end());
	float curval;
	while( !input_file.eof() )
	{
		input_file >> curval;
		cout << curval << endl;
		//TODO check error flags to handle \n in the end of file
		if( binary_search(codes.begin(), codes.end(), curval, mycomp))
			output_file << "YES" << endl;
		else
			output_file << "NO" << endl;
	}
	input_file.close();
	output_file.close();
}
