/*給定一數字n，請找出不大於n的數字中最大的偶數*/

#include<stdio.h>

int main(){
  	int n;
  	scanf("%d",&n);
  	if(n%2!=0)
    {
      	printf("%d\n",n-1);
    }
  	else
    {
      	printf("%d\n",n);
    }
  	return 0;
}