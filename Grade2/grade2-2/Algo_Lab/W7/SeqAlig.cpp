#include <bits/stdc++.h>
using namespace std;

set<pair<string, string>> st;
int m, n;
int gap = -1, match = 1, mis = -1;

void find_all(string str1, string str2, int **dp, int i, int j, string s1, string s2){
    if(i == 0 && j == 0){
        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());
        st.insert({s1, s2});
        return;
    }
    else{
        int *ptr[m+1];
        for(int i=0; i <= m; i++){
            ptr[i] = dp[i];
        }
        if((str1[i-1] == str2[j-1] && dp[i][j] == dp[i-1][j-1] + match) ||
            (str1[i-1] != str2[j-1] && dp[i][j] == dp[i-1][j-1] + mis)){
            find_all(str1, str2, ptr, i - 1, j - 1, s1 + str1[i-1], s2 + str2[j-1]);
        }
        if(dp[i][j] == dp[i][j-1] + gap){
            find_all(str1, str2, ptr, i, j - 1, s1 + "-", s2 + str2[j-1]);
        }
        if(dp[i][j] == dp[i-1][j] + gap ){
            find_all(str1, str2, ptr, i - 1, j, s1 + str1[i-1], s2 + "-");
        }
    }
}

void Needleman(string str1, string str2){
    int dp[m+1][n+1];

    for(int i=0; i <= m; i++){
        dp[i][0] = i * gap;
    }
    for(int i=0; i <= n; i++){
        dp[0][i] = i * gap;
    }

    for(int i=1; i <= m; i++){
        for(int j=1; j <= n; j++){
            int up = dp[i-1][j] + gap;
            int left = dp[i][j-1] + gap;
            int diag = 0;
            if(str1[i-1] == str2[j-1]){
                diag = dp[i-1][j-1] + match;
            }
            else{
                diag = dp[i-1][j-1] + mis;
            }
            dp[i][j] = max(diag, max(up, left));
        }
    }

    int *ptr[m+1];
    for(int i=0; i <= m; i++){
        ptr[i] = dp[i];
    }

    string s1, s2;
    find_all(str1, str2, ptr, m, n, s1, s2);
}

int main(){
    string str1, str2;
    cin >> str1 >> str2;

    m = str1.size();
    n = str2.size();

    cout<< endl;
    Needleman(str1, str2);

    set<pair<string, string>>::iterator it;
    for(it = st.begin(); it != st.end(); it++){
        cout << it->first << endl << it->second << endl << endl;
    }
}
