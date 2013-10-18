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

bool equals(char c1, char c2) {
	if (c1 >= '�' && c1 <= '�') 
		c1 = c1-('�'-'�'); 
	if (c2 >= '�' && c2 <= '�') 
		c2 = c2-('�'-'�');

	return (tolower(c1) == tolower(c2));
}

bool contains(string &text, string &key) {
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

void cutSpaces(string &s) {
	string res = "";
	for (int i=0; i<s.length(); i++)
		if (!isSpaceChar(s[i])) {
			res += s[i];
		}
	s = res;
}

string toString(bool b) {
	if (b) 
		return "YES";
	else 
		return "NO";
}

int main() {
	string text, key;
	ifstream in("input.txt");
	ofstream out("output.txt");
	getline(in, text);
	cutSpaces(text);
	while (!in.eof()) {
		getline(in, key);
		cutSpaces(key);
		reverse(key.begin(), key.end());
		out << toString(contains(text, key)) << endl;
	}
	in.close();
	out.close();
	return 0;
}