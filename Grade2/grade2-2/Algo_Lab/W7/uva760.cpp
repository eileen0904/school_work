#include <bits/stdc++.h>
using namespace std;

int dp[301][301];
vector<string> ans;
int num;

void setDP(string a, string b){
    for(int i=0; i <= a.size(); i++){
        dp[i][0] = 0;
    }
    for(int i=0; i <= b.size(); i++){
        dp[0][i] = 0;
    }
    for(int i=1; i <= a.size(); i++){
        for(int j=1; j <= b.size(); j++){
            if(a[i-1] == b[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
}

void traceback(string temp, string a, string b, int i, int j){
    while(dp[i][j] > 0){
        if(a[i-1] == b[j-1]){
            i--;
            j--;
            temp = temp + a[i];
        }
        else{
            if(dp[i-1][j] > dp[i][j-1]){
                i--;
            }
            else if(dp[i-1][j] < dp[i][j-1]){
                j--;
            }
            else{
                traceback(temp, a, b, i - 1, j);
                traceback(temp, a, b, i, j - 1);
                return;
            }
        }
    }
    bool same = false;
    for(int k=0; k < num; k++){
        if(temp == ans[k]){
            same = true;
        }
    }
    if(!same){
        ans.push_back(temp);
        num++;
    }
}

int main(){
    string a, b;
    while(cin >> a >> b){
        int len1 = a.size();
        int len2 = b.size();
        string temp;
        ans.clear();
        num = 0;
        memset(dp, 0, sizeof(dp));
        setDP(a, b);
        if(dp[len1][len2] == 0){
            cout << "No common sequence." << endl;
        }
        else{
            traceback(temp, a, b, len1, len2);
            for(int i=0; i < num; i++){
                reverse(ans[i].begin(), ans[i].end());
            }
            sort(ans.begin(), ans.end());
            for(int i=0; i < num; i++){
                cout << ans[i] << endl;
            }
        }
        cout << endl;
    }
}
