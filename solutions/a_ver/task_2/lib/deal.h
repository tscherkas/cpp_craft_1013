#ifndef _DEAL_DATA_H
#define _DEAL_DATA_H

#include <stdint.h>
#include <fstream>

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

istream& operator>> (istream& is, MessageHeader &m);

bool is_outdated_deal(MessageHeader &item);

#endif // _DEAL_DATA_H