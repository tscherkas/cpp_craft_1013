#include "binFileReader.h"
#include "binFileWriter.h"
#include <iostream>
#include <fstream>
#include <set>
#include <boost/thread/thread.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <strstream>

uint32_t tmp[] = { 1u, 2u, 3u, 4u };
static const std::set<uint32_t> acceptableOperations(&tmp[0], &tmp[0] + 4);

void processor(const std::string& ifname, const std::string& ofname) {
	binFileReader bfr(ifname);

	if (bfr.fileOk) {
		std::cout << "i fileok" << std::endl;
	} else {
		std::cout << "i fileNOTok" << std::endl;
		return;
	}

	binFileWriter bfw(ofname);
	if (bfw.fileOk) {
		//std::cout << "o fileok" << std::endl;
	} else {
		//std::cout << "o fileNOTok" << std::endl;
		return;
	}

	uint32_t maxTime = 0;
	bool isRecordValid;
	dataStruct1_t ds1;

	while (bfr.readDataStruct(ds1)) {
//		std::cout << "type" << ds1.type << "\ttime" << ds1.time << "\t["
//				<< ds1.msg << "]=" << ds1.len << std::endl;

		isRecordValid = true;

		if ((!acceptableOperations.count(ds1.type)) || (ds1.time + 2 <= maxTime)/* ||
		 (bfr.fileOk) */) {
			isRecordValid = false;
//			std::cout << "FILTERED ";
		}

		if (maxTime < ds1.time) {
			maxTime = ds1.time;
		}

		if (isRecordValid) {
			bfw.writeDataStruct(ds1);
		}
	}
}

void x() {
	std::cout << "x " << std::endl;
}

int main(int argc, char** argv) {
	std::cout << "*Homework34*" << std::endl;

	std::string filenamei = SOURCE_DIR "/sources/34/input.txt";
	std::string filenameo = SOURCE_DIR "/sources/34/output.txt";


    boost::thread_group tg;
	static const size_t maxFileIndex = 999;
	std::stringstream sstr;

	for(size_t i = 0; i < maxFileIndex; i++){
		sstr << SOURCE_DIR "/sources/34/input_" << i << ".txt";
		if(boost::filesystem::exists(sstr.str())){
			filenamei = sstr.str();
			sstr.str("");
			sstr << SOURCE_DIR "/sources/34/output_" << i << ".txt";
			filenameo = sstr.str();
			std::cout << filenamei << "--->" << filenameo << std::endl;
			tg.create_thread( boost::bind(&processor, filenamei, filenameo) );
		}
		sstr.str("");
	}

//	if (boost::filesystem::exists(filenamei)) {
//		std::cout << "input exists" << std::endl;
//	} else {
//		std::cout << "input NOT exists" << std::endl;
//	}

    tg.join_all();
    
    

	std::cout << "---===over===---" << std::endl;
	return 0;
}
