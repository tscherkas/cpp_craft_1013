#pragma once

#include <vector>
#include <set>
#include <map>
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

class MsgBufInfo;

typedef std::map<const size_t, MsgBufInfo> MsgTypeMap;
typedef const size_t Type;

class Msg {
    public:
        Msg(const size_t type, 
                const size_t time, 
                const size_t len, 
                const std::string msg) : type_(type), time_(time), len_(len), msg_(msg) { }

        friend std::ostream& operator<<(std::ostream& os, const Msg& msg);
        Type get_type() const { return type_; }
        int get_time() const { return time_; }
        size_t get_len() const { return len_; }
        //message size is given as 3 integer values + character array of length LEN
        size_t get_size() const { return sizeof(size_t) * 3 + len_; }
        std::string get_msg() const { return msg_; }
    private:
        size_t type_;
        size_t time_;
        size_t len_;
        std::string msg_;
};

class MsgBufInfo {
    public:
        MsgBufInfo(const size_t time, const size_t size) : size_(size), msg_count_(1) 
        {
            time_set_.insert(time);
        }

        //average number of messages of certain type per second
        double get_avg() const 
        {
            return static_cast<double>(msg_count_) / time_set_.size();
        }

        const size_t get_size() const { return size_; }
        bool add_type(const Msg&);
        friend std::ostream& operator<<(std::ostream&, const MsgBufInfo&);
        void add(const Msg& m);
    private:
        MsgBufInfo();
        void operator=(const MsgBufInfo&);
        std::set<size_t> time_set_; //set of seconds
        size_t size_; //total length of all messages
        size_t msg_count_; //number of messages
};

class MsgBuf {
    public:
        MsgBuf() {}
        static const size_t MAX_SIZE;
        const MsgTypeMap& get_type_map() const;
        const std::vector<Msg>& get_messages() const;
        const size_t get_size(const size_t type) const;
        const bool is_full(const size_t type) const;
        void read(Reader&);
        void write_type_map(Writer&);
        static void write_data(std::vector<Msg> messages, Writer& out); 
    private:
        MsgBuf(const MsgBuf&);
        void operator=(const MsgBuf&);
        void add(const Msg& m);
        MsgTypeMap type_map;
        std::vector<Msg> messages;
};
