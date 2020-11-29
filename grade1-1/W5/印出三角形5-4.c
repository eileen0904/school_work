/*輸入一正整數表示正三角形層數 ，並且印出此三角形
1.以 ' * ' 字元表示
2.每行最後面不能有空白
3.最後一行後面沒有換行*/

#include<stdio.h>

int main(){
  	int a,row,spare,star;
  	scanf("%d",&a);
  	if(a>=1&&a<=30){
  	for(row=1;row<=a;row++){ //印外圈//
      	for(spare=a-row;spare>=1;spare--){ //印前面空格//
          	printf(" ");
        }
      	for(star=1;star<=row;star++){
          	printf("*");
          	if(star!=row){ 
          	printf(" ");
          	}
        }
        if(row!=a){
        printf("\n");
        }
     }
    }

    return 0;
}