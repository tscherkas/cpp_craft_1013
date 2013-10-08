#include <iostream>
#include <ctype.h>
#include <fstream>
#include <string>
#include <algorithm> 


int main()
{
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");

	std::string polindrom;
	while(!in.eof())
	{
		std::getline(in, polindrom);
		polindrom.erase(std::remove_if(polindrom.begin(), polindrom.end(), [](char a){return a == ' ';}), polindrom.end());
		//for (std::string::size_type i = 0; i < polindrom.length(); ++i)
		//{
		//	char c = toupper(polindrom.at(i));
		//	polindrom[i] = toupper(polindrom[i]);
		//}
		std::transform(polindrom.begin(), polindrom.end(), polindrom.begin(), toupper);
	}
}