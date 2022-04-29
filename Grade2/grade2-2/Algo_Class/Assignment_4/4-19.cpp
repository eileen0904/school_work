#include <bits/stdc++.h>
using namespace std;

bool cmp(int a, int b){
    return a < b;
}
int main(){
    int job[4] = {7, 3, 10, 15};
    int n = 4, now = 0, total = 0;
    sort(job, job + n, cmp); 
    for(int i=0; i < n; i++){
        now = now + job[i];
        total = total + now;
    }
    cout << endl << "Total time is : " << total << endl;
    cout <<"Time in the system :" << (double)total / n << endl;

    return 0;
}
