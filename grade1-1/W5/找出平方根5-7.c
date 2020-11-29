//已知一正整數N的平方根介於0到N之間，令N的平方根為x，a=0為下界，b=N為上

界。則有不等式a<=x<=b，將不等式平方可以得到a*a<=x*x=N<=b*b，根據二分

逼近法計算c = (a+b)/2，當c平方大於等於N時我們將上界更新，得到新的不等式

a<=x<=c，反之，則更新下界，得到新的不等式c<=x<=b，上界與下界的差稱為誤

差。請設計一個程式，由使用者輸入一個正整數，計算出該正整數的平方根，

請精準到小數點後四位//
//輸出 n 的平方根到小數點後四位//

#include<stdio.h>

int main(){
    int n,i;
    float a=0,b=n ,c;
    scanf("%d",&n);
    b=n;
    for(i=0;i<=1000;i++){
    c = ((a+b)/2);

    if((c*c)>=n){b=c;}
    if((c*c)<=n){a=c;}
    //printf("%.4f",c);


    }
 printf("%.4f",c);
 return 0;
}