#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;


void mark_island(vector<string>& data, int i, int j){
    stack<pair<int,int> > st;
    pair<int, int> p;
    int data_size = data.size()-1;
    int length = data[0].length()-1;
    
    st.push(make_pair(i,j));
    while(!st.empty()){
        p = st.top();
        st.pop();
        data[p.first][p.second] = 'x';

        if(p.second > 0 && data[p.first][p.second-1] == 'o'){
            st.push(make_pair(p.first, p.second-1));
        }
        if(p.second < length && data[p.first][p.second+1] == 'o'){
            st.push(make_pair(p.first, p.second+1));
        }
        if(p.first > 0 && data[p.first-1][p.second] == 'o'){
            st.push(make_pair(p.first-1, p.second));
        }
        if(p.first < data_size && data[p.first+1][p.second] == 'o'){
            st.push(make_pair(p.first+1, p.second));
        }
    }
}

int main(){
    ifstream i_fs(SOURCE_DIR "/Input.txt");
    ofstream o_fs(SOURCE_DIR "/Output.txt");
    if(!i_fs){
        cout << "Could not open input file" << endl;
        return 1;
    }
    if(!o_fs){
        cout << "Could not open output file" << endl;
        return 1;
    }
    vector<string> data;
    string line;
    int count = 0;

    while(!i_fs.eof()){
        i_fs >> line;
        data.push_back(line);
    }
    int data_length = data.size();
    int length = data[0].length();

    for(int i=0; i < data_length; i++){
        for(int j=0; j < length; j++){
            if(data[i][j] == 'o'){
                mark_island(data, i, j);
                count++;
            }
        }
    }
    o_fs << count;
    return 0;
}
