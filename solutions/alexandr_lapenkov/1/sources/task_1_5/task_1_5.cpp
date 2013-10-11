#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

/*
* Alexandr Lapenkov
* Cpp_craft, task 1.5
*/

using namespace std;

class Solution
{

private:
         
         int n,m;
         vector<string>a;
         
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
       
       //Check and add cell
       inline void bfs_move(queue<int>&x, queue<int>&y, const int tx, const int ty)
       {
              
              //bounds check
              if(tx<0||ty<0||tx>=n||ty>=m)return ;
              if(a[tx][ty]!='o')return ;
       
              //Add cell to the queues
              x.push(tx);
              y.push(ty);
          
              a[tx][ty]='~';
          
          }  


          //Marks one "island"
          void bfs_component(const int sx, const int sy)
          {
           queue<int>x,y;
           int tx,ty;
 
           //Add start cell to the queues
               x.push(sx);
               y.push(sy);
    
               a[sx][sy]='~';
    
               while(!x.empty())
               {
                      tx=x.front(); ty=y.front();
                        x.pop(); y.pop();
                        
                        //Try to move around the cell
                        bfs_move(x,y,tx+1,ty);
                        bfs_move(x,y,tx-1,ty);
                        bfs_move(x,y,tx,ty+1);
                        bfs_move(x,y,tx,ty-1);
               }

            }
            
            void process()
            {            
               string buf;
               int ans=0;
       
                while(!in.eof())
                {
                 in>>buf;
				 if(in.eof())break;
                 a.push_back(buf);   
                }

                n=a.size();
                m=a[0].size();
          
                for(int i=0;i<n;i++)
                        for(int j=0;j<m;j++)
                                if(a[i][j]=='o')
                                {
                                //Mark the "island"
                                ans++;
                                bfs_component(i,j);
                                }
        
                out<<ans;
                 
             }

};


int main(){
       
      Solution s;
      s.process();
       
    return 0;  
}

