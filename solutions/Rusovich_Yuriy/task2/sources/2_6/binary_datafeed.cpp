#include <reader.h>

#pragma pack(push,1)

struct OutDataFeed
{
	char stockName[9];
    unsigned __int32 date;
    double price;
    unsigned __int32 volume;
    double f2;
};

#pragma pack(pop)

int main()
{
	binary_reader::Reader reader("input.txt");
	std::ofstream outputFile(SOURCE_DIR "/output.txt" );
	
	if (reader.isOpenedFile())
	{
		DataFeed dataFeed;

		while (reader.readDataFeed(&dataFeed))
		{
			OutDataFeed outDataFeed;
			memcpy(&outDataFeed.stockName, &dataFeed.stockName, 9);

			outDataFeed.date = (atoi(dataFeed.year) - 1) * 372
				+ (atoi(dataFeed.month) - 1) * 31
				+ atoi(dataFeed.day);

			outDataFeed.price = dataFeed.vwap;
            outDataFeed.volume = dataFeed.volume;
			outDataFeed.f2 = dataFeed.f2;

			outputFile.write(reinterpret_cast<char*>(&outDataFeed), sizeof(DataFeed));
		}
	}
	outputFile.close();
}

