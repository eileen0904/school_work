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

class Cmp{
public:
    bool operator()(const Interval &I1, const Interval &I2){
        return I1.left < I2.left;
    }
};

void MinInterval(vector<class Interval> &V, const Interval &target){
    Interval v;
    vector<class Interval> vp;
    int p = target.left, max_right = 0, idx = 0;

    sort(V.begin(), V.end(), Cmp());

    while(p <= target.right){
        for(int i=idx; i < n; i++){
            if(V[i].left <= p && V[i].right >= max_right){
                v.left = V[i].left;
                v.right = V[i].right;
                max_right = V[i].right;
                idx = i + 1;
            }
        }
        if(V[idx].left > max_right) break; //要有交集才行
        else{
            p = v.right;
            vp.push_back(Interval(v.left, v.right));
        }
    }
    if(max_right < target.right){
        cout << "No minimum interval cover" << endl;
    }
    else {
        cout << "Minimum interval cover :" << endl;
        for(int i=0; i < vp.size(); i++){
            cout << "(" << vp[i].left << ", " << vp[i].right << ")" << endl;
        }
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