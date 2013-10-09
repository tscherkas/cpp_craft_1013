#include <fstream>
#include <string>
#include <vector>
#include <queue>


void RemoveIslandFromMap(std::vector<std::string>& map, std::pair<int, int> o)
{
    std::queue<std::pair<int, int>> island;
    island.push(o);

    while (!island.empty())
    {
        o = island.front();
        island.pop();

        for (int i = o.first; i < map.size(); ++i)
        {
            for (int j = o.second; j < map[i].size(); ++j)
            {
            }
        }
    }
}

int main()
{
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");

    std::vector<std::string> map;

    while (!in.eof())
    {
        std::string str;
        std::getline(in, str);
        map.push_back(str);
    }
    
    int count = 0;
    for (int i = 0; i < map.size(); ++i)
    {
        for (int j = 0; j < map[i].size(); ++j)
        {
            if (map[i][j] == 'o')
            {
                ++count;
                RemoveIslandFromMap(map, std::make_pair(i, j));
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }

    in.close();
    out.close();
}