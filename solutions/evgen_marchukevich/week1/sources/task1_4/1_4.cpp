#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <list>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <vector>

#define pb(VALUE) push_back(VALUE)
#define mp(FST,SEC) make_pair(FST,SEC)
#define len(STR) STR.length()
#define F first
#define S second


using namespace std;


int main()
{
	ifstream f1("input.txt");
	ofstream f2("output.txt");
	int n;
	f1 >> n;
	vector<double> a;
	for(int i=0;i<n;i++)
	{
		double x;
		f1 >> x;
		a.pb(x);
	}
	sort(a.begin(),a.end());
	while (!f1.eof())
	{
		double x;
		f1 >> x;
		int z;
		z=lower_bound(a.begin(),a.end(),x)-a.begin()-1;
		if (fabs(a[z]-x)<1e-4 || (z>0 && fabs(a[z-1]-x)<1e-4))
				f2 << "YES" << endl; else
				f2 << "NO" << endl;
			
	}
	return 0;
}
