#include <bits/stdc++.h>
using namespace std;

int main(){
    int budget, n; //n is count of items;
    cout << "Please enter how many items do you want:" << endl;
    cin >> n;
    cout << "Please enter your budget:" << endl;
    cin >> budget;
    int price[n], prefer[n], dp[n][budget + 1], item_set[n][budget + 1];
    cout << "Please enter current market prices and preferences in the range of 1~100:" << endl;
    for(int i=0; i < n; i++){ //n
        cin >> price[i] >> prefer[i];
    }
    //init
    for(int i=0; i < price[0]; i++){ //budget
        dp[0][i] = 0;
        item_set[0][i] = 0;
    }
    for(int i=price[0]; i <= budget; i++){ //budget+1
        dp[0][i] = prefer[0];
        item_set[0][i] = 1;
    }
    //dp
    for(int i=1; i < n; i++){ //n-1
        for(int j=0; j <= budget; j++){ //budget+1
            if(price[i] > j){
                dp[i][j] = dp[i - 1][j];
                item_set[i][j] = 0;
            }
            else{
                if(dp[i - 1][j] >= dp[i - 1][j - price[i]] + prefer[i]){
                    dp[i][j] = dp[i - 1][j];
                    item_set[i][j] = 0;
                }
                else{
                    dp[i][j] = dp[i - 1][j - price[i]] + prefer[i];
                    item_set[i][j] = 1;
                }
            }
        }
    }
    cout << endl << "The max preferences is:" << endl;
    cout << dp[n-1][budget] << endl;
    cout << endl << "The set of items:" << endl;
    for(int i=0; i < n; i++){ //n
        if(item_set[i][budget]){
            cout << "item: " << i << endl;
        }
    }

    return 0;
}
