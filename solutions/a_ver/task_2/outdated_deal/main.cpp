//#include <cstdint>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

struct MessageHeader{
    uint32_t type;
    uint32_t time;
    uint32_t len;
};

const static uint32_t MARKET_OPEN = 1u;
const static uint32_t TRADE = 2u;
const static uint32_t QUOTE = 3u;
const static uint32_t MARKET_CLOSE = 4u;

const static unsigned short int BUFFER_SIZE = -1; // 65535

void buffered_copy(istream &src, ostream &dst, streampos offset, streamoff length){
    static char* copy_buffer = new char[BUFFER_SIZE];
    //static unique_ptr<char[]> copy_buffer(new char[BUFFER_SIZE]);
    src.seekg(offset, ios_base::beg);
    
    // write message
    while(length > BUFFER_SIZE){
        src.read(copy_buffer, BUFFER_SIZE);
        dst.write(copy_buffer, BUFFER_SIZE);
        length -= BUFFER_SIZE;
    }
    src.read(copy_buffer, length);
    dst.write(copy_buffer, length);
}

bool is_valid(MessageHeader &item){
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
    MessageHeader m_header;

    while(i_fs.good()){
        i_fs.read((char *)&m_header, sizeof(MessageHeader));
        if(i_fs.fail()){
            break;
        }
        if(!is_valid(m_header)){
            i_fs.seekg(m_header.len, ios_base::cur);
            continue;
        }
        o_fs.write((char *)&m_header, sizeof(MessageHeader));
        buffered_copy(i_fs, o_fs, i_fs.tellg(), m_header.len);
    }
    i_fs.close();
    o_fs.close();

    // print result data
    i_fs.open(SOURCE_DIR "/Output.bin", ifstream::binary);
    while(i_fs.good()){
        i_fs.read((char *)&m_header, sizeof(MessageHeader));
        if(i_fs.fail()){
            break;
        }
        cout << "- type: " << m_header.type;
        cout << " time: " << m_header.time;
        cout << " len: " << m_header.len;
        cout << " data: ";
        buffered_copy(i_fs, cout, i_fs.tellg(), m_header.len);
        cout << endl;
    }
    i_fs.close();
    return 0;
}