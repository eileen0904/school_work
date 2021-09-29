/*判斷三個線段是否能構成一個三角形，如果可以又是怎樣的三角形。
輸入會包含三個整數 a b c ，c 會是最大值*/

#include<stdio.h>

int main(){
  	int a,b,c;
  	scanf("%d%d%d",&a,&b,&c);
  	if(a+b>c&&a*a+b*b==c*c){
       printf("right triangle");
    }
    if(a+b>c&&a*a+b*b>c*c){
       printf("acute triangle");
    }
    if(a+b>c&&a*a+b*b<c*c){
       printf("obtuse triangle");
    }
  	if(a+b<=c){
       printf("can not construct");
    }
    return 0;
}