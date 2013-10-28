#ifndef BINFILEWRITER_INCLUDED
#define BINFILEWRITER_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>
#include "dataStructs.h"

class binFileWriter{
private:
    std::string fName;
    std::fstream ofs;

    binFileWriter(const binFileWriter& that);
    binFileWriter operator=(const binFileWriter& that);

public:
    binFileWriter(const std::string& filename);
    ~binFileWriter();
    bool fileOk;

    template<class T>
    void writeRawValue(T& value);
    void writeRawValue(std::string& value, const size_t length);

    void writeDataStruct1(dataStruct1_t& dataStruct);
};


template<class T>
void binFileWriter::writeRawValue(T& value){
   ofs.write( (char*)value, sizeof value);
}


#endif
