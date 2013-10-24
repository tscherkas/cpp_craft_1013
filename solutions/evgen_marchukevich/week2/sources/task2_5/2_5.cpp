#include <iostream>
#include <fstream>
#include <cstdio>
#include <math.h>
#include <string>
#include <cstring>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <vector>


using namespace std;


class Solution
{

private :
		
		struct msg{
			unsigned int type;
			unsigned int time;
			unsigned int len;
			string m;
			};


		ifstream f1;
		ofstream f2;


		bool err;	
		map<unsigned int,int> a,kol;
		map<unsigned int,size_t> z;
		map<unsigned int,int> u;
		map<unsigned int,double> ans;
		int time;
		vector<unsigned int> types,all_types;
	

		void reader(msg &t)
		{	
			if(f1.read(reinterpret_cast<char*>(&t.type),sizeof (unsigned int))==0) 
			{
				err=1;
				return;
			}
			f1.read(reinterpret_cast<char*>(&t.time),sizeof (unsigned int));
			f1.read(reinterpret_cast<char*>(&t.len),sizeof (unsigned int));
			for(unsigned int i=0;i<t.len;i++)
			{
				char c;
				f1.read(reinterpret_cast<char*>(&c),sizeof (char));
				t.m+=c;
			}
		}


		void writer()
		{
			sort(all_types.begin(),all_types.end());
			vector<unsigned int> :: iterator it;
			for(it=all_types.begin();it!=all_types.end();it++)
			{
				f2.write(reinterpret_cast<char*>(&(*it)),sizeof (*it));
				double w=ans[*it]/(1.0*kol[*it]);
				f2.write(reinterpret_cast<char*>(&w),sizeof (double));
			}

		}


		bool check(const msg &x)
		{
			return (z[x.type]+sizeof(x)<=2048);
		}

		void calc(const msg &x)
		{
			if (time!=x.time) 
				{
					vector<unsigned int> :: iterator it;
					for(it=types.begin();it!=types.end();it++)
					{
						if (ans[*it]==0)
						{
							ans[*it]=a[*it]; 
							kol[*it]++;
						}
						else 
						{
							ans[*it]+=a[*it];
							kol[*it]++;
						}
						a[*it]=0;
						z[*it]=0;
					}
					types.clear();
					time=x.time;
				} 
				if (!check(x)) return;
				a[x.type]++;
				if (a[x.type] == 1 && x.type!=-1) 
					{
						types.push_back(x.type);	
						if (u[x.type]==0)
						{
							all_types.push_back(x.type);
							u[x.type]++;
						}
					}
				z[x.type]+=sizeof(x);

		}

public :

		Solution()
		{
			f1.open("input.txt", ios_base::in | ios_base::binary);
			f2.open("output.txt",ios_base::out| ios_base::binary);	
			if (!f1.is_open() || !f2.is_open()) 
			{
				throw new exception();				
			}	
			err=0;
			time=-1;	
		}

		~Solution()
		{
			types.clear();
			f1.close();
			f2.close();	
		}


		void process()
		{
			while (!f1.eof())
			{
				msg x;
				reader(x);
				if (err) break;
				calc(x);
			}
			msg x;
			x.time=-1;
			x.type=-1;
			calc(x);
			writer();
		}
					
};


int main()
{
	try
	{
		Solution s;
		s.process();
	}

	catch(...)
	{
		cerr << "Can't open file" << endl;
	}
	return 0;
}