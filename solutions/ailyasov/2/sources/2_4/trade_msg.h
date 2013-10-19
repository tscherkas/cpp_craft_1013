#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "reader.h"
#include "writer.h"

using binary_reader::Reader;
using binary_writer::Writer;

enum TYPES {
    MARKET_OPEN = 1,
    TRADE = 2,
    QUOTE = 3,
    MARKET_CLOSE = 4
};

class TradeMsg {
    public:
        TradeMsg(const unsigned int type, const unsigned int time, const unsigned int len, const std::string msg) : 
            type_(type), time_(time), len_(len), msg_(msg) {
                //empty
            } 
        TradeMsg() {
            //empty
        }
        friend std::ostream& operator<<(std::ostream&, const TradeMsg&);
        static std::vector<TradeMsg> read_data(Reader&);
        static void write_data(std::vector<TradeMsg>, Writer&);
        int get_type() const { return type_; }
        int get_time() const { return time_; }
        int get_len() const { return len_; }
        std::string get_msg() const { return msg_; }
        static int max_time;
    private:
        int type_;
        int time_;
        int len_;
        std::string msg_;
};
