#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <locale>
#include <set>

void read_line(std::ifstream& stream, std::string& line)
{
    std::getline(stream, line);
    line.erase(
        std::remove_if(line.begin(), line.end(), [](const char& symbol)
            { return symbol == ' ' || symbol == ',' || symbol == '-' || symbol == '\\';}),
        line.end());

    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
}

int main( int argc, char* argv[] )
{
    std::ifstream input(SOURCE_DIR "/tests/test1.txt");
    
    int n = 0;
    input>>n;

    std::set<float> passes;

    int x;
    for(int i=0; i<n; ++i)
    {
        input>>x;
        passes.insert(x);
    }


    while(!input.eof())
    {

    }
    

}
