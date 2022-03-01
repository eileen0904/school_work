# 快速排序(Quick Sort)

## 概念
* 在數列中挑選一個數作為**pivot**，然後調整數列，使得所有在**pivot**左邊的數，都比**pivot**還小，而在**pivot**右邊的數都比**pivot**大。
* 把**pivot**左邊和右邊分別視為新的數列。
* 再從新的數列重複整過程，直到分不出「新的數列」為止。
## 程式碼
c++ (ver.1)
```c=
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
```
c++ (ver.2)
```c=
#include <iostream>
using namespace std;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(int *arr, int front, int end){
    if(front >= 0 && end < 5 && end - front > 1){
        //超出陣列邊界
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
```
## 時間複雜度
* Best Case : ***NlogN***
* Worst Case : ***N^2***

###### tags: `演算法` `排序`
