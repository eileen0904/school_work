#include <iostream>
#include <vector>

using namespace std;

int LIS(vector<int> &S) {
    int len = S.size();
    if(len < 2){
        return len;
    }
    vector<int> tail;
    tail.push_back(S[0]);
    int end = 0;

    for(int i = 1; i < len; i++){
        if(S[i] > tail[end]){
            tail.push_back(S[i]);
            end++;
        } 
        else{
            int left = 0;
            int right = end;
            while(left < right){
                int mid = (left + right) / 2;
                if(tail[mid] < S[i]){
                    left = mid + 1;
                }
                else{
                    right = mid;
                }
            }
            tail[left] = S[i];
        }
    }
    return end + 1;
}

