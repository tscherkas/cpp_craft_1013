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


struct msg{
	int type;
	int time;
	int len;
	string m;
	};


ifstream f1;
ofstream f2;


void reader(msg &t,bool &err)
{	
	if(f1.read(reinterpret_cast<char*>(&t.type),sizeof (int))==0) 
		{
			err=1;
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


bool check(const msg &t, const int max)
{
	if (t.type<1 || t.type>4) return 0;
	if (max==-1) return 1;
	if (t.time <=max-2) return 0;
	return 1;
}


void writer(vector<msg> &a, int T)
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

inline void process(const msg &x,int &T,vector<msg> &a,bool &inn1 , bool &inn2)
{
		if (!check(x,T)) 
			return;
		if (inn1)
		{
			T=x.time;
			inn1=0;
			a.push_back(x);
			return;
		}
		if (x.time>T+1)
		{
			writer(a,T-1);
			writer(a,T);			
			a.push_back(x);
			T=x.time;
			return;
		}
		if (x.time==T+1 && !inn2)
		{
			writer(a,T-1);
			a.push_back(x);
			T++;
			return;
		}
		if (x.time==T+1) 
		{
			inn2=0;
			T++;
		}
		a.push_back(x);
}

void closer(vector<msg> &a)
{
	a.clear();
	f1.close();
	f2.close();	
}

int main()
{
	f1.open("input.txt", ios_base::in | ios_base::binary);
	f2.open("output.txt",ios_base::out| ios_base::binary);
	bool inn1=1,inn2=1;
	bool err=0;
	int T=-1;
	vector<msg> a;		
	if (!f1.is_open() || !f2.is_open()) 
	{
		closer(a);
		return 0;
	}
	while (!f1.eof())
	{
		msg x;
		reader(x,err);
		if (err) break;
		process(x,T,a,inn1,inn2);
	}
	if (a.size()!=0)
	{
		writer(a,T-1);
		writer(a,T);
	}
	closer(a);
	return 0;
}