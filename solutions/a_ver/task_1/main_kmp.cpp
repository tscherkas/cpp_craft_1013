/*
 * Search algorithm in standard library (libstdc++-v3 4.8.1) implemented a
 * trivial way therefore may work not fats
 *
 * http://gcc.gnu.org/viewcvs/gcc/tags/gcc_4_8_1_release/libstdc++-v3/include/bits/basic_string.tcc?view=markup
 * 
 * This implementation used the Knuth-Morris-Pratt algorithm 
 * ("Introduction to Algorithms" Thomas H. Corman and other)
 *
 * */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define EXPECT_INPUT_LEN 100000

void compute_prefix(int prefix[], const string &needle){
    int m = needle.length()-1;
    int k = -1;
    prefix[0] = k;
    for(int q=1; q <= m; q++){
        while(k > -1 && needle[m - (k+1)] != needle[m - q]){
            k = prefix[k]; 
        }
        if(needle[m - (k+1)] == needle[m - q]){
            k++;
        }
        prefix[q] = k;
    }
}

int kmp_matcher(const string &haystack, const string &needle){
    int n = haystack.length();
    int m = needle.length() - 1;
    int prefix[m];

    compute_prefix(prefix, needle);

    int q = -1;
    for(int i=0; i < n; i++){
        while(q > -1 && needle[m - (q+1)] != haystack[i]){
            q = prefix[q];
        }
        if(needle[m - (q+1)] == haystack[i]){
            q++;
        }
        if(q == m){
            return i - m;
        }
    }
    return -1;
}


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
    int offset;
    text.reserve(EXPECT_INPUT_LEN);

    read_line(i_fs, text);
    read_line(i_fs, line);
    
    while(!line.empty()){
        offset = kmp_matcher(text, line);
        if(offset != -1){
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
