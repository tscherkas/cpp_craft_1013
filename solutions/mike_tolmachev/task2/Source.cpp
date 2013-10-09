#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>


int main()
{
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");

    int N;
    in >> N;

    float code;
    std::vector<float> codes;
    for (int i = 0; i < N; ++i)
    {
        in >> code;
        codes.push_back(code);
    }

	while(!in.eof())
	{
        in >> code;

        bool res = true;
        for (auto i = codes.begin(); i != codes.end(); ++i)
        {
            if (fabs(*i - code) < 0.0001)
            {                
                res = false;
                break;
            }
        }
        
        out << ((res) ?  "YES" : "NO") << std::endl;
       
	}

    in.close();
    out.close();
}