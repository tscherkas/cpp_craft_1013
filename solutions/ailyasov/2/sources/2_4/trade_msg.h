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
        TradeMsg(const size_t type, const size_t time, const size_t len, const std::string msg) : 
            type_(type), time_(time), len_(len), msg_(msg) {
                //empty
            } 
        TradeMsg() {
            //empty
        }
        friend std::ostream& operator<<(std::ostream&, const TradeMsg&);
        static std::vector<TradeMsg> read_data(Reader&);
        static void write_data(std::vector<TradeMsg>, Writer&);
        size_t get_type() const { return type_; }
        size_t get_time() const { return time_; }
        size_t get_len() const { return len_; }
        std::string get_msg() const { return msg_; }
        static size_t max_time;
    private:
        size_t type_;
        size_t time_;
        size_t len_;
        std::string msg_;
};
