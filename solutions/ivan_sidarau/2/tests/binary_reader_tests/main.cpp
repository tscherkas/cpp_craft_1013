#include <reader.h>

#include <iostream>
#include <fstream>

#define test_no_throw( action ) \
{ \
	try \
	{ \
		action; \
	} \
	catch( ... ) \
	{ \
		std::cout << "test_no_throw failed: " <<  __FILE__ << ":" << __LINE__ << std::endl; \
	} \
} \

template< unsigned int size >
struct a
{
	unsigned int type_;
	unsigned int time_;
	unsigned int len_;
	char msg_[ size + 1 ];
	explicit a( unsigned int type, unsigned int time, const char* buffer )
		: type_( type )
		, time_( time )
		, len_( size )
	{
		strcpy( msg_, buffer );
	}
	void out( std::ostream& out )
	{
		out.write( reinterpret_cast< char* >( &type_ ), sizeof( type_ ) );
		out.write( reinterpret_cast< char* >( &time_ ), sizeof( time_ ) );
		out.write( reinterpret_cast< char* >( &len_ ), sizeof( len_ ) );
		out.write( reinterpret_cast< char* >( &msg_ ), len_ );
	}
};


int main()
{
	test_no_throw( binary_reader::proxy_function_that_was_created_only_for_compiling_goals() );
	//
	a<6> a1( 1, 1, "GOOGLE" );
	a<6> a2( 2, 1, "TUT.BY" );
	a<5> a3( 3, 1, "APPLE" );
	a<4> a4( 8, 1, "EPAM" );
	a<8> a5( 3, 2, "CPPCRAFT" );
	a<9> a6( 2, 3, "STARCRAFT" );
	a<5> a7( 2, 2, "PLSQL" );
	a<7> a8( 3, 2, "LAVAVEJ" );
	a<9> a9( 2, 1, "MICROSOFT" );
	a<10> a10( 3, 1, "CALL RAMPA" );
	a<6> a11( 2, 3, "GOOGLE" );
	a<4> a12( 4, 4, "CPPC" );
	//
	std::ofstream out( "2.4_example.out", std::ios_base::binary );
	a1.out( out );
	a2.out( out );
	a3.out( out );
	a4.out( out );
	a5.out( out );
	a6.out( out );
	a7.out( out );
	a8.out( out );
	a9.out( out );
	a10.out( out );
	a11.out( out );
	a12.out( out );
	out.close();
}
