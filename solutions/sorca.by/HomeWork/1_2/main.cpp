#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>

bool isEquals (float a, float b, float eps);

int main()
{
    std::string yes = "YES";
    std::string no = "NO";
    float eps = 0.0001;
    float pass;

    //open
    std::ifstream inFile	( "../1_2/data/input.txt");
    std::ofstream outFile	( "../1_2/data/output.txt");

    long N = 1;
    inFile >> N;
    if (N == 0) {
        return 1;
    }

    float *codes = new float [N];
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


bool isEquals(float a, float b, float eps) {
        return fabs(a-b) < eps;
}

