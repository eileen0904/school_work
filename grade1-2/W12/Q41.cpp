//UVa10189

#include <iostream>
#include <cstring>
using namespace std;

int R[] = {0, -1, -1, -1, 0, 1, 1, 1};
int C[] = {-1, -1, 0, 1, 1, 1, 0, -1};

int main()
{
    int n = 0, m = 0, i, j, count = 1;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
        {
            break;
        }
        char map[n][m];
        int ms[n][m];
        memset(map, 0, sizeof(map));
        memset(ms, 0, sizeof(ms));
        for (i = 0; i < n; i++)
        {
            cin >> map[i];
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                if (map[i][j] == '*')
                {
                    ms[i][j] = -1;
                    continue;
                }
                for (int k = 0; k < 8; k++)
                {
                    if (i + R[k] >= 0 && j + C[k] >= 0 && i + R[k] < n && j + C[k] < m)
                    {
                        if (map[i + R[k]][j + C[k]] == '*')
                        {
                            ms[i][j]++;
                        }
                    }
                }
            }
        }
        cout << "Field "<< "#" << count << ":" << endl;
        count++;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                if (ms[i][j] == -1)
                {
                    cout << "*";
                }
                else
                {
                    cout << ms[i][j];
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
