#include <bits/stdc++.h>
using namespace std;

const int N = 100;

int main(){
    int m[N][N], p[N][N], d[N], n;
    cin >> n;
    for(int i=1; i <= n; i++){
        cin >> d[i-1] >> d[i];
    }
    int i, j, k, L, q;
    for(i = 1; i <= n; i++)
        m[i][i] = 0;

    for(L = 2; L <= n; L++){
        for(i = 1; i <= n - L + 1; i++){
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for(k = i; k <= j - 1; k++){
                m[i][j] = min(m[i][j], m[i][k] + m[k+1][j] + d[i-1] * d[k] * d[j]);
                p[i][j] = k;
            }
        }
    }
    cout << "Matrix M:" << endl;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "Matrix P:" << endl;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            cout << p[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "Minimum number of multiplications is: " << m[1][n] << endl;
    return 0;
}
