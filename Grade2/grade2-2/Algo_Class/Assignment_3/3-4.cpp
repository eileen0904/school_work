#include <bits/stdc++.h>
using namespace std;

int binomialCoeff(int n, int k){
    int C[k + 1];
    memset(C, 0, sizeof(C));

    C[0] = 1; 

    for(int i = 1; i <= n; i++){
        for(int j = min(i, k); j > 0; j--)
            C[j] = C[j] + C[j - 1];
    }
    return C[k];
}

int main(){
    int n = 5, k = 2;
    cout << "Value of C(" << n << "," << k << ")"<< "is " <<binomialCoeff(n, k);
    return 0;
}