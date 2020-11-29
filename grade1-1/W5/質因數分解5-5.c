//質因數分解//
//當輸入為 0 的時候結束測試//

#include<stdio.h>

int main(){
    int a,i;
    scanf("%d",&a);

    while(a!=0){
        printf("%d = ",a);
        for(i=2;i<=a;i++){
            while(a>=i){
                if(a%i==0){
                    if(a==i){
                        printf("%d\n",i);
                    }
                    else{
                        printf("%d * ",i);
                    }
                 a=a/i;
                }
                else
                break;
            }
        }
        scanf("%d",&a);
    }
    return 0;

}