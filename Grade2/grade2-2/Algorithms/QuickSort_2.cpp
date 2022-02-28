#include <iostream>
using namespace std;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(int *arr, int front, int end){
    if(front >= 0 && end < 5 && end - front > 1){
        int pivot = arr[front];
        int left = front, right = end;
        while(left!=right){
            while(arr[right] >= pivot && left < right){
                right = right - 1;
            }
            while(arr[left] <= pivot && left < right){
                left = left + 1;
            }
            if(left < right){
                swap(&arr[left], &arr[right]);
            }
        }
        arr[front] = arr[left];
        arr[left] = pivot;

        quicksort(arr, front, left-1);
        quicksort(arr, left+1, end);
    }
    else{return;}

}

int main(){
    int n = 5;
    int arr[] = {2,1,5,4,3};

    quicksort(arr, 0, n-1);

    for(int i=0; i<5; i++){
        cout<<arr[i]<<" ";
    }
}
