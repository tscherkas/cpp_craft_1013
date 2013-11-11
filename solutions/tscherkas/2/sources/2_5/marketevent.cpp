#include "marketevent.h"
#include <string.h>
#include <sstream>
#include <fstream>

MarketEvent::MarketEvent(uint32_t tp, uint32_t tm,uint32_t len,char* msg)
		:TYPE(tp),TIME(tm),LEN(len)
{
	MSG = new char[len];
	for(uint32_t i = 0; i < len; i++)
		*(MSG+i) = *(msg+i);
}
MarketEvent::MarketEvent(const MarketEvent& ev)
{
        TYPE = ev.TYPE;
        TIME = ev.TIME;
        LEN = ev.LEN;
        MSG = new char[LEN];
        for(uint32_t i = 0; i < LEN; i++)
            *(MSG+i) = *(ev.MSG+i);
}
MarketEvent::~MarketEvent()
{
	delete MSG;
}
uint32_t MarketEvent::getTime() const
{
	return TIME;
}
uint32_t MarketEvent::getType() const
{
    return TYPE;
}
uint32_t MarketEvent::getLen() const
{
    return LEN;
}
const char* MarketEvent::getMsg() const
{
    return MSG;
}
std::string MarketEvent::toString() const
{
	std::stringstream info;
	info <<"\nEVENT\nType: " << TYPE << "\nTIME: " << TIME << "\nLen: " << LEN << "\nMessage: " ;
	for(uint32_t i =0 ; i < LEN; ++i)
	    info << *(MSG+i);
	info << std::endl;
	return info.str();
}
bool MarketEvent::operator< (const MarketEvent& ev) const
{
	return TIME < ev.TIME;
}

std::ostream &operator<< ( std::ostream& out, const MarketEvent& ev )
{
	uint32_t size = 3*sizeof(uint32_t)+ev.LEN;
	char *buf = new char[size];
	memcpy(buf,&ev,3*sizeof(uint32_t));
	memcpy(buf+3*sizeof(uint32_t),ev.MSG,ev.LEN);
	out.write(buf,size);
	delete [] buf;
	return out;
}


std::istream& operator>> ( std::istream& in, MarketEvent& ev )
{
    	char *buf = new char[sizeof(uint32_t)];
	in.read(buf,sizeof(uint32_t));
	if(in.eof())
        return in;
	memcpy(&ev.TYPE,buf,sizeof(uint32_t));

	in.read(buf,sizeof(uint32_t));
	if(in.eof())
        return in;
	memcpy(&ev.TIME,buf,sizeof(uint32_t));

	in.read(buf,sizeof(uint32_t));
	if(in.eof())
        return in;
	memcpy(&ev.LEN,buf,sizeof(uint32_t));

	delete [] buf;
	delete [] ev.MSG;
	ev.MSG = new char[ev.LEN];
	in.read(ev.MSG,ev.LEN);
    return in;
}

