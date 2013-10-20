#include <list>
#include <string.h>
#include <iostream>
#include <fstream>
#include "marketevent.h"

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>

static const uint32_t register_size = 2048;

int main()
{
    std::ifstream input_file (SOURCE_DIR "/tests/2.5_example.in",std::ios::in|std::ios::binary);
	if(!input_file.is_open())
	{
	    std::cout << "Error by opening input file";
		return 0;
	}
	std::ofstream output_file(SOURCE_DIR "/tests/2.5_example.out",std::ios::out|std::ios::binary);
	if(!output_file.is_open())
	{
	    std::cout << "Error by creating output file";
		return 0;
	}
	std::list < MarketEvent > events;
    boost::unordered_map <uint32_t, uint32_t> counter; //счетчик размера по типам
    boost::unordered_map <uint32_t, uint32_t>::iterator it;//и его итератор
    boost::unordered_map <uint32_t, double> result;
	uint32_t current_sec = 0;
	while(!input_file.eof())
	{
		MarketEvent var(0,0,1,"");
		input_file>>var;
		if(input_file.eof())
            break;
        if(var.getType() > 100000)
            continue;
        if(var.getTime() > current_sec)
        {
            current_sec = var.getTime();
            counter.clear();
        }
		it = counter.find(var.getType());
		if(it != counter.end() && register_size - it->second > var.getLen()+12)
		{
		    events.push_back(var);
		    it->second +=  var.getLen()+12;
		    result[var.getType()]++;
		}
		else if(it != counter.end())
                continue;
        else
        {
            counter[var.getType()] = var.getLen()+12;
		    events.push_back(var);
		    result[var.getType()]++;
        }

	}
	const uint32_t bufsize = sizeof(uint32_t)+3+sizeof(double);
	char *buf = new char[bufsize];
	*(buf+sizeof(uint32_t)) = *(buf+sizeof(uint32_t)+sizeof(double)+1)= *(buf+sizeof(uint32_t)+sizeof(double)+2) ='\n';
	for(boost::unordered_map <uint32_t, double>::iterator it = result.begin();
        it != result.end();
        it++
        )
    {
        memcpy(buf,&it->first,sizeof(uint32_t));
        memcpy(buf+sizeof(uint32_t)+1,&it->second/current_sec,sizeof(double));
        output_file.write(buf, bufsize);
    }
	output_file.close();
    return 0;
}

