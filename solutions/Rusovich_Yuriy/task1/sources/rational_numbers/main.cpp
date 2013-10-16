#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define accuracy 10000

int main()
{
	std::ifstream inputFile(SOURCE_DIR "/input_rational_numbers.txt");
	std::ofstream outputFile(SOURCE_DIR "/output_rational_numbers.txt" );
	
	int countKey = 0;
	std::string countKeyString;
	std::vector < long long > keys; 

	std::getline(inputFile, countKeyString);
	countKey = atoi(countKeyString.c_str());
	
	for (int i = 0; i < countKey; ++i)
	{
		std::string key;
		if (!inputFile.eof())
		{
			std::getline(inputFile, key);
			keys.push_back((long long)atof(key.c_str()) * accuracy);
		} else 
		{
			break;
		}
	}
	
	while (!inputFile.eof()) 
    {
		std::string passwordString;
		std::getline(inputFile, passwordString);
		
		if (passwordString.empty())
			continue;

		long long password = (long long)atof(passwordString.c_str()) * accuracy;
		
		for (int i = 0; i < countKey; ++i)
		{
			if (password == keys[i])
			{
				outputFile << std::string("YES") << std::endl;
				break;
			} else
			{
				if (i + 1 == countKey)
					outputFile << std::string("NO") << std::endl;
				continue;
			}
		}
	}

	inputFile.close();
	outputFile.close();
    
	system("pause");
	return 0;
}