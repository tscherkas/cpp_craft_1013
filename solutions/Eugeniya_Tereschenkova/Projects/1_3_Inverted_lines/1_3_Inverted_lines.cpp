// 1_3_Inverted_lines.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <algorithm>
using namespace std;

bool isSpaceSymb(const char& symb)
{
	switch(symb)
	{
	case ' ':
	case '-':
	case '\\':
		return 1;
	default:
		return 0;
	}
}

void formatting_line(ifstream& stream, string& line)
{
	getline(stream, line);
	if(line.empty())
		return;
	line.erase(remove_if(line.begin(), line.end(), isSpaceSymb), line.end());
	transform(line.begin(), line.end(), line.begin(), tolower);
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	ifstream input_file( "Input.txt" );
	ofstream output_file( "Output.txt" );
	string line, key;

	if(!input_file.eof())
		formatting_line(input_file, line);

	while(!input_file.eof())
	{
		formatting_line(input_file, key);
		if(key.empty())
			continue;
		reverse(key.begin(), key.end());
		if (line.find(key) != string::npos)
			output_file << "YES" << endl;
		else
			output_file << "NO" << endl;
	}

	input_file.close();
	output_file.close();
	
	return 0;
}
