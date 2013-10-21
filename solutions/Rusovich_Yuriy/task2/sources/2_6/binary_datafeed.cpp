#include <reader.h>

int main()
{
	binary_reader::Reader reader("input.txt");
	std::ofstream outputFile(SOURCE_DIR "/output.txt" );
	
	if (reader.isOpenedFile())
	{
		DataFeed dataFeed;

		while (reader.readDataFeed(&dataFeed))
		{

			int y = 0;
			
		}
	}

	outputFile.close();
}

