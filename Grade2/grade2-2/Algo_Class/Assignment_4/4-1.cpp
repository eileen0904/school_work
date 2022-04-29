#include <bits/stdc++.h>
using namespace std;

string Find_T(vector<string> &S){
    int size = S.size();
    vector<vector<int>> cost(size, vector<int>(size)); //the cost of appending word[i] after word[j]

    for(int i=0; i < size; i++){
        for(int j=0; j < size; j++){
            cost[i][j] = S[j].size();
            for(int len = 1; len <= min(S[i].size(), S[j].size()); len++){
                if(S[i].substr(S[i].size() - len) == S[j].substr(0, len)){ //頭尾相接
                    cost[i][j] = S[j].size() - len;
                }
            }
        }
    }

    int n = 1 << size; //2^size
    //i: word編號，2^size = 2^i + 2^(i+1) +...+ 2^(i+size-1)
    vector<vector<int>> dp(n, vector<int>(size, INT_MAX/2)); //reach state ending with i shortest cost
    vector<vector<int>> path(n, vector<int>(size, -1)); //reach state ending with i its preceeding word
    int min = INT_MAX, last = -1;

    for (int i = 0; i < size; i++){ //Initial
        dp[1 << i][i] = S[i].size();
    }

    for(int cs = 1; cs < n; cs++){ //All state: 1->used, 0->unused, cs:CurState
        for(int cw = 0; cw < size; cw++){ //枚舉所有end word，cw:CurWord
            if((cs & (1 << cw)) == 0) continue; //判斷當前word是否用過，(1<<j)=>只有當前word是1，其他都是0
            int prevState = cs - (1<<cw); //把第cw位置空，得到上一個狀態(沒有訪問過cw的狀態)
            if(prevState == 0){ //現在是第一個word(第一個狀態)
                dp[cs][cw] = S[cw].size();
            }
            else{
                for(int pw = 0; pw < size; pw++){ //k: previous word
                    if(dp[prevState][pw] + cost[pw][cw] < dp[cs][cw]){ //把CurWord加到PrevWord的cost
                        dp[cs][cw] = dp[prevState][pw] + cost[pw][cw];
                        path[cs][cw] = pw; //紀錄[當前狀態][當前word]的上一個word
                    }
                }
            }
            if(cs == (1 << size) - 1 && dp[cs][cw] < min){ //到達最後一個狀態(所有都訪問過)
                min = dp[cs][cw];
                last = cw; //最後是以哪一個word結尾
            }
        }
    }

    int s = (1 << size) - 1;
    string ans;
    while(s > 0){ //from end to start
        int PrevWord = path[s][last];
        if(PrevWord == -1){ //走到頭了
            ans = S[last] + ans;
        }
        else{ //把substring取出來 + ans
            ans = S[last].substr(S[last].length() - cost[PrevWord][last]) + ans;
        }
        s = s ^ (1 << last); //回到上一個狀態
        last = PrevWord;
    }
    cost.clear();
    dp.clear();
    path.clear();
    return ans;
}

int main(){
    while(1){
        cout << "Enter the number of keywords: ";
        int n;
        cin >> n;
        vector<string> S;
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            S.push_back(s);
        }
        string ans = Find_T(S);
        cout << "The shortest sentence is: " << ans << endl;
        cout << "The length of the sentence is: " << ans.size() << endl << endl;

    }

    return 0;
}
