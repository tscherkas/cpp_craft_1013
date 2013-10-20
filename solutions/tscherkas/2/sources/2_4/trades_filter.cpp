#include "inttypes.h"
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>
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
		return 22;
	std::ofstream output_file(SOURCE_DIR "/tests/2.4_example.out",std::ios::out|std::ios::binary);
	if(!output_file.is_open())
		return 234;
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

