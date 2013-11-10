#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <limits>
#include <boost\noncopyable.hpp>
#include <boost\thread.hpp>
#include <boost\algorithm/minmax_element.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;

	class solution: virtual protected boost::noncopyable
	{
	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	private:
		int Max, Min;
		boost::thread_group tg;

		void FindMinMax(const data_type& Dat);


	};
}

#endif // _TASK4_5_SOLUTION_H_

