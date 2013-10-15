#include <iostream>
#include <math.h>
#include <algorithm>
#include <set>
#include <utility>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

/*
* Alexandr Lapenkov
* Cpp_craft, task 1.3
*/

using namespace std;

class Solution
{

private:
              
     string text, line;
       
     ifstream in;
     ofstream out;
       
     void cut(string &s)
     {
 
     string res;
   
     for(string::iterator i=s.begin();i<s.end();i++)
          if((*i)!=' '&&(*i)!='\\'&&(*i)!='-')
              res+=((*i)>='?'&&(*i)<='?')?(*i)-'?'+'?':tolower((*i));
 
     s=res;
 
     }

public:

    Solution()
    {
        in.open(SOURCE_DIR"/input.txt",ios_base::in);
        out.open(SOURCE_DIR"/output.txt",ios_base::out);
    }
            
    ~Solution()
    {
        in.close();
        out.close();
    }
       
    void process()
    {
                            
        getline(in,text);
        cut(text);
        reverse(text.begin(),text.end());
       
        while(!in.eof())
        {
            getline(in,line);
            if(in.eof())break;
            cut(line);
					
            if(text.find(line)!=string::npos)
                out<<"YES\n";
            else
                out<<"NO\n";
         }
       
    }
            
};


int main()
{
       
    Solution s;
    s.process();
       
    return 0;  
}
