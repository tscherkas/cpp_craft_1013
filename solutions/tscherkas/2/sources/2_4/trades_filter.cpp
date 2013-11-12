//#include "inttypes.h"
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>
#include <deque>
#include "marketevent.h"



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
	std::ifstream input_file (SOURCE_DIR "/tests/2.4_example.in",std::ios::in|std::ios::binary);
	if(!input_file.is_open())
	{
	    std::cout << "Error by opening input file";
		return 0;
	}
	std::ofstream output_file(SOURCE_DIR "/tests/2.4_example.out",std::ios::out|std::ios::binary);
	if(!output_file.is_open())
	{
	    std::cout << "Error by creating output file";
		return 0;
	}
    std::list < MarketEvent > current_events,old_hight_priority_events,old_low_priority_events;
    std::deque < std::list < MarketEvent > > buffers_of_actual_events;
    buffers_of_actual_events.push_back(old_low_priority_events);
    buffers_of_actual_events.push_back(old_hight_priority_events);
    buffers_of_actual_events.push_back(current_events);
    is_old_ev_predicate predicate(0);
    while(!input_file.eof())
	{
		MarketEvent var(0,0,1,"");
		input_file>>var;
		if(input_file.eof())
            break;
        if(!predicate(var))
        {
            if(var.getTime()>predicate.compare_value+2)
            {
                if(var.getTime()>predicate.compare_value+4)
                {
                    buffers_of_actual_events.clear();
                    buffers_of_actual_events.push_back(old_low_priority_events);
                    buffers_of_actual_events.push_back(old_hight_priority_events);
                    buffers_of_actual_events.push_back(current_events);
                }
                else if (var.getTime()==predicate.compare_value+4) {
                    buffers_of_actual_events.pop_front();
                    buffers_of_actual_events.pop_front();
                    buffers_of_actual_events.push_back(old_hight_priority_events);
                    buffers_of_actual_events.push_back(current_events);
                }
                else if (var.getTime()==predicate.compare_value+3) {
                    buffers_of_actual_events.pop_front();
                    buffers_of_actual_events.push_back(current_events);
                }
                buffers_of_actual_events[2].push_back(var);
                std::cout << var.toString().c_str();
            }
            else
            {
                std::cout << var.toString().c_str();
                buffers_of_actual_events[var.getTime()-predicate.compare_value].push_back(var);
            }
        }
	}
    input_file.close();
    for(std::deque < std::list<MarketEvent> >::iterator buf_it = buffers_of_actual_events.begin();
        buf_it!=buffers_of_actual_events.end();
        buf_it++)
            for(std::list<MarketEvent>::iterator it = buf_it->begin();
                it != buf_it->end();
                it++)
                    output_file << (*it);
	output_file.close();
    return 0;
}

