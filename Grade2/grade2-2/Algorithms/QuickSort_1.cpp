#include <iostream>
using namespace std;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int front, int end){
    int pivot = arr[end];
    int i = front -1; //(i)左邊的數，都比pivot小;(i)右邊的數，都比pivot大
    int j; //pivot與其餘數值逐一比較的index
    for (j = front; j < end; j++) {
        if (arr[j] < pivot) {
            i++;  //所有小於pivot的數所形成的數列，又增加了一名成員
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}

void quicksort(int *arr, int front, int end){
    if (front < end) {
        int pivot = partition(arr, front, end);
        quicksort(arr, front, pivot - 1);
        quicksort(arr, pivot + 1, end);
    }
}

int main(){
    int n = 5;
    int arr[] = {2,1,5,4,3};

    quicksort(arr, 0, n-1);

    for(int i=0; i<5; i++){
        cout<<arr[i]<<" ";
    }
}