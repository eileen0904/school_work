#include <bits/stdc++.h>
using namespace std;

int dp[205][10005], path[205][10005];

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int ML, w[2005], sum[2005], n = 1, l;
        cin >> ML;
        ML = ML * 100;
        while(cin >> l && l){
            w[n] = l;
            sum[n] = sum[n-1] + w[n];
            n++;
        }
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        int cars = 0, length;
        n--;
        for(int i=1; i <= n; i++){
            for(int j=0; j <= ML; j++){
                if(w[i] <= j && dp[i-1][j-w[i]]){ //left
                    dp[i][j] = 1;
                    path[i][j] = 0;
                }
                if((sum[i] - j) <= ML && dp[i-1][j]){ //right
                    dp[i][j] = 1;
                    path[i][j] = 1;
                }
                if(dp[i][j]){
                    cars = i;
                    length = j;
                }
            }
        }
        cout << cars << endl;
        int temp = cars, k = length, ans[205];
        while(temp){
            ans[temp] = path[temp][k];
            if(!path[temp][k]) //left
                k = k - w[temp];
            temp--;
        }
        for(int i=1; i <= cars; i++){
            if(ans[i]) cout << "port" << endl;
            else cout << "starboard" << endl;
        }
        if(testcase)
            puts("");
    }

    return 0;
}
