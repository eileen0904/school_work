/*swap 函數會交換兩個傳入的參數 。*/


void swap(int *a, int *b) {
  int c=0;
  c=*a;
  *a=*b;
  *b=c;
}