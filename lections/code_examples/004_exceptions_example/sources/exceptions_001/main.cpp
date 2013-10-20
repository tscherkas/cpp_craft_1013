#include <string>
#include <iostream>

class my_exception
{
};

class another_exception
{
};

int main()
{
	try
	{
		throw my_exception();
	}
	catch( my_exception )
	{
		std::cout << "my exception was catched!" << std::endl;
	}	
	catch( ... )
	{
		std::cout << "unknown exception was catched!" << std::endl;
	}
}

