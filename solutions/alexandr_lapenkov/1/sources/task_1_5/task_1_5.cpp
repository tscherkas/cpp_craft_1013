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

	struct point
	{
		int x,y;
		point(int x, int y)
		{
			point::x=x;
			point::y=y;
		}
	};

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
       
    inline void bfs_move(queue<point>&q, const int tx, const int ty)
    {
    
        if(tx<0||ty<0||tx>=n||ty>=m)return ;
        if(a[tx][ty]!='o')return ;
        
        q.push(point(tx,ty));
          
        a[tx][ty]='~';
          
    }  


    void bfs_component(const int sx, const int sy)
    {
        queue<point>q;
        int tx,ty;
 
        q.push(point(sx,sy));
    
        a[sx][sy]='~';
    
        while(!q.empty())
        {
            tx=q.front().x; ty=q.front().y;
            q.pop();
           
            bfs_move(q,tx+1,ty);
            bfs_move(q,tx-1,ty);
            bfs_move(q,tx,ty+1);
            bfs_move(q,tx,ty-1);
        }

    }
            
    void process()
    {            
        string buf;
        int ans=0;
       
        while(!in.eof())
        {
            if(!(in>>buf))break;
            a.push_back(buf);   
        }

        n=(int)a.size();
        m=(int)a[0].size();
          
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(a[i][j]=='o')
                {
                    ans++;
                    bfs_component(i,j);
                }
        
        out<<ans;
                 
    }

};


int main()
{
       
    Solution s;
    s.process();
       
    return 0;  
}

