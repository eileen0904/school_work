#include <bits/stdc++.h>
using namespace std;

int n;
class Interval{
public:
    Interval(){}
    Interval(int l, int r){
        left = l;
        right = r;
    }
    int left = 0, right = 0;
};

void MinInterval(vector<class Interval> &V, const Interval &target){
    Interval v;
    vector<class Interval> vp;
    int p = target.right, min_left = target.right - 1;

    while(p <= target.left){
        for(int i=0; i < n; i++){
            if(V[i].right >= p && V[i].left <= min_left){
                v.left = V[i].left;
                v.right = V[i].right;
                min_left = V[i].left;
            }
        }
        p = v.left;
        vp.push_back(Interval(v.left, v.right));
    }
}

int main(){
    vector<class Interval> V;
    int a, b;
    cin >> n;
    for(int i=0; i < n; i++){
        cin >> a >> b;
        V.push_back(Interval(a, b));
    }
    cout << "Input target :" << endl;
    cin >> a >> b;
    Interval target(a, b);
    MinInterval(V, target);

    return 0;
}
