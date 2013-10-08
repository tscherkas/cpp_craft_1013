#include <fstream>
#include <string>
#include <algorithm>

const int str_capacity = 100000;
//const char empty_char = '';

void optimize_string(std::string& line)
{
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    std::replace(line.begin(), line.end(), '\\', ' ');
    std::replace(line.begin(), line.end(), '/', ' ');
    std::replace(line.begin(), line.end(), '-', ' ');
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
}

int main( int argc, char* argv[] )
{
    std::ifstream input_file	( SOURCE_DIR "/tests/data/001/input.txt" );
    std::ofstream output_file	( SOURCE_DIR "/tests/data/001/output.txt");

    std::string line;
    std::getline( input_file, line );

    optimize_string(line);

    std::string test_line;
    while ( true ) {
        std::getline( input_file, test_line );
        if ( input_file.eof() ) {
            break;
        }
        optimize_string(test_line);
        auto result = std::search( line.rbegin(), line.rend(), test_line.begin(), test_line.end() );
        result != line.rend() ? output_file << "YES" << std::endl : output_file << "NO" << std::endl;
    }

    output_file.close();
    input_file.close();
}
