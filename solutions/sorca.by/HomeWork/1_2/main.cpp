#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>

bool isEquals (double a, double b, double eps);

int main()
{
	static const double eps = 0.00001;
	static const std::string yes = "YES";
	static const std::string no = "NO";
	double pass;

	//open
	std::ifstream inFile	(BINARY_DIR "input.txt");
	std::ofstream outFile	(BINARY_DIR "output.txt");

	long N = 1;
	inFile >> N;
	if (N <= 0) {
		return 1;
	}

	double  *codes = new double [N];
	for (int i = 0; i<N; ++i){
		inFile >> codes[i];
	}

	//should be optimized for "std::binary_search"
	bool eqNum = false;
	while(true) {
		inFile >> pass;
		if(inFile.eof())
			break;
		eqNum = false;
		for(int i = 0; i < N; ++i){
			if(isEquals(pass, codes[i], eps)) {
				eqNum = true;
				break;
			}
		}
		outFile << (eqNum ? yes : no) << std::endl;
		if(inFile.eof()) {
			break;
		}
	}
	//close
	delete[] codes;
	outFile.close();
	inFile.close();
	return 0;
}


bool isEquals(double a, double b, double eps) {
	return fabs(a-b) < eps;
}

