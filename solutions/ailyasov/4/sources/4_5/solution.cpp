#include <algorithm>
#include <vector>
#include <limits>

#include <boost/thread/thread.hpp>
#include <boost/cstdint.hpp>
#include <boost/thread/mutex.hpp>

#include "solution.h" 

using boost::uint32_t;

static int DEFAULT_VALUE = 0;

int deref_iterator_or_default(std::vector<int>::const_iterator it, std::vector<int> const& v)
{ 
    return (it == v.end()) ? DEFAULT_VALUE : *it;
}

void task4_5::solution::add_min_max(data_type::const_iterator it)
{
    std::vector<int> const& v = *it;
    if(!v.empty())
    {
        int min = std::numeric_limits<int>().max();
        int max = std::numeric_limits<int>().min();
        for(std::vector<int>::const_iterator itt = v.begin(); itt != v.end(); ++itt)
        {
            if(*itt < min)
                min = *itt;
            if(*itt > max)
                max = *itt;
        }
        boost::mutex::scoped_lock lock ( values_protector_ );
        max_values_.push_back( max );
        min_values_.push_back( min );
    }
} 

task4_5::solution::solution( const data_type& data ) : data_(data)
{
    max_values_.reserve(data.size());
    min_values_.reserve(data.size());

    boost::thread_group t_group;
    for(data_type::const_iterator it = data_.begin(); it != data_.end(); ++it)
    {
        t_group.create_thread(boost::bind(&task4_5::solution::add_min_max,this,it));
    } 
    t_group.join_all();

    min_ = deref_iterator_or_default(std::min_element(min_values_.begin(), min_values_.end()), min_values_); 
    max_ = deref_iterator_or_default(std::max_element(max_values_.begin(), max_values_.end()), max_values_); 
} 

int task4_5::solution::get_min() const
{ 
    return min_;
}

int task4_5::solution::get_max() const
{
    return max_;
} 
