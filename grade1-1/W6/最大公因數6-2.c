//三個數的最大公因數//

#include<stdio.h>

int main(){
    int a,b,c,d,i,max;
    while(scanf("%d %d %d",&a,&b,&c)!=EOF){
        max=a;
        if(b>max){
            max=b;
        }
        if(c>max){
            max=c;
        }
        d=1;
        for(i=2;i<=max;i++){
            if(a%i==0&&b%i==0&&c%i==0){
                d=i;
            }

        }
        printf("%d\n",d);


    }

    return 0;

}