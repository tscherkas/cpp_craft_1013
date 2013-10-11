#include <iostream>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <vector>

#define EPS 1e-4

/*
* Alexandr Lapenkov
* Cpp_craft, task 1.4
*/

using namespace std;

class Solution{
      
private:
     
     int n;
     double x;
     vector<double>a;
     
     ifstream in;
     ofstream out;
   
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
        
                 in>>n;
                 a.reserve(n);
                 
                 for(int i=0;i<n;i++)
                 {
                         in>>x;
                         a.push_back(x);
                 }
              
              //Sort the vector to perform binary search later.
              sort(a.begin(),a.end());
              
               while(!in.eof())
               {
                            vector<double>::iterator it;
                            
                            in>>x;
                            
                            //eof() doesn't return "true" just after the last element, but reads one more empty string.
                            if(in.eof())break;
                            
                               it = lower_bound(a.begin(),a.end(),x);
                             
                            //Checking the first element which is greater or equal to X
                             
                               if(it!=a.end() && fabs((*it)-x)<=EPS)
                                  out<<"YES\n";
                               else
                                  if(it!=a.begin())
                                  {
                                                   //Checking the first element which is less than X 
                                                    it--;
                                                    
                                                    if(fabs((*it)-x)<=EPS)
                                                      out<<"YES\n";
                                                    else 
                                                      out<<"NO\n";
                                  }
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
