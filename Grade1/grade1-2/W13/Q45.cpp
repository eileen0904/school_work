//UVa541

#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int n = 0;
    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }
        int i, j, arr[105][105], c[105], r[105];
        memset(arr, 0, sizeof(arr));
        memset(c, 0, sizeof(c));
        memset(r, 0, sizeof(r));
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                cin >> arr[i][j];
            }
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                r[i] = r[i] + arr[i][j];
                c[i] = c[i] + arr[j][i];
            }
        }
        int wr_n = 0, wc_n = 0, wr, wc;
        for (i = 0; i < n; i++)
        {
            if (r[i] % 2 != 0)
            {
                wr_n++;
                wr = i;
            }
            if (c[i] % 2 != 0)
            {
                wc_n++;
                wc = i;
            }
        }
        if (wr_n == 0 && wc_n == 0)
        {
            cout << "OK" << endl;
        }
        else if (wr_n == 1 && wc_n == 1)
        {
            cout << "Change bit "<< "(" << wr + 1 << "," << wc + 1 << ")" << endl;
        }
        else
        {
            cout << "Corrupt" << endl;
        }
    }
    return 0;
}