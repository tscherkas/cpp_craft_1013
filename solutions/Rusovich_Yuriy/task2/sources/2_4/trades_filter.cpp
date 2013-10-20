#include <reader.h>

const static int needTypes = 4;

int main()
{
	binary_reader::Reader reader("input.txt");
	std::ofstream outputFile(SOURCE_DIR "/output.txt" );
	
	unsigned __int32 currentTime = 0;

	if (reader.isOpenedFile())
	{
		TradesData tradesData;

		while (reader.readTradesData(&tradesData))
		{
			if (tradesData.type > needTypes)
				continue;

			if (tradesData.time + 2 > currentTime || currentTime < tradesData.time)
			{
				if (outputFile)
				{
					outputFile.write(reinterpret_cast<char*>(&tradesData.type), sizeof(unsigned __int32));
					outputFile.write(reinterpret_cast<char*>(&tradesData.time), sizeof(unsigned __int32));
					outputFile.write(reinterpret_cast<char*>(&tradesData.len), sizeof(unsigned __int32));
					outputFile.write(tradesData.message.c_str(), tradesData.len * sizeof(char));
/*
					outputFile << tradesData.type << std::endl;
					outputFile << tradesData.time << std::endl;
					outputFile << tradesData.len << std::endl;
					outputFile << tradesData.message << std::endl;*/
				}
			}
			if (currentTime < tradesData.time)
				currentTime = tradesData.time;

			
		}
	}

	outputFile.close();
}

