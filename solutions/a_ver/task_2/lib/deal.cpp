#include <stdint.h>
#include <fstream>
#include <deal.h>

using namespace std;

istream& operator>> (istream& is, MessageHeader &m){

    is.read((char *)&m.type, sizeof(uint32_t));
    is.read((char *)&m.time, sizeof(uint32_t));
    is.read((char *)&m.len, sizeof(uint32_t));

    return is;
}

bool is_outdated_deal(MessageHeader &item){
    static uint32_t max_time = 0;
    bool result = true;
    if((item.type == MARKET_OPEN || item.type == TRADE ||
        item.type == QUOTE || item.type == MARKET_CLOSE) &&
       (item.time > (max_time - 2) || max_time < 2)){
        result = false;
    }
    if(max_time < item.time){
        max_time = item.time;
    }
    return result;
}