#include <iostream>
#include <algorithm>
using namespace std;

int MaxCrossSub(int *A, int l, int r, int &l_index, int &r_index){
    int mid = (l + r) / 2;
    int left_sum = 0, max_left_sum = A[mid];
    int right_sum = 0, max_right_sum = A[mid+1];
    l_index  = mid;
    r_index = mid + 1;
    for(int i = mid; i >= l; i--){
        left_sum = left_sum + A[i];
        if(left_sum >= max_left_sum){
            max_left_sum = left_sum;
            l_index = i;
        }
    }
    for(int i = mid+1; i <= r; i++){
        right_sum = right_sum + A[i];
        if(right_sum >= max_right_sum){
            max_right_sum = right_sum;
            r_index = i;
        }
    }
    return max_left_sum + max_right_sum;
}

int MaxSub(int *A, int l, int r, int &l_index, int &r_index){
    if(l == r){ //Base Case: Only one element
        return A[l];
    }
    int mid = (l + r) / 2;
    int left = MaxSub(A, l, mid, l_index, r_index);
    int right = MaxSub(A, mid+1, r, l_index, r_index);
    int cross = MaxCrossSub(A, l, r, l_index, r_index);
    return max(max(left, right), cross);
}

int main(){
    int A[] = {-7, 0, 0};
    int n = 3;
    int l_index = 0, r_index = 0;
    int sum = MaxSub(A, 0, n-1, l_index, r_index);
    cout << "Sum is: " << sum << endl;
    cout << "Start index is: " << l_index << endl;
    cout << "Length is: " << r_index - l_index + 1 <<endl;
    cout << "Max Subarray is: ";
    for(int i=l_index; i <= r_index; i++){
        cout << A[i] << " ";
    }

    return 0;
}
