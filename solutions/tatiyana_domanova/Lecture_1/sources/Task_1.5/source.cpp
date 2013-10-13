#include <fstream>
#include <vector>
#include <string>

using namespace std;

void readData(const ifstream &in, vector<vector<bool>*> &p, vector<vector<bool>*> &map) {
	string s;
	int row = 0;
	while (!in.eof()) {
		getline(in,s);
		p.push_back(new vector<bool> ());
		map.push_back(new vector<bool> ());
		
		for (int i=0; i<s.length(); i++)
			if ( s[i] == '~') {
				p[row]->push_back(0);
				map[row]->push_back(0);
			} else {
				p[row]->push_back(0);
				map[row]->push_back(1);
			}
		row++;
	}
}

void markIsland(vector<vector<bool>*> &p,const vector<vector<bool>*> &map, int x, int y) {
	(*p[x])[y] = 1;
	if (x>0 && (*p[x-1])[y] == 0 && (*map[x-1])[y] == 1) 
		markIsland(p,map,x-1,y);
	if (x<map.size()-1 && (*p[x+1])[y] == 0 && (*map[x+1])[y] == 1) 
		markIsland(p,map,x+1,y);
	if (y>0 && (*p[x])[y-1] == 0 && (*map[x])[y-1] == 1) 
		markIsland(p,map,x,y-1);
	if (y<map[x]->size()-1 && (*p[x])[y+1] == 0 && (*map[x])[y+1] == 1) 
		markIsland(p,map,x,y+1);
}

int countIslands(vector<vector<bool>*> &p,const vector<vector<bool>*> &map) {
	int count = 0;
	for (int i=0; i<map.size(); i++)
		for (int j=0; j<map[i]->size(); j++)
			if ((*p[i])[j] == 0 && (*map[i])[j] == 1) {
				count ++;
				markIsland(p, map, i,j);
			} else {
				(*p[i])[j] = 1;
			}
	return count;
}

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	vector<vector<bool>*> p, map;
	readData(in,p,map);
	out << countIslands(p,map);
	for (int i=0; i<map.size(); i++) {
		delete map[i];
		delete p[i];
	}
	in.close();
	out.close();
	return 0;
}