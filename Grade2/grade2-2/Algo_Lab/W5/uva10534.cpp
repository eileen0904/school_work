#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, S[10001], lis[10001], lds[10001];
    vector<int> v;
    while (cin>>n){
        int i;
        for(i = 0; i < n; i++){ //n
            cin >> S[i];
        }

        v.clear();
        int size = 1;
        v.push_back(S[0]);
        lis[0] = 1;
        for(i = 1; i < n; i++){ //n-1
            if(S[i] > v.back()){
                v.push_back(S[i]);
                lis[i] = ++size;
            }
            else{
                int temp = lower_bound(v.begin(), v.end(), S[i]) - v.begin(); //logn
                v[temp] = S[i];
                lis[i] = temp + 1;
            }
        }

        v.clear();
        size = 1;
        v.push_back(S[n - 1]);
        lds[n - 1] = 1;
        for(i = n - 2; i >= 0; i--){ //n-1
            if(S[i] > v.back()){
                v.push_back(S[i]);
                lds[i] = ++size;
            }
            else{
                int temp = lower_bound(v.begin(), v.end(), S[i]) - v.begin(); //logn
                v[temp] = S[i];
                lds[i] = temp + 1;
            }
        }

        int max = 0;
        for(i = 0; i < n; i++){ //n
            int temp = min(lis[i], lds[i]);
            if(max < temp){
                max = temp;
            }
        }

        cout << max * 2 - 1 << endl;
    }

    return 0;
}