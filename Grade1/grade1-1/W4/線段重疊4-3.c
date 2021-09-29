//我們可以用兩個點在一為座標上定義一個線段，請寫一隻程式決定兩個線段是否重疊//
//輸入會包含四個整數，前兩個整數定義第一個線段，後兩個整數定義第二個線段//
//如果兩個線段有重疊就輸出 overlay ，如果沒有重疊就輸出 no overlay//

#include<stdio.h>

int main(){
  	int a,b,c,d;
  	scanf("%d %d %d %d",&a,&b,&c,&d);
  	
  	if(c>=a&&c>=b&&d>=a&&d>=b){
      	printf("no overlay");
    }
  	else if(c<=a&&c<=b&&d<=a&&d<=b){
      		printf("no overlay");
    }
  		else{printf("overlay");}
  
  	return 0;
}
