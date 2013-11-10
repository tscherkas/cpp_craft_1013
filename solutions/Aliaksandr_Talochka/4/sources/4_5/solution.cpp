#include "solution.h"


task4_5::solution::solution( const data_type& data )
	: Max(0), Min(0)
{
	if(data.size())
		FindMinMax(data);
}

int task4_5::solution::get_min() const
{
	return Min;
}
int task4_5::solution::get_max() const
{
	return Max;
}

void task4_5::solution::FindMinMax(const data_type& Dat)
{
	Max = std::numeric_limits<int>::min();
	Min = std::numeric_limits<int>::max();

	data_type::const_iterator it;
	for(it = Dat.begin(); it != Dat.end(); ++it)
	{
		std::pair< std::vector< int >::const_iterator, std::vector< int >::const_iterator > result = boost::minmax_element(it->begin(), it->end());

		if(*result.first < Min) Min = *result.first;
		if(*result.second > Max) Max = *result.second;
		
	}
}
