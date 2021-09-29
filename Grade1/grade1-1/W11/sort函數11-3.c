/*sort 函數會比較將傳入的陣列中的前 n 個元素由小到大排列好*/


void sort(int array[], int n)
{
  int i,j;
  int temp=0;
  for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++){
      if(array[i]>array[j]){
        temp=array[i];
        array[i]=array[j];
        array[j]=temp;
      }
    }
  }
}
