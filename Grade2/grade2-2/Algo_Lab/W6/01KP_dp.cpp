#include <bits/stdc++.h>
using namespace std;

int n = 3;
int weight[3] = {1, 3, 4};
int value[3] = {15, 20, 30};
int max_weight = 4;

int Knapsack(){
    int dp[n][max_weight + 1];

    for(int i=0; i < weight[0]; i++){
        dp[0][i] = 0;
    }
    for(int i=weight[0]; i <= max_weight; i++){
        dp[0][i] = value[0];
    }

    for(int i=1; i < n; i++){
        for(int j=0; j <= max_weight; j++){
            if(weight[i] > j){
                dp[i][j] = dp[i - 1][j];
            }
            else{
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
            }
        }
    }

    return dp[n - 1][max_weight]; 
}

int main(){
    cout << Knapsack();
}