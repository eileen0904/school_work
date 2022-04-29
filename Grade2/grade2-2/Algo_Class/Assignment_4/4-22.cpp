#include <bits/stdc++.h>
using namespace std;

class Job{
    public:
        Job(int i, int d, int p){
            id = i;
            deadline = d;
            profit = p;
        }
        int id, deadline, profit;
};

bool cmp(const Job &j1, const Job &j2){
    return j1.profit > j2.profit;
}

int Scheduling(Job arr[], int n){
    sort(arr, arr + n, cmp);
    int result[n], max_profit = 0;
    bool slot[n];
    for(int i=0; i < n; i++){
        slot[i] = false;
    }
    for(int i=0; i < n; i++){
        for(int j = min(n, arr[i].deadline) - 1; j >= 0; j--){
            if(slot[j] == false){
                result[j] = i;
                slot[j] = true;
                break;
            }
        }
    }
    cout << "Maximum profit sequence of jobs" << endl;
    for(int i=0; i < n; i++){
        if(slot[i]){
            cout << arr[result[i]].id << " ";
            max_profit = max_profit + arr[result[i]].profit;
        }
    }

    return max_profit;
}

int main(){
    Job arr[] = {{1, 2, 40}, {2, 4, 15}, {3, 3, 60},
                {4, 2, 20}, {5, 3, 10}, {6, 1, 45}, {7, 1, 55}};
    int n = 7;
    int total = Scheduling(arr, n);
    cout << endl << "Maximum profit is : " << total << endl;

    return 0;
}
