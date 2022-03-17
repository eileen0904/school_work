#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main(){

    string str;
    cin>>str;

    int i, j, size = 0;
    size = str.size();
    bool dp[size][size];
    unordered_map<string, int> sub_p;

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            dp[i][j] = false;
        }
    }

    for(i=size-1;i>=0;i--){
        for(j=i;j<size;j++){
            if(str[i] == str[j]){
                if(j-i <= 1){
                    dp[i][j] = true;
                    if(j-i == 1){
                        string s1 = str;
                        string s2 = s1.assign(s1, i, 2);
                        if(!(sub_p.count(s2))){
                            sub_p[s2] = 1;
                        }
                        s1.clear();
                        s2.clear();
                    }
                }
                else if(dp[i+1][j-1]){
                    dp[i][j] = true;
                    string s1 = str;
                    string s2 = s1.assign(s1, i, j-i+1);
                    if(!(sub_p.count(s2))){
                        sub_p[s2] = 1;
                    }
                    s1.clear();
                    s2.clear();
                }
            }
        }
    }

    unordered_map<string, int>::iterator it;
    for(it=sub_p.begin(); it != sub_p.end(); it++){
        cout<<(*it).first<<endl;
    }

    return 0;
}
