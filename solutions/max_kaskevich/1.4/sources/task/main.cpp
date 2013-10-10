#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <locale>
#include <set>


int get_int(std::string& str)
{
    return std::atof(str.c_str()) * 10000.0f;
}


int main( int argc, char* argv[] )
{
    std::ifstream input(SOURCE_DIR "/tests/test1.txt");
    
    std::string x;
    std::getline(input, x);
    int n = std::atoi(x.c_str());

    std::set<int> pwds;
    for(int i = 0; i < n; ++i)
    {
        std::getline(input, x);
        pwds.insert(get_int(x));
    }

    while(!input.eof())
    {
        std::getline(input, x);
        if(x.empty())
        {
            continue;
        }
        std::cout << (pwds.find(get_int(x)) != pwds.end() ? "YES" : "NO") << std::endl;
    }    

}
