/*輸入檔包含 5 局記錄。
每局包含一行 2 個字元的資料。
第一個字母代表 Alice 的決策、而第二個代表 Bob 的。
'P' 代表出了布。
'S' 代表出了剪刀。
'R' 代表出了石頭。*/

#include<stdio.h>

int main(){
    char a,b;
  	int i,c,d;
    c=0,d=0;
  	for(i=1;i<=5;i++){
      	scanf(" %c%c",&a,&b);
      	if(a=='R'&&b=='S'||a=='P'&&b=='R'||a=='S'&&b=='P'){
          	c++;
        }
      	if(a=='R'&&b=='R'||a=='P'&&b=='P'||a=='S'&&b=='S'){
          	c++;d++;
        }
      	if(a=='R'&&b=='P'||a=='P'&&b=='S'||a=='S'&&b=='R'){
          	d++;
        }
     }
     if(c>d){
       	printf("Alice");
     }
  	 if(d>c){
       	printf("Bob");
     }
  	 if(c==d){
       	printf("Draw");
     }

     return 0;
}