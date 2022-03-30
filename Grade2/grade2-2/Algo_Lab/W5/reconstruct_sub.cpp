#include <bits/stdc++.h>
using namespace std;

void LIS(vector<int> &S, int index){
    //int len = S.size();
    if(index < 1) cout << S[0];
    else{
        int dp[index];
        int ans = 0;
        //n is index
        for(int i = 0; i < index + 1; i++){ //n+1
            dp[i] = 1;
            for(int j = 0; j < i; j++){ //n
                if(S[i] > S[j]){
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        int j = ans, path[ans];
        for(int i = index; i >= 0 && j >= 0; i--){ //n+1
            if(dp[i] == j){
                j--;
                path[j] = S[i];
            }
        }

        for(int i = 0; i < ans; i++){ //n
            cout << path[i] << " ";
        }
    }   
}

int main(){
    int n = 0;
    cin>>n;
    vector<int> S;
    for(int i=0; i< n; i++){
        int num = 0;
        cin>>num;
        S.push_back(num);
    }
    LIS(S, 10);
    return 0;
}
