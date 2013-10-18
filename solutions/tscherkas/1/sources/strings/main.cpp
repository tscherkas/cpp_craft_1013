#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
class My_iterator : public std::iterator<std::input_iterator_tag , char>
{
	std::string::iterator  it;
public:
	My_iterator(){};
	My_iterator(std::string::iterator i):it(i) {while(*it==' '||*it=='/'||*it=='\\'||*it=='-') ++it;}
	My_iterator(const My_iterator& my_it) : it(my_it.it) {}
	My_iterator& operator++() {++it;	while(*it==' '||*it=='/'||*it=='\\'||*it=='-') ++it; return *this;}
	My_iterator operator++(int) {My_iterator tmp(*this); operator++(); return tmp;}
	bool operator==(const My_iterator& rel_it) {return it==rel_it.it;}
	bool operator!=(const My_iterator& rel_it) {return it!=rel_it.it;}
	void operator=(const My_iterator& my_it) { it=my_it.it;}
	char& operator*() {return *it;}
};




int main( int argc, char* argv[] )
{
	std::ifstream input_file( SOURCE_DIR "/tests/strings/input.txt" );
	if(!input_file.is_open())
		return 0;
	std::ofstream output_file("output.txt" );
	if(!output_file.is_open())
		return 0;
	std::string original_text, key;
	if( !input_file.eof() )
	{
		std::getline( input_file, original_text );
		std::transform(original_text.begin(),
			original_text.end(),
			original_text.begin(),
			::tolower);
	}
    while( !input_file.eof() )
	{
		std::getline( input_file, key );
		if(!key.empty())
		{
			std::transform(key.begin(),
                        	key.end(),
                        	key.begin(),
                        	::tolower);
			std::reverse(key.begin(),key.end());  		
			std::cout<<original_text<<"   "<<key<<std::endl;
			My_iterator it1 = key.begin(),end1 = key.end();
			My_iterator it2=original_text.begin(), end2 = original_text.end();
			My_iterator it = std::search(it2, end2,it1,end1);
			if(it==end2)
				output_file << "NO"  << std::endl;
			else
				output_file << "YES"  << std::endl;
		
		}
	}
	input_file.close();
	output_file.close();
}
