/*compare 函數會比較兩個傳入參數的大小，
如果 a > b 就回傳 1 ，如果 a < b 就回傳 -1 ，如果兩數箱等，就回傳 0 。*/


int compare(int a, int b) {
  if(a>b){return 1;}
  if(a==b){return 0;}
  if(a<b){return -1;}
}