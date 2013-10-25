#include <iostream>
#include <fstream>
#include "binFileRW.h"

int main(int argc, char** argv) {
	std::cout << "*Homework34*" << std::endl;

	std::string filename = SOURCE_DIR "/sources/34/input.txt";

	binFileRW brr(filename);
	if (brr.fileGood) {
		std::cout << "file opened" << std::endl;
	} else {
		std::cout << "file NOT opened" << std::endl;
	}

	dataStruct1_t ds1;
	while (brr.readValue(ds1)) {
		std::cout << "\ttp" << ds1.type << "\ttm" << ds1.time
				<< "\tln" << ds1.len << "\tms[" << ds1.msg << "]" << std::endl;
	}

	std::cout << "---===over===---" << std::endl;
	return 0;
}
