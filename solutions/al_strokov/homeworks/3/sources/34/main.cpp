#include "binFileReader.h"
#include "binFileWriter.h"
#include <iostream>
#include <fstream>
#include <set>
//#include <boost/thread/thread.hpp>


uint32_t tmp[] = {1u, 2u, 3u, 4u};
static const std::set<uint32_t> acceptableOperations(&tmp[0], &tmp[0]+ 4);

void processor(const std::string& ifname, const std::string& ofname){
	binFileReader bfr(ifname);

	if (bfr.fileOk) {
		std::cout << "i fileok" << std::endl;
	} else {
		std::cout << "i fileNOTok" << std::endl;
		return;
	}

    binFileWriter bfw(ofname);
	if (bfw.fileOk) {
		std::cout << "o fileok" << std::endl;
	} else {
		std::cout << "o fileNOTok" << std::endl;
		return;
	}

	uint32_t maxTime = 0;
	bool isRecordValid;
	dataStruct1_t ds1;

	while(bfr.readDataStruct1(ds1)){
		std::cout << "type" << ds1.type << "\ttime" << ds1.time << "\t["
					<< ds1.msg << "]=" << ds1.len << std::endl;

		isRecordValid = true;

		if ( (!acceptableOperations.count(ds1.type)) ||
				(ds1.time + 2 <= maxTime)/* ||
				(bfr.fileOk) */){
			isRecordValid = false;
			std::cout << "FILTERED ";
		}

		if ( maxTime < ds1.time ){
			maxTime = ds1.time;
		}
        
        if (isRecordValid){
            bfw.write(ds1);
            std::cout << "//writed //" << ds1.msg << std::endl;
        }
	}
}

int main(int argc, char** argv) {
	std::cout << "*Homework34*" << std::endl;

	std::string filename = SOURCE_DIR "/sources/34/input.txt";

    processor(filename,SOURCE_DIR "/sources/34/output.txt");

	std::cout << "---===over===---" << std::endl;
	return 0;
}
