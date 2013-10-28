#include "binFileReader.h"


binFileReader::binFileReader(const std::string& filename):
    fName(filename), fileOk(false){
    ifs.open( filename.c_std(), std::ios::binary | std::ios::in );
}


bool binFileReader::readRawValue(std::string& value, const size_t length){
    if (ifs.is_eof()){
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


bool binFileReader::readDataStruct1(dataStruct1_t& dataStruct){
    if (ifs.is_eof()){
        return false;
    } else {
        readRawValue(dataStruct.type);
        readRawValue(dataStruct.time);
        readRawValue(dataStruct.len);
        readRawValue(dataStruct.msg, dataStruct.len);

        return true;
    }
}
