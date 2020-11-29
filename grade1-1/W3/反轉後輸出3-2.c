/*讀入一個四位數，把它反轉後輸出。
(第一位數不會是0)*/

#include<stdio.h>

int main(){
	int n,a,b,c,d;
    scanf("%4d",&n);
    a=n/1000;
    b=n/100-a*10;
    c=n/10-a*100-b*10;
    d=n-a*1000-b*100-c*10;
    printf("%d%d%d%d",d,c,b,a);

      return 0;
}