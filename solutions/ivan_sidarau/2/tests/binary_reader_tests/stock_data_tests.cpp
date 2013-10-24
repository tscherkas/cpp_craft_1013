#include "test_registrator.h"

#include <vector>
#include <ctime>
#include <cstdlib>

#include <boost/filesystem.hpp>

#include <stock_data.h>

namespace binary_data
{
	namespace tests_
	{
		namespace details
		{			
		}
	}
}

void binary_reader::tests_::test_stock_data()
{
	static const double eps = 0.0000001;
	std::string test_file_path = BINARY_DIR "/test_out.txt";
	BOOST_CHECK_NO_THROW( stock_data( "AAPL", "20130101", 100.0, 101.1, 20000, 1.1, 2.1, 2.2, 3.3, 4.4 ) );
	{
		std::ofstream out( test_file_path, std::ios_base::binary );
		stock_data sd( "AAPL", "20130101", 100.0, 101.1, 20000, 1.1, 2.1, 2.2, 3.3, 4.4 );
		sd.write_raw( out );
	}
	{
		std::ifstream in( test_file_path, std::ios_base::binary );
		stock_data sd( in );
		BOOST_CHECK_EQUAL( std::strcmp( sd.stock_name_, "AAPL" ), 0 );
		BOOST_CHECK_EQUAL( std::strcmp( sd.date_time_, "20130101" ), 0 );
		BOOST_CHECK_EQUAL( fabs( sd.price_ - 100.0 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.vwap_ - 101.1 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.f1_ - 1.1 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.t1_ - 2.1 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.f2_ - 2.2 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.f3_ - 3.3 ) < eps, true );
		BOOST_CHECK_EQUAL( fabs( sd.f4_ - 4.4 ) < eps, true );
		BOOST_CHECK_EQUAL( sd.volume_, 20000 );
	}
	boost::filesystem::remove( test_file_path );

}

void binary_reader::tests_::generate_2_6_tests()
{
}