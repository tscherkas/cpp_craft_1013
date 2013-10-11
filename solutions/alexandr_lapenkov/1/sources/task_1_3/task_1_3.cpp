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
       
       
       //Removes {' ','\','-'}. Translates to lower case.
       void cut(string &s)
       {
 
         string res;
   
                for(int i=0;i<s.size();i++)
                        if(s[i]!=' '&&s[i]!='\\'&&s[i]!='-')
                        //Tolower for russian and english letters.
                          res+=(s[i]>='À'&&s[i]<='ß')?s[i]-'À'+'à':tolower(s[i]);
 
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
       
                      //Format and reverse input text.
                       cut(text);
                       reverse(text.begin(),text.end());
       
                        while(!in.eof())
                        {
                                        
                                        getline(in,line);
                                        if(in.eof())break;
                                        //Format the query.
                                        cut(line);
					
                                        if(text.find(line)!=string::npos)
                                                                         out<<"YES\n";
                                        else
                                                                         out<<"NO\n";
                           }
       
            }
            
};


int main(){
       
       Solution s;
       s.process();
       
    return 0;  
}
