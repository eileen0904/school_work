//讀入一個大寫字母，並輸出所對應之小寫字母//

#include<stdio.h>

int main(){
  
	char c;
	scanf("%c",&c);
	c = c + 32;
	printf("%c\n",c);
 
	return 0;
}