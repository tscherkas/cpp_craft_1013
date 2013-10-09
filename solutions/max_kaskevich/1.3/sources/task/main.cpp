#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <locale>

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
    setlocale(LC_ALL, "Russian");
    std::ifstream input(SOURCE_DIR "/tests/test1.txt");

    std::string text;
    read_line(input, text);

    std::string line;
    while(!input.eof())
    {
        read_line(input, line);
        std::reverse(line.begin(), line.end());
        if(line.empty())
        {
            continue;
        }
        if (text.find(line) != std::string::npos)
        {
            std::cout<< "YES" <<std::endl;
        }
        else
        {
            std::cout<< "NO" <<std::endl;
        }
    }
    

}
