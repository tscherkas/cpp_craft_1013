#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

float stringToFloat(std::string &str){
    std::stringstream formatter;
    float result;
    formatter << str << endl;
    formatter >> result;
    formatter << setprecision(4) << std::setiosflags(std::ios_base::fixed) << (result - 0.00004);//-0.00004 allow to avoid rounding
    formatter >> result;
    return result;
}

void writeResult(bool result){
    std::fstream resultFile( "output.txt", std::fstream::out | std::fstream::app );
    if(!resultFile.good()){
        cout << "Can't open file to write a result" << endl;
    }
    resultFile << (result ? "YES" : "NO") << std::endl;
    resultFile.close();
}

int main(){
    std::ifstream input("input.txt");
    std::string line;
    int count = 0;
    int keyRowCount = 0;
    vector<float> codes;

    if(input.good()){
        while(!input.eof()){
            std::getline(input, line);
            count++;
            std::stringstream stream(line);

            if(count == 1){
                stream >> keyRowCount;
                std::cout << "Number of codes row: " << keyRowCount << std::endl;
                if(keyRowCount <= 0){
                    std::cout << "Error: illigal document format, please put integer into first row" << std::endl;
                    return 0;
                }
            } else if((count - 1) <= keyRowCount){
                codes.push_back(stringToFloat(line));
                std::cout << "Code: " << codes.back() << std::endl;
            } else {
                if(line.size() == 0){
                    continue;
                }
                std::vector<float>::iterator it = codes.begin();
                bool isCodeFound = false;
                for(it; it != codes.end(); ++it){
                    if((*it) == stringToFloat(line)){
                        isCodeFound = true;
                    }
                }
                writeResult(isCodeFound);
                std::cout << (isCodeFound ? "YES" : "NO") << std::endl;
            }
        }
    } else {
        std::cout << "Can't open file " << std::endl;
    }
    input.close();
    return 0;
}
//h:\dev\cpp_craft_1013\solutions\nikolay_nikiforchuk\task_1.4\task_1_4\

