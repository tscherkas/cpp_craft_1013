/*
 * Realization with sorting
 *
 * Used two buffers: one for performing quick sort of partial data,
 * second for performing merge sort data obtained in step of quick sort.
 *
 * 1. Read data to buffer for quick sort
 * 2. When buffer is full - perform quick sort. Then flushing data from
 *    buffer into temporary file and remember offset
 * 3. After reading all data from input file perform merge sort with
 *    copy data from original input to result output file
 */
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator> 

using namespace std;

typedef unsigned short int chunk_size_t;

// Original header of message
struct MessageHeader{
    uint32_t type;
    uint32_t time;
    uint32_t len;
};

struct MetaHeader: MessageHeader{
    uint64_t offset;
};

struct Chunk{
    uint64_t offset;
    chunk_size_t count;
};

const chunk_size_t QSORT_BUFFER_SIZE = -1; // 65535
const static unsigned short int COPY_BUFFER_SIZE = 255;

const static uint32_t MARKET_OPEN = 1u;
const static uint32_t TRADE = 2u;
const static uint32_t QUOTE = 3u;
const static uint32_t MARKET_CLOSE = 4u;

bool comparator(const MetaHeader &item1, const MetaHeader &item2){
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

void flush_buffer(vector<Header> &buffer, ofstream &o_fs){
    for(vector<Header>::iterator it = buffer.begin(); it < buffer.end(); it ++){
        o_fs.write((char *)&(*it), sizeof(Header));
    }
    buffer.resize(0);
}

void merge_by_one(fstream &i_fs, fstream &o_fs, Chunk &first, Chunk &second){
    MetaHeader item_first, item_second;
    chunk_size_t first_number = first.count;
    chunk_size_t second_number = second.count;

    i_fs.clear();
    o_fs.clear();

    i_fs.seekg(first.offset);
    i_fs.read((char *)&item_first, sizeof(MetaHeader))

    i_fs.seekg(second.offset);
    i_fs.read((char *)&item_second, sizeof(MetaHeader))

    while(first_number < first.count && second_number > second_count){
        if(comparator(item_first, item_second)){
            o_fs.write((char *)&item_first, sizeof(MetaHeader));

            i_fs.seekg(first.offset + first_number * sizeof(MetaHeader));
            i_fs.read((char *)&item_first, sizeof(MetaHeader));
            first_number++;
        }else{
            o_fs.write((char *)&item_second, sizeof(MetaHeader));

            i_fs.seekg(second.offset + second_number * sizeof(MetaHeader));
            i_fs.read((char *)&item_second, sizeof(MetaHeader));
            second_number++;
        }
    }
    if(first_number > 0){
        buffered_copy(
            i_fs, o_fs,
            first.offset + first_number * sizeof(MetaHeader),
            first.count * sizeof(MetaHeader))
    }
    if(second_number > 0){
        buffered_copy(
            i_fs, o_fs,
            second.offset + second_number * sizeof(MetaHeader),
            second.count * sizeof(MetaHeader))
    }
}

void merge_bulk(fstream &i_fs, fstream &o_fs, Chunk &first, Chunk &second){
    // to read with buffering more than one elements
}

void merge_sort(fstream &i_fs, queue<Chunk> &msort_queue){
    Chunk &first;
    Chunk &second;
    size_t size = msort_queue.size();
    fstream o_fs(SOURCE_DIR "/Temporary2.bin";);

    while(msort_queue.size() < 2){
        i_fs.open(tmp_file1);
        o_fs.open(tmp_file2);

        first = msort_queue.front();
        msort_queue.pop();
        second = msort_queue.front();
        msort_queue.pop();

        merge(i_fs, first, second);
        msort_queue.push(Chunk(first.offset, first.count + second.count));
        if(size == 0){
            size = msort_queue.size();
            i_fs.swap(o_fs);
        }
        size--;
    }
    i_fs.swap(o_fs);
    o_fs.close();
}

int main(){
    ifstream i_fs(SOURCE_DIR "/Input.in", ifstream::binary);
    ofstream o_fs(SOURCE_DIR "/Output.bin", ofstream::binary);
  
    fstream io_fs(SOURCE_DIR "/Temporary.in", ifstream::binary);

    if(!i_fs){
        cout << "Could not open input file" << endl;
        return 1;
    }
    if(!o_fs){
        cout << "Could not open output file" << endl;
        return 1;
    }
    if(!io_fs){
        cout << "Could not open temporary file" << endl;
        return 1;
    }

    vector<MetaHeader> qsort_buffer;
    queue<Chunk> msort_queue;

    qsort_buffer.reserve(QSORT_BUFFER_SIZE);


    vector<Header>::iterator it = qsort_buffer.begin();

    qsort_buffer.resize(qsort_buffer.size()+1);
    while(i_fs.good()){
        i_fs.read((char *)&(*it), sizeof(BaseHeader));
        (*it).offset = i_fs.tellg();
        // pass data
        i_fs.seekg(it->len, ios_base::cur);

        if(is_valid(*it)){
            it++;
            qsort_buffer.resize(qsort_buffer.size()+1);
        }
        if(qsort_buffer.capacity() == qsort_buffer.size()){
            sort(qsort_buffer.begin(), qsort_buffer.end(), comparator);

            msort_queue.push(Chunk(o_fs.tellg(), qsort_buffer.size()));
            flush_buffer(qsort_buffer, o_fs);
            it = qsort_buffer.begin();
        }
    }
    qsort_buffer.resize(qsort_buffer.size()-1);

    i_fs.close();

    merge_sort(io_fs, msort_queue);

    // create result file



    o_fs.close();
    // print result data
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