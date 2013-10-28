#include <iostream>
#include <fstream>
#include "binFileReader.h"

int main(int argc, char** argv) {
	std::cout << "*Homework34*" << std::endl;

	std::string filename = SOURCE_DIR "/sources/34/input.txt";

	binFileReader bfr(filename);

	if (bfr.fileOk) {
		std::cout << "fileok" << std::endl;
	} else {
		std::cout << "fileNOTok" << std::endl;
		return 1;
	}

	dataStruct1_t ds1;

	while(bfr.readDataStruct1(ds1)){
		std::cout << "type" << ds1.type << "\ttime" << ds1.time << "\t["
					<< ds1.msg << "]=" << ds1.len << std::endl;
	}

	std::cout << "---===over===---" << std::endl;
	return 0;
}
