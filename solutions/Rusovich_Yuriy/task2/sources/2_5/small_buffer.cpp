#include <reader.h>
#include <map>

const static int needTypes = 100000;

int main()
{
	binary_reader::Reader reader("input.txt");
	std::ofstream outputFile(SOURCE_DIR "/output.txt" );
	
	unsigned __int32 commonCountTime = 1;
	std::map <unsigned __int32, unsigned __int32> countOfType;
	std::map <unsigned __int32, unsigned __int32>::iterator it;
	unsigned __int32 currentTime = 0;
	
	if (reader.isOpenedFile())
	{
		TradesData tradesData;
		bool isFirst = true;
		while (reader.readTradesData(&tradesData))
		{
			if (tradesData.type > needTypes)
				continue;

			if (isFirst)
			{
				currentTime = tradesData.time;
				isFirst = false;
			}

			if (tradesData.time != currentTime)
			{
				++commonCountTime;
				currentTime = tradesData.time;
			}

			if ((it = countOfType.find(tradesData.type)) == countOfType.end())
				countOfType.insert(std::pair<unsigned __int32, unsigned __int32>(tradesData.type, 1));
			else
				++it->second;
		}
		for (it = countOfType.begin(); it != countOfType.end(); ++it)
		{
			unsigned __int32 type = it->first;
			outputFile.write(reinterpret_cast<char*>(&type), sizeof(unsigned __int32));
			double mean = (double)it->second/commonCountTime;
			outputFile.write(reinterpret_cast<char*>(&mean), sizeof(unsigned __int32));
			//outputFile << type << mean << std::endl;
		}
	}
	outputFile.close();
}

