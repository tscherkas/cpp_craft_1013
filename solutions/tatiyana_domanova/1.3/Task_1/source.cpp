#include <fstream>
#include <string>
#include <iostream>

using namespace std;

bool isSpaceChar(char c) {
	if (c == ' ')
		return true;
	if (c == '-') 
		return true;
	if (c == '\\')
		return true;
	return false;
}

string reverse(string s) {
	string res;
	for (int i=s.length()-1; i>=0; i--)
		res+=s[i];
	return res;
}

bool equals(char c1, char c2) {
	if (c1 >= 'À' && c1 <= 'ß') 
		c1 = c1-('À'-'à'); 
	if (c2 >= 'À' && c2 <= 'ß') 
		c2 = c2-('À'-'à');

	return (tolower(c1) == tolower(c2));
}

bool contains(string text, string key) {
	for (int i=0; i<text.length()-key.length(); i++) {
		bool flag = true;
		for (int j=0; j<key.length(); j++)
			if (!equals(text[i+j],key[j])) {
				flag = false;
				break;
			}
		if (flag)
			return true;
	}
	return false;		
}

string cutSpaces(string s) {
	string res = "";
	for (int i=0; i<s.length(); i++)
		if (!isSpaceChar(s[i])) {
			res += s[i];
		}
	return (res);
}

string toString(bool b) {
	if (b) return "YES";
	else return "NO";
}

int main() {
	string text, key;
	ifstream in("input.txt");
	ofstream out("output.txt");
	getline(in, text);
	text = cutSpaces(text);
	while (!in.eof()) {
		getline(in, key);
		out << toString(contains(text, reverse(cutSpaces(key)))) << endl;
	}
	return 0;
}