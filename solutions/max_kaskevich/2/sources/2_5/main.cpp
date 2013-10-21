#include "message.h"
#include <stdint.h>
#include <map>

static const uint32_t max_data_size = 2048;

struct meassage_stats
{
    uint32_t seconds;
    uint32_t msg_data_size_by_time;
    uint32_t last_second;
    uint32_t msg_count;
    meassage_stats() : seconds(1),
                       msg_data_size_by_time(0),
                       last_second(0),
                       msg_count(0)
    {}
};

int main( int argc, char* argv[] )
{
    std::ifstream input(BINARY_DIR "/input.txt", std::ios::binary);
    std::ofstream output(BINARY_DIR "/output.txt", std::ios::binary);
    if(!input || !output)
    {
        return 1;
    }
    typedef  std::map<uint32_t, meassage_stats> msg_stats_map;
    msg_stats_map msg_stats;
    uint32_t next_time = 0;
    message m;
    while(input >> m)
    {
        // clear size info when new time comming
        if (m.time >= next_time)
        {
            for(msg_stats_map::value_type& m_stat: msg_stats)
            {
                m_stat.second.msg_data_size_by_time = 0;
            }
            next_time = m.time + 1;
        }

        auto& m_stat = msg_stats.insert(msg_stats_map::value_type(m.type, meassage_stats())).first->second;
        m_stat.msg_data_size_by_time += m.len + 12;


        if(m_stat.msg_data_size_by_time < max_data_size)
        {
    	    ++m_stat.msg_count;
    	    if(m.time > m_stat.last_second)
    	    {
                m_stat.last_second = m.time;
    	        ++m_stat.seconds;
    	    }
        }
        // miss msg
        if(m.len)
        {
    	    input.seekg(m.len, std::ios::cur);
        }
    }

    double avg = 0;
    for(msg_stats_map::value_type& m_stat_pair: msg_stats)
    {
        avg = m_stat_pair.second.msg_count /  m_stat_pair.second.seconds;
        output.write(reinterpret_cast<char*>(const_cast<uint32_t*>(&m_stat_pair.first)), sizeof(uint32_t));
        output.write(reinterpret_cast<char*>(&avg), sizeof(double));
    }
}
