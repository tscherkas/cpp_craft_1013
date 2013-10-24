#ifndef _BINARY_READER_STOCK_DATA_H_
#define _BINARY_READER_STOCK_DATA_H_

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

namespace binary_reader
{
	class stock_data : virtual protected boost::noncopyable
	{
	public:
		explicit stock_data( std::ifstream& in );
		~stock_data();
	};
}

#endif // _BINARY_READER_STOCK_DATA_H_

