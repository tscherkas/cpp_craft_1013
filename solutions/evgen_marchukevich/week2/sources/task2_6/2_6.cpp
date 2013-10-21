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
	string name;
	string date;
	double price;
	double vwap;
	unsigned int volume;
	double f1;
	double t1;
	double f2;
	double f3;
	double f4;
	};


ifstream f1;
ofstream f2;


void reader(msg &t, bool &err)
{	
	for(unsigned int i=0;i<9;i++)
	{
		char c;
		if(f1.read(reinterpret_cast<char*>(&c),sizeof (char))==0) 
			{
				err=1;
				return;
			}
		t.name+=c;
	}
	for(unsigned int i=0;i<8;i++)
	{
		char c;
		f1.read(reinterpret_cast<char*>(&c),sizeof (char));
		t.date+=c;
	}
	f1.read(reinterpret_cast<char*>(&t.price),sizeof (double));
	f1.read(reinterpret_cast<char*>(&t.vwap),sizeof (double));
	f1.read(reinterpret_cast<char*>(&t.volume),sizeof (unsigned int));
	f1.read(reinterpret_cast<char*>(&t.f1),sizeof (double));
	f1.read(reinterpret_cast<char*>(&t.t1),sizeof (double));
	f1.read(reinterpret_cast<char*>(&t.f2),sizeof (double));
	f1.read(reinterpret_cast<char*>(&t.f3),sizeof (double));
	f1.read(reinterpret_cast<char*>(&t.f4),sizeof (double));

}


void writer(string &s,long long &t,double vwap,unsigned int volume,double ff2)
{
	f2.write(reinterpret_cast<char*>(&s),sizeof (s));
	f2.write(reinterpret_cast<char*>(&t),sizeof (t));
	f2.write(reinterpret_cast<char*>(&vwap),sizeof (vwap));
	f2.write(reinterpret_cast<char*>(&volume),sizeof (volume));
	f2.write(reinterpret_cast<char*>(&f2),sizeof (ff2));
}


inline void process(msg &x)
{
	int year, month, day;
	sscanf(x.date.c_str(),"%4d%2d%2d",&year,&month,&day);
	long long pp= 1ll*year*372+1ll*month*31+1ll*day-1;
	writer(x.name,pp,x.vwap,x.volume,x.f2);
}
void closer()
{
	f1.close();
	f2.close();	
}

int main()
{
	f1.open("input.txt", ios_base::in | ios_base::binary);
	f2.open("output.txt",ios_base::out| ios_base::binary);
	bool err=0;
	if (!f1.is_open() || !f2.is_open()) 
	{
		closer();
		return 0;
	}
	while (!f1.eof())
	{
		msg x;
		reader(x,err);
		if (err) break;
		process(x);
	}
	closer();
	return 0;
}