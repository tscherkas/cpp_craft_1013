#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

#define EXPECT_INPUT_LEN 100000

void read_line(ifstream &i_fs, string &line){
    char c = '\0';
    if(!line.empty()){
        line.erase();
    }
    c = i_fs.get();
    while(!i_fs.eof()  && c != '\n'){
        if(c != ' ' && c != '-' && c != '\\'){
            line.push_back(toupper(c));
        }
        c = i_fs.get();
    }
}

int main(int argc, char* argv[])
{
    ifstream i_fs(SOURCE_DIR "/Input.txt");
    if(!i_fs){
        cout << "Could not open input file" << endl;
        return 1;
    }
    ofstream o_fs(SOURCE_DIR "/Output.txt");
    if(!o_fs){
        cout << "Could not open output file" << endl;
        return 1;
    }
    string text;
    string line;
    string::iterator it;
    text.reserve(EXPECT_INPUT_LEN);

    read_line(i_fs, text);
    read_line(i_fs, line);
    
    while(!line.empty()){
        it = std::search(text.begin(), text.end(),
                         line.rbegin(), line.rend());
        if(it != text.end()){
            o_fs << "YES" << endl;
        }else{
            o_fs << "NO" << endl;
        }
        read_line(i_fs, line);
    }
    i_fs.close();
    o_fs.close();

    return 0;
}
