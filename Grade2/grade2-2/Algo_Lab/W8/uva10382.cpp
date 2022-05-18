#include <bits/stdc++.h>
using namespace std;

class Circle{
public:
    double left , right;
};

Circle C[10005];

int main(){
    int testcase;
    double l, w;
    while(cin >> testcase >> l >> w){
        double p, r;
        int size = 0;
        for(int i=0; i < testcase; i++){
            cin >> p >> r;
            if(r*2 >= w){
                C[size].left = p - sqrt(r*r - (w/2)*(w/2));
                C[size].right = p + sqrt(r*r - (w/2)*(w/2));
                size++;
            }
        }
        int ans = 0;
        double begin = 0, max_right = 0;
        while(begin < l){
            max_right = 0;
            for(int i=0; i < size; i++){
                if(C[i].left <= begin && C[i].right > max_right){
                    max_right = C[i].right;
                }
            }
            if(max_right == begin){
                ans = -1;
                break;
            }
            ans++;
            begin = max_right;
        }
        cout << ans << endl;
    }
    return 0;
}