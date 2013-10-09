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

		int i = o.first;
		int j = o.second;
		map[i][j] = ' ';


		if (j < map[i].length()-1 && map[i][j+1] == 'o')
		{
			island.push(std::make_pair(i,j+1));
		}
		if (j > 0 && map[i][j-1] == 'o')
		{
			island.push(std::make_pair(i,j-1));
		}
		if (i < map.size()-1 && map[i+1][j] == 'o')
		{
			island.push(std::make_pair(i+1,j));
		}
		if (i > 0 && map[i-1][j] == 'o')
		{
			island.push(std::make_pair(i-1,j));
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

	out << count;

    in.close();
    out.close();
}