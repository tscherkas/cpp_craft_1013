#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <cmath>


int main()
{
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");

    int N;
    in >> N;

    double code;
    std::set<int> codes;
    for (int i = 0; i < N; ++i)
    {
        in >> code;
        int x = code*10000.0;
        codes.insert(x);
    }

	while(!in.eof())
	{
        in >> code;
        int x = code*10000.0;

        out << ((codes.find(x) != codes.end()) ?  "YES" : "NO") << std::endl;
       
	}

    in.close();
    out.close();
}