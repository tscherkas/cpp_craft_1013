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

private:

	struct msg{
		int type;
		int time;
		int len;
		string m;
		};

	ifstream f1;
	ofstream f2;

	bool error,inn1,inn2;
	int T;
	vector<msg> a;			

	
	void reader(msg &t)
		{	
			if(f1.read(reinterpret_cast<char*>(&t.type),sizeof (int))==0) 
				{
					error=1;
					return;
				}
			f1.read(reinterpret_cast<char*>(&t.time),sizeof (int));
			f1.read(reinterpret_cast<char*>(&t.len),sizeof (int));
			for(int i=0;i<t.len;i++)
			{
				char c;
				f1.read(reinterpret_cast<char*>(&c),sizeof (char));
				t.m+=c;
			}	
		}


	void writer(int T)
		{
			vector<msg> b;
			vector<msg> :: iterator it;
			for(it=a.begin();it!=a.end();it++)
			{
				if (it->time!=T) b.push_back(*it); else
				{
					f2.write(reinterpret_cast<char*>(&(it->type)),sizeof (int));
					f2.write(reinterpret_cast<char*>(&(it->time)),sizeof (int));
					f2.write(reinterpret_cast<char*>(&(it->len)),sizeof (int));
					for(int i=0;i<it->len;i++)
						{
							f2.write(reinterpret_cast<char*>(&(it->m[i])),sizeof (char));
						}
				}
			}
			a.clear();
			for(it=b.begin();it!=b.end();it++)
				a.push_back(*it);
			b.clear();
		}
	
	bool check(const msg &t, const int max)
		{
			if (t.type<1 || t.type>4) return 0;
			if (max==-1) return 1;
			if (t.time <=max-2) return 0;
			return 1;
		}

public:

	Solution()
	{
		f1.open("input.txt", ios_base::in | ios_base::binary);
		f2.open("output.txt",ios_base::out| ios_base::binary);
		if (!f1.is_open() || !f2.is_open()) 
		{
			throw new exception();
		}
		error=0;
		inn1=inn2=1;
		T=-1;
	}

	~Solution()
	{		
		a.clear();
		f1.close();
		f2.close();	
	}

	void process()
		{
			while (!f1.eof())
			{
				msg x;
				reader(x);
				if (error) break;
						if (!check(x,T)) 
							continue;
						if (inn1)
						{
							T=x.time;
							inn1=0;
							a.push_back(x);
							continue;
						}
						if (x.time>T+1)
						{
							writer(T-1);
							writer(T);			
							a.push_back(x);
							T=x.time;
							continue;
						}
						if (x.time==T+1 && !inn2)
						{
							writer(T-1);
							a.push_back(x);
							T++;
							continue;
						}
						if (x.time==T+1) 
						{
							inn2=0;
							T++;
						}
						a.push_back(x);
				}
			if (a.size()!=0)
			{
				writer(T-1);
				writer(T);
			}	
		}
	

};




int main()
{
	try
	{
		Solution x;
		x.process();
	}
	catch(...)
	{
		cerr << "Can't open file" << endl;
	}
	return 0;
}