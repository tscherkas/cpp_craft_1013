#include "binFileReader.h"


binFileReader::binFileReader(const std::string& filename):
    fName(filename), fileOk(false){
    ifs.open( filename.c_str(), std::ios::binary | std::ios::in );
    fileOk = ifs.is_open();
}


bool binFileReader::readRawValue(std::string& value, const size_t length){
    if (ifs.eof()){
    	fileOk = false;
        return false;
    } else {
        char* buff = new char[length];
        ifs.read(buff, length);
        value = buff;
        value = value.substr(0, length);
        delete[] buff;
        return true;
    }
}

bool binFileReader::readDataStruct(dataStruct1_t& dataStruct){
    if (ifs.eof()){
    	fileOk = false;
        return false;
    } else {
        readRawValue(dataStruct.type);
        readRawValue(dataStruct.time);
        readRawValue(dataStruct.len);
        bool b = readRawValue(dataStruct.msg, dataStruct.len);

        return b;
    }
}

binFileReader::~binFileReader(){
	ifs.close();
	fileOk = false;
}
