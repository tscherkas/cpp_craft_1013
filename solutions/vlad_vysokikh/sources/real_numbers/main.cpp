#include <fstream>
#include <vector>
#include <math.h>
#include <iostream>

const double epsilon = 0.0001;

int main()
{
    std::ifstream input_file	( SOURCE_DIR "/tests/data/002/input.txt" );
    std::ofstream output_file	( SOURCE_DIR "/tests/data/002/output.txt");

    int N;
    input_file >> N;

    std::vector<double> codes;
    double value;
    for (int i=0; i<N; i++) {
        input_file >> value;
        codes.push_back(value);
    }

    input_file.peek();
    while ( !input_file.eof() ) {
        bool found = false;
        input_file >> value;

        for (int i=0; i<N; i++) {
            if ( fabs( codes[i] - value ) < epsilon ) {
                found = true;
                break;
            }
        }
        output_file << ( found ? "YES" : "NO" ) << std::endl;
        input_file.peek();
    }
    output_file.close();
    input_file.close();
}

