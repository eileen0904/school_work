//判斷輸入的數是不是質數//
//當輸入為 0 的時候結束測試//

#include<stdio.h>

int main(){
    int a,b,prime=1;
    scanf("%d",&a);
    while(a!=0){
        prime=1;
        for(b=2;b<a;b++){
            if(a%b==0){
                prime=0;
            }
        }
        if(a==1){
            printf("not a prime\n");
        }
        else if(prime==0){
            printf("not a prime\n");
        }
        else{
            printf("prime\n");
        }

        scanf("%d",&a);
    }

    return 0;

}