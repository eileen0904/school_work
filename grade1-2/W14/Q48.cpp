//UVa989

#include <iostream>
#include <cstring>
using namespace std;

int map[9][9], row[9][10], col[9][10], square[9][10];
int n, flag;

void backtrace(int count)
{
    int i, j, k;
    if(flag){return;}
    if(count==n*n*n*n)
    {
        flag = 1;
        for(i=0;i<n*n;i++)
        {
            for(j=0;j<n*n;j++)
            {
                cout<<map[i][j];
                if(j!=n*n-1){cout<<" ";}
            }
            cout<<endl;
        }
    }
    int r = count / (n*n);
    int c = count % (n*n);
    //cout<<"count:"<<count<<endl;
    if(map[r][c]!=0)
    {
        backtrace(count+1);
    }
    else
    {
        int s = r/n*n + c/n;
        for(k=1;k<=n*n;k++)
        {
            if(row[r][k]==0 && col[c][k]==0 && square[s][k]==0)
            {
                row[r][k] = 1;
                col[c][k] = 1;
                square[s][k] = 1;
                map[r][c] = k;
                backtrace(count+1);
                map[r][c] = 0;
                row[r][k] = 0;
                col[c][k] = 0;
                square[s][k] = 0;
            }
        }
    }
}

int main()
{
    int i, j;
    bool first = true;
    while(cin>>n)
    {
        memset(map, 0, sizeof(map));
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(square, 0, sizeof(square));
        int N = n*n;
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                cin>>map[i][j];
                row[i][map[i][j]] = 1;
                col[j][map[i][j]] = 1;
                square[i/n*n+j/n][map[i][j]] = 1;
            }
        }
        if(!first)
        {
            cout<<endl;
        }
        flag = 0;
        backtrace(0);
        if(!flag)
        {
            cout<<"NO SOLUTION"<<endl;
        }
        first = false;
    }
    return 0;
}
