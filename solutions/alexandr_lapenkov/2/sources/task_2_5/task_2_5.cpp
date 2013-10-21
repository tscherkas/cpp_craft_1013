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
		unsigned int type,time,len;
		
		friend binreader& operator>>(binreader&, Data&); 

		size_t getSize()
		{
			return sizeof(int)*3+sizeof(char)*len;
		}
	
	};

	friend binreader& operator>>(binreader& in, Data& a)
	{
		if(in.good())
			a.type = in.get_unsigned();
		if(in.good())
			a.time = in.get_unsigned();
		if(in.good())
			a.len = in.get_unsigned();
		if(in.good())
			in.get_line(a.len);	
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
		   map<unsigned, size_t> takes;
		   map<unsigned, int> saved, diff, last;
		   Data x;
		   
		   in>>x;
		   if(x.getSize()<=2048)
		   {
		      takes[x.type]+=x.getSize();
			  saved[x.type]++;
		   }
		   diff[x.type] = 1;
		   last[x.type] = x.time;

		   while(in.good())
		   {
			   in>>x;
			   if(!in.good())break;

			   size_t size = x.getSize();
			   
			   if(!last.count(x.type)||x.time!=last[x.type])
			   {
				   takes.clear();
				   diff[x.type]++;
			   }

			   if(x.getSize()<=2048)
			   {
				   takes[x.type]+=x.getSize();
				   saved[x.type]++;
			   }
			   
			   last[x.type] = x.time;
		   }
		   for(map<unsigned, int>::iterator it = saved.begin();it!=saved.end();it++)
		   {
			   out.write_unsigned(it->first);
			   out.write_double(double(it->second)/diff[it->first]);
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
