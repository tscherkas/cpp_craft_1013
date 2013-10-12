#include <fstream>
#include <string>
#include <set>

int main( int argc, char* argv[] )
{
    std::ifstream input(SOURCE_DIR "/tests/data/task1.4/input.txt");
    std::ofstream output(SOURCE_DIR "/tests/data/task1.4/output.txt");
	if ( !(input && output) )
	{
		return 1;
	}    

	int n = 0;
	input >> n;

	double x;
	std::set<int> pwds;
	while(n-- && input >> x)
	{
		pwds.insert(x * 10000.0f);
	}

	while(input >> x)
	{
		output << (pwds.find(x * 10000.0f) != pwds.end() ? "YES" : "NO") << std::endl;
	}    

}
