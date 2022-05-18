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
    vector<class Interval> lv;
    Interval v;
    vector<class Interval> vp;
    int p = target.left, idx = 0;

    sort(V.begin(), V.end(), Cmp());

    while(p <= target.right){
        for(int i=idx; i < n; i++){
            if(V[i].left <= p){
                lv.push_back(Interval(V[i].left, V[i].right));
                idx = i + 1;
            }
        }
        int max_right = lv[0].right;
        for(int i=0; i < lv.size(); i++){
            if(lv[i].right > max_right){
                max_right = lv[i].right;
                v.left = lv[i].left;
                v.right = max_right;
            }
        }
        p = v.right;
        vp.push_back(Interval(v.left, v.right));
        lv.clear();
    }
    cout << "Minimum interval cover :" << endl;
    for(int i=0; i < vp.size(); i++){
        cout << "(" << vp[i].left << ", " << vp[i].right << ")" << endl;
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