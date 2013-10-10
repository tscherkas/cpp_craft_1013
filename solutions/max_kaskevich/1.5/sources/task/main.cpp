#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <locale>
#include <vector>


struct WorldMap
{
    std::vector<std::string> data;

    std::string& operator[](size_t i)
    {
        return data[i];
    }

    std::string& get_new_line()
    {
        data.push_back(std::string());
        return data.back();
    }

    int x_max()
    {
        return data.front().size();
    }

    int y_max()
    {
        return data.size();
    }
};


void mark_the_land(WorldMap& map, int x, int y)
{
    map[y][x] = 'x';
    if(x + 1 < map.x_max() && map[y][x+1] == 'o')
    {
        mark_the_land(map, x + 1, y);
    }
    if(x > 0 && map[y][x-1] == 'o')
    {
        mark_the_land(map, x - 1, y);
    }
    if(y + 1 < map.y_max() && map[y+1][x] == 'o')
    {
        mark_the_land(map, x, y + 1);
    }
    if(y > 0 && map[y-1][x] == 'o')
    {
        mark_the_land(map, x, y - 1);
    }

}

int main( int argc, char* argv[] )
{
    std::ifstream input(SOURCE_DIR "/tests/test1.txt");
    
    WorldMap map;
    while(!input.eof())
    {
        std::getline(input, map.get_new_line());
    }

    int lands = 0;

    for(int x = 0; x < map.x_max(); ++x)
    {
        for(int y = 0; y < map.y_max(); ++y)
        {
            if(map[y][x] == 'o')
            {
                mark_the_land(map, x, y);
                ++lands;
            }
        }
    }
    std::cout << lands << std::endl;
}
