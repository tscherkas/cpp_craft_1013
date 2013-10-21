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
	unsigned int type;
	unsigned int time;
	unsigned int len;
	string m;
	};


ifstream f1;
ofstream f2;


void reader(msg &t,bool &err)
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


bool check(const msg &x,map<unsigned int,size_t> &z)
{
	return (z[x.type]+sizeof(x)<=2048);
}


void writer(map<unsigned int,double> &ans,map<unsigned int,int> &kol,vector<unsigned int> &all_types)
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

inline void process(const msg &x,map<unsigned int,int> &a,map<unsigned int,double> &ans, vector<unsigned int> &types,map<unsigned int,size_t> &z,int &time,map<unsigned int,int> &kol,map<unsigned int,int> &u, vector<unsigned int> &all_types)
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
		if (!check(x,z)) return;
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

void closer(vector<unsigned int> &types)
{
	types.clear();
	f1.close();
	f2.close();	
}

int main()
{
	f1.open("input.txt", ios_base::in | ios_base::binary);
	f2.open("output.txt",ios_base::out| ios_base::binary);
	bool err=0;
	map<unsigned int,int> a,kol;
	map<unsigned int,size_t> z;
	map<unsigned int,int> u;
	map<unsigned int,double> ans;
	int time=-1;
	vector<unsigned int> types,all_types;
	if (!f1.is_open() || !f2.is_open()) 
	{
		closer(types);
		return 0;
	}
	while (!f1.eof())
	{
		msg x;
		reader(x,err);
		if (err) break;
		process(x,a,ans,types,z,time,kol,u,all_types);
	}
	msg x;
	x.time=-1;
	x.type=-1;
	process(x,a,ans,types,z,time,kol,u,all_types);
	writer(ans,kol,all_types);
	closer(types);
	return 0;
}