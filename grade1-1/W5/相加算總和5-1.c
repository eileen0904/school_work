//不斷地輸入正整數，直到輸入 0 為止，將所有輸入的正整數相加並輸出//

#include<stdio.h>

int main(){
  	int n,sum=0;
  	scanf("%d",&n);
    while(n!=0){
      	sum=sum+n;
      	scanf("%d",&n);
    }
  	printf("%d",sum);
  
  	return 0;
}