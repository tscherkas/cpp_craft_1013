#include <string>
#include <iostream>

class base_exception
{
public:
	virtual void what() const
	{
		std::cout << "base_exception" << std::endl;
	}
};

class nested_exception : public base_exception
{
public:
	virtual void what() const
	{
		std::cout << "nested_exception" << std::endl;
	}
};

int main()
{
	try
	{
		throw nested_exception();
	}
	catch( const base_exception& e )
	{
		e.what();
	}
	catch( const nested_exception& e )
	{
		e.what();
	}
}

