#include "inttypes.h"
#include <string.h>
#include <sstream>
#include <fstream>
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
	MarketEvent(uint32_t tp, uint32_t tm,uint32_t len,char* msg)
		:TYPE(tp),TIME(tm),LEN(len)
	{
		MSG = new char[len];
		for(uint32_t i = 0; i < len; i++)
			*(MSG+i) = *(msg+i);
	}
	MarketEvent(const MarketEvent& ev)
	{
        TYPE = ev.TYPE;
        TIME = ev.TIME;
        LEN = ev.LEN;
        MSG = new char[LEN];
        for(uint32_t i = 0; i < LEN; i++)
            *(MSG+i) = *(ev.MSG+i);
	}
	~MarketEvent()
	{
		delete MSG;
	}
	uint32_t getTime() const
	{
	    return TIME;
	}
	uint32_t getType() const
	{
	    return TYPE;
	}
	uint32_t getLen() const
	{
	    return LEN;
	}
	std::string toString() const
	{
        std::stringstream info;
        info <<"\nEVENT\nType: " << TYPE << "\nTIME: " << TIME << "\nLen: " << LEN << "\nMessage: " ;
        for(uint32_t i =0 ; i < LEN; ++i)
            info << *(MSG+i);
        info << std::endl;
        return info.str();
	}
	bool operator< (const MarketEvent& ev) const
	{
		return TIME < ev.TIME;
	}
	friend std::ostream& operator<< ( std::ostream& out, const MarketEvent& ev );
	friend std::istream& operator>> ( std::istream& in,  MarketEvent& ev );

};
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

struct is_old_ev_predicate {
    uint32_t compare_value;
    is_old_ev_predicate(uint32_t v):compare_value(v){}
    bool operator() (const MarketEvent& event)
    {
        return (event.getType() > 4)||
            !event.getType()||
            event.getTime() <= compare_value;
    }
};
int main()
{
	std::ofstream output_file("2.4_example.out",std::ios::out|std::ios::binary);
	if(!output_file.is_open())
		return 0;

	MarketEvent var2(2,2,7,"Onliner");
	MarketEvent var3(2,3,5,"DEVBY");
	MarketEvent var4(1,4,5,"OSTIS");
	MarketEvent var5(3,4,5,"HALLO");
	output_file << var1 << var2 << var3 << var4 << var5;
	output_file.close();*/
	std::ifstream input_file ("2.4_example.in",std::ios::in|std::ios::binary);
	if(!input_file.is_open())
		return 0;
    std::list < MarketEvent > events;
    uint32_t max_time = 0;

	while(!input_file.eof())
	{
		MarketEvent var(0,0,1,"");
		input_file>>var;
		if(input_file.eof())
            break;
		if(var.getTime() > max_time)
            max_time = var.getTime();
        std::cout << var.toString().c_str();
		events.push_back(var);
	}
	input_file.close();
    events.remove_if(is_old_ev_predicate(max_time-2));
    events.sort();
    for(std::list<MarketEvent>::iterator it = events.begin(); it != events.end(); it++)
        output_file << (*it);
	output_file.close();
return 0;
}

