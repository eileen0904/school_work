#include <bits/stdc++.h>
using namespace std;

int n = 3;
int weight[3] = {1, 3, 4};
int value[3] = {15, 20, 30};
int max_weight = 4;

int Knapsack(int i, int leftweight){
    int res = 0;
    if(i == -1) return 0;

    if(weight[i] <= leftweight){
        int r1 = Knapsack(i - 1, leftweight);
        int r2 = Knapsack(i - 1, leftweight - weight[i]) + value[i];
        res = max(r1, r2);
    }

    return res;
}

int main(){
    cout << Knapsack(n-1, max_weight);
}
