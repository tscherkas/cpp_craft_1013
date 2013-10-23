//#include <cstdint>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator> 

using namespace std;

struct BaseHeader{
    uint32_t type;
    uint32_t time;
    uint32_t len;
};

struct Header: BaseHeader{
    uint64_t offset;
};

const static unsigned short int BUFFER_SIZE = -1; // 65535
const static unsigned short int COPY_BUFFER_SIZE = 255;

const static uint32_t MARKET_OPEN = 1u;
const static uint32_t TRADE = 2u;
const static uint32_t QUOTE = 3u;
const static uint32_t MARKET_CLOSE = 4u;

bool comparator(const Header &item1, const Header &item2){
    return item1.time < item2.time;
}

void buffered_copy(istream &src, ostream &dst, streampos offset, streamoff length){
    static char* copy_buffer = new char[COPY_BUFFER_SIZE];
    src.seekg(offset, ios_base::beg);
    
    // write message
    while(length > COPY_BUFFER_SIZE){
        src.read(copy_buffer, COPY_BUFFER_SIZE);
        dst.write(copy_buffer, COPY_BUFFER_SIZE);
        length -= COPY_BUFFER_SIZE;
    }
    src.read(copy_buffer, length);
    dst.write(copy_buffer, length);
}

bool is_valid(Header &item){
    static uint32_t max_time = 0;
    bool result = false;
    if((item.type == MARKET_OPEN || item.type == TRADE ||
        item.type == QUOTE || item.type == MARKET_CLOSE) &&
       (item.time > (max_time - 2) || max_time < 2)){
        result = true;
    }
    if(max_time < item.time){
        max_time = item.time;
    }
    return result;
}

int main(){
    ifstream i_fs(SOURCE_DIR "/Input.in", ifstream::binary);
    ofstream o_fs(SOURCE_DIR "/Output.bin", ofstream::binary);
    if(!i_fs){
        cout << "Could not open input file" << endl;
        return 1;
    }
    if(!o_fs){
        cout << "Could not open output file" << endl;
        return 1;
    }
    vector<Header> buffer;
    buffer.reserve(BUFFER_SIZE);

    vector<Header>::iterator it = buffer.begin();

    buffer.resize(buffer.size()+1);
    while(i_fs.good() && buffer.size() < BUFFER_SIZE){
        i_fs.read((char *)&(*it), sizeof(BaseHeader));
        (*it).offset = i_fs.tellg();
        // pass data
        i_fs.seekg(it->len, ios_base::cur);

        if(is_valid(*it)){
            it++;
            buffer.resize(buffer.size()+1);
        }
    }
    buffer.resize(buffer.size()-1);

    sort(buffer.begin(), buffer.end(), comparator);

    i_fs.clear();

    for(vector<Header>::iterator it = buffer.begin(); it < buffer.end(); it ++){
        // write header
        o_fs.write((char *)&(*it), sizeof(BaseHeader));
        buffered_copy(i_fs, o_fs, it->offset, it->len);
    } 
    i_fs.close();
    o_fs.close();


    ifstream io_fs(SOURCE_DIR "/Output.bin", ifstream::binary);
    BaseHeader message;
    while(io_fs.good()){
        io_fs.read((char *)&message, sizeof(BaseHeader));
        if(io_fs.fail()){
            break;
        }
        cout << "- type: " << message.type;
        cout << " time: " << message.time;
        cout << " len: " << message.len;
        cout << " data: ";
        buffered_copy(io_fs, cout, io_fs.tellg(), message.len);
        cout << endl;
    }
    return 0;
}