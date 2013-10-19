#include <iostream>
#include <vector>
#include <cctype>
#include <iterator>
#include <cstddef>

#include "trade_msg.h"
#include "reader.h"
#include "writer.h"

using std::vector;
using binary_reader::Reader;
using binary_writer::Writer;

std::ostream& operator<<(std::ostream& os, const TradeMsg& msg) {
    os << "[" << msg.type_ << "," << msg.time_ << "," << msg.len_ << "," << msg.msg_ << "]";
    return os;
} 

vector<TradeMsg> TradeMsg::read_data(Reader& in) {
    vector<TradeMsg> messages;
    while(!in.eof()) {
        unsigned int type = in.get_int();
        unsigned int time = in.get_int();
        unsigned int len = in.get_int();
		if(in.eof()) return messages;
        std::string str_msg = in.get_string(len);
        if(len == str_msg.size()) {
            if(type <= MARKET_CLOSE && (TradeMsg::max_time < 2 || time > std::max(TradeMsg::max_time - 2, 0U)) ) {				
                TradeMsg::max_time = std::max(time, TradeMsg::max_time);
                TradeMsg msg(type, time, len, str_msg);
                messages.push_back(msg);
            }
        }
    }
    return messages;
} 

void TradeMsg::write_data(vector<TradeMsg> messages, Writer& out) {
    for(vector<TradeMsg>::iterator it = messages.begin(); it != messages.end(); ++it) {
        out.save_int((*it).get_type());
        out.save_int((*it).get_time());
        out.save_int((*it).get_len());
        out.save_string((*it).get_msg());
    }
}

unsigned int TradeMsg::max_time = 0;
