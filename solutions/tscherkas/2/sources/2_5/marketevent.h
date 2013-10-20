#ifndef MARKETEVENT2_5_H
#define MARKETEVENT2_5_H

#include "inttypes.h"
#include <iostream>
#include <list>


class MarketEvent
{
private:
	uint32_t TYPE;
	uint32_t TIME;
	uint32_t LEN;
	char* MSG;
	MarketEvent();
	MarketEvent& operator=(const MarketEvent&);
public:
	MarketEvent(uint32_t tp, uint32_t tm,uint32_t len,char* msg);
	MarketEvent(const MarketEvent& ev);
	~MarketEvent();
	uint32_t getTime() const;
	uint32_t getType() const;
	uint32_t getLen() const;
	const char* getMsg() const;
	std::string toString() const;
	bool operator< (const MarketEvent& ev) const;
	friend std::ostream& operator<< ( std::ostream& out, const MarketEvent& ev );
	friend std::istream& operator>> ( std::istream& in,  MarketEvent& ev );

};

#endif //MARKETEVENT2_5_H
