#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main(){

    string str;
    cin>>str; //c1

    int i, j, size = 0;
    size = str.size(); //c2
    bool dp[size][size]; //c3
    unordered_map<string, int> sub_p;

    for(i=0;i<size;i++){ //size
        for(j=0;j<size;j++){ //size
            dp[i][j] = false; //c4
        }
    }

    for(i=size-1;i>=0;i--){ //size
        for(j=i;j<size;j++){ //size-i
            if(str[i] == str[j]){
                if(j-i <= 1){
                    dp[i][j] = true; //c5
                    if(j-i == 1){
                        string s1 = str; //c6
                        string s2 = s1.assign(s1, i, 2); //c7(?) = 1
                        if(!(sub_p.count(s2))){ //Worst:size, Best:1
                            sub_p[s2] = 1; //c8
                        }
                        s1.clear(); //c9
                        s2.clear(); //c10
                    }
                }
                else if(dp[i+1][j-1]){
                    dp[i][j] = true; //c11
                    string s1 = str; //c12
                    string s2 = s1.assign(s1, i, j-i+1); //c13(?) = 1
                    if(!(sub_p.count(s2))){ //Worst:size, Best:1
                        sub_p[s2] = 1; //c14
                    }
                    s1.clear(); //c15
                    s2.clear(); //c16
                }
            }
        }
    }

    unordered_map<string, int>::iterator it;
    for(it=sub_p.begin(); it != sub_p.end(); it++){ //size
        cout<<(*it).first<<endl; //c17
    }

    return 0;
}
