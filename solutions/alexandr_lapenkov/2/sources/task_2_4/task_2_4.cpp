#include <iostream>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include "readlib.h"
#include "writelib.h"

using namespace std;

class Solution
{ 
	binreader in;
	binwriter out;
       
	struct Data
	{
		int type,time,len;
		string msg;
		
		friend binreader& operator>>(binreader&, Data&);
		friend binwriter& operator<<(binwriter&, const Data&);
		
		bool operator <(const Data& a) const
		{
			return (time<a.time);
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
			a.msg = in.get_line(a.len);	
		return in;
	}

	friend binwriter& operator<<(binwriter& out, const Data& a)
	{
		out.write_unsigned(a.type);
		out.write_unsigned(a.time);
		out.write_unsigned(a.len);
		out.write_line(a.msg.c_str(),a.len);

		return out;
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
		   Data x,last;
		   bool f=0;
		   int max_t;
		   vector<Data>a;

		   while(in.good())
		   {
			   in>>x;
			   if(!in.good())break;
			   if(x.type<1u||x.type>4u)continue;

			   if(!f)
			   {
				   max_t = x.time;
				   a.push_back(x);
				   f=1;
			   }
			   else
			   {
				   if(x.time>(max_t-2))
					   a.push_back(x);
				   max_t=max(max_t,x.time);
			   }
				
		   }
		   
		   sort(a.begin(),a.end());
		   
		   for(vector<Data>::iterator it = a.begin(); it<a.end(); it++)
			   out<<(*it);
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
