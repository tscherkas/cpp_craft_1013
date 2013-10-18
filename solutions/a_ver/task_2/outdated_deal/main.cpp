//#include <cstdint>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Header{
    uint32_t type;
    uint32_t time;
    uint32_t len;
};

const static unsigned short int BUFFER_SIZE = -1; // 65535

// /usr/bin/time "\t%M Kb - Max. resident\t%K Kb - Avg. total memory" 

bool comparator(const Header* item1, const Header* item2){
    return item1->time < item2->time;
}

int main(){
    ifstream i_fs(SOURCE_DIR "/Input.in");
    if(!i_fs){
        cout << "Could not open input file" << endl;
        return 1;
    }

    vector<Header*> buffer;
    
    while(!i_fs.eof() && i_fs.good()){
        Header* msg_header = new Header();
        i_fs.read((char *)msg_header, sizeof(Header));

        if(i_fs.good()){
            buffer.push_back(msg_header);
            i_fs.seekg(msg_header->len, ios_base::cur);
        }
    }
    sort(buffer.begin(), buffer.end(), comparator);

    for(vector<Header*>::iterator it = buffer.begin(); it < buffer.end(); it ++){
        delete *it;
    }

    i_fs.close();
    return 0;
}