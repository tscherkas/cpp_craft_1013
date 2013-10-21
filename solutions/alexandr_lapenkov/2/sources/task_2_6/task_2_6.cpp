#include <iostream>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "readlib.h"
#include "writelib.h"

using namespace std;

class Solution
{ 
	binreader in;
	binwriter out;
       
	struct Data
	{
		double f1,t1,f2,f3,f4,volume;
		string stock_name;
		string date_time;
		double price, vwap;

		
		friend binreader& operator>>(binreader&, Data&); 
	
	};

	friend binreader& operator>>(binreader& in, Data& a)
	{
		a.stock_name = in.get_line(9);
		a.date_time = in.get_line(8);
		a.price = in.get_unsigned();
		a.vwap = in.get_double();
		a.volume = in.get_double();
		a.f1 = in.get_double();
		a.t1 = in.get_double();
		a.f2 = in.get_double();
		a.f3 = in.get_double();
		a.f4 = in.get_double();
		return in;
	}

public:

       Solution()
       {
		   in.open(SOURCE_DIR"/input.txt");
		   out.open(SOURCE_DIR"/output.txt");
		   if(!in.is_open()||!out.is_open())
			   throw new exception();
       }
            
       ~Solution()
       {
		   in.close();
		   out.close();
       }                 	
       
       void process()
       {
		   Data x;
		   while(in.good())
		   {
			   in>>x;
			   if(!in.good())break;
			   out.write_line(x.stock_name.c_str(),9);
			   unsigned day,month,year;
			   sscanf(x.date_time.c_str(),"%4d%2d%2d",&day,&month,&year);
			   out.write_unsigned(year*372+month*31+day-1);
			   out.write_double(x.vwap);
			   out.write_double(x.volume);
			   out.write_double(x.f2);
		   }
	   }	
            
};


int main()
{
	try
	{
		Solution s;
		s.process();
	}catch(...)
	{
		cerr<<"Can't open files!";
	}
	
	return 0;  
}
