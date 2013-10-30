#include "binFileWriter.h"


binFileWriter::binFileWriter(const std::string& filename):
    fName(filename), fileOk(false){
    ofs.open( filename.c_str(), std::ios::binary | std::ios::out );
    fileOk = ofs.is_open();
}


void binFileWriter::writeRawValue(const std::string& value, const size_t length){
	ofs.write( value.c_str() , length);
}


void binFileWriter::writeDataStruct(const dataStruct1_t& dataStruct){
	writeRawValue(dataStruct.type);
	writeRawValue(dataStruct.time);
	writeRawValue(dataStruct.len);
	writeRawValue(dataStruct.msg, dataStruct.len);
}

binFileWriter::~binFileWriter(){
	ofs.close();
	fileOk = false;
}
