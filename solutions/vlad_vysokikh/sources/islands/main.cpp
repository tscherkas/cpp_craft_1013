#include <fstream>
#include <string>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<bool>> IslandMap;

int mark_island(IslandMap& sourceMap, IslandMap& helperMap, int x, int y)
{
    if (sourceMap[x][y] && !helperMap[x][y]) {
        helperMap[x][y] = true;
        if ( x != 0) {
            mark_island(sourceMap, helperMap, x - 1, y);
        }
        if ( x != ( sourceMap.size() - 1 )) {
            mark_island(sourceMap, helperMap, x + 1, y);
        }
        if ( y != 0) {
            mark_island(sourceMap, helperMap, x, y - 1);
        }
        if ( y != ( sourceMap[y].size() - 1 )) {
            mark_island(sourceMap, helperMap, x, y + 1);
        }
        return 1;
    }
    return 0;
}

int main()
{
    std::ifstream input_file	( SOURCE_DIR "/tests/data/003/input.txt" );
    std::ofstream output_file	( SOURCE_DIR "/tests/data/003/output.txt");


    IslandMap vect, helperVect;
    int strCount=0;
    std::string str;

    while ( !input_file.eof() ) {
        std::getline(input_file, str);
        if ( !str.empty() ) {
            std::vector<bool> tmp(str.size(), false);
            helperVect.push_back(tmp);
            for (int i=0; i<str.size(); i++){
                if (str.at(i) == 'o') {
                    tmp[i] = true;
                }
            }
            vect.push_back(tmp);
            strCount++;
        }
    }
    int islandCount = 0;
    for (int i=0;i<strCount; i++) {
        for (int j=0; j<vect[i].size();j++) {
            islandCount += mark_island(vect, helperVect, i, j);
        }
    }

    output_file << islandCount;

    input_file.close();
    output_file.close();

}

