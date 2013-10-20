#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "reader.h"
#include "writer.h"

using binary_reader::Reader;
using binary_writer::Writer;
//[ stock_name, date, price, volume, f2 ]
class TradeMsgOut {
    public:
        TradeMsgOut(
                std::string stock_name,
                unsigned int date,
                double price,
                unsigned int volume,
                double f2
                ) : 
            stock_name_(stock_name),
            date_(date),
            price_(price),
            volume_(volume),
            f2_(f2)
    {
        //empty
    } 
        TradeMsgOut() {
            //empty
        }
        friend std::ostream& operator<<(std::ostream&, const TradeMsgOut&);
        static void write(const std::vector<TradeMsgOut>, Writer&);
        std::string get_stock_name() const { return stock_name_; }
        unsigned int get_date() const { return date_; }
        double get_price() const { return price_; }
        unsigned int get_volume() const { return volume_; }
        double get_f2() const { return f2_; }
    private:
        std::string stock_name_;
        unsigned int date_;
        double price_;
        unsigned int volume_;
        double f2_;
};
