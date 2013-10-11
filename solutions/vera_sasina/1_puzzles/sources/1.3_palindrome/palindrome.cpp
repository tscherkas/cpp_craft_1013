#include "palindrome.h"

using namespace std;
//function to remove ignore characters and  to lower
void string_del(string& str)
{
	for(int i = 0; i < str.size(); i++)
	{
		if(isalpha(str.at(i)))
			str[i] = tolower(str.at(i));
		if(str.at(i) == ' ' || str.at(i) == '\\' || str.at(i) == '-')
			str.erase(i--, 1);
	}
}
//function to find substring
bool find_key(string& key, string str)
{
	string temp_key;
	string_del(str);
	for(int i = key.size()-1; i >= 0; i--)
		temp_key.push_back(key.at(i));
	string_del(temp_key);
	if(str.find(temp_key) != string::npos)
		return true;
	else
		return false;
}