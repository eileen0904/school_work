#include <bits/stdc++.h>
using namespace std;

int LIS(vector<int> &S, int index) {
    //int len = S.size();
    if(index < 1) return 1;
    int dp[index];
    int ans = 0;
    for(int i = 0; i < index + 1; i++){
        dp[i] = 1;
        for(int j = 0; j < i; j++){
            if(S[i] > S[j]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
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
    cout << LIS(S, 6);
    return 0;
}
