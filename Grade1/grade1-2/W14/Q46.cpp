//UVa118

#include <cstring>
#include <iostream>
using namespace std;

int main() 
{
    int map[50][50], visited[50][50];
    memset(map, 0, sizeof(map));
    memset(visited, 0, sizeof(visited));
    int i, n = 0, m = 0, sx = 0, sy = 0;
    cin >> n >> m;
    string f, cmd;
    while (cin >> sx >> sy >> f >> cmd) 
    {
        int lost = 0;
        for (i = 0; i < cmd.size(); i++) 
        {
            if (cmd[i] == 'R') 
            {
                switch (f[0]) {
                    case 'N':
                        f[0] = 'E';
                        break;
                    case 'S':
                        f[0] = 'W';
                        break;
                    case 'W':
                        f[0] = 'N';
                        break;
                    case 'E':
                        f[0] = 'S';
                        break;
                }
            } 
            else if (cmd[i] == 'F')
            {
                switch (f[0]) 
                {
                    case 'N':
                        sy++;
                        break;
                    case 'S':
                        sy--;
                        break;
                    case 'W':
                        sx--;
                        break;
                    case 'E':
                        sx++;
                        break;
                }
            } 
            else 
            {
                switch (f[0]) 
                {
                    case 'N':
                        f[0] = 'W';
                        break;
                    case 'S':
                        f[0] = 'E';
                        break;
                    case 'W':
                        f[0] = 'S';
                        break;
                    case 'E':
                        f[0] = 'W';
                        break;
                }
            }
            if (sx < 0 || sy < 0 || sx > n || sy > m) 
            {
                switch (f[0]) 
                {
                    case 'N':
                        sy--;
                        break;
                    case 'S':
                        sy++;
                        break;
                    case 'W':
                        sx++;
                        break;
                    case 'E':
                        sx--;
                        break;
                }
                if (visited[sx][sy] == 1) 
                {
                    continue;
                }
                visited[sx][sy] = 1;
                lost = 1;
                break;
            }
        }
        if (lost != 1) 
        {
            cout << sx << " " << sy << " " << f[0];
        } 
        else 
        {
            cout << sx << " " << sy << " " << f[0] << " "<< "LOST";
        }
    }
    return 0;
}