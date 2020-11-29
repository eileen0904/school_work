//任一大於2的偶數，都可表示成兩個質數之和。//
//像是 10 可以分解成 (3 + 7) (5 + 5) 兩對質數的合//

#include<stdio.h>

int main(){
    int n,i,j,k,num,ans=0;
    scanf("%d",&n);
    for(i=2;i<=n/2;i++){
        for(j=n-i;j>=n/2;j--){
            if(i+j==n){
                if(prime(i)!=0 && prime(j)!=0){
                        ans++;
                    }
                }
            }
        }
    printf("%d",ans);
    return 0;
    }

int prime(int num) //i=(int num)//
{
    for(int i = 2 ; i < num; i++)
    {
        if(num%i==0) //不是質數//
            return 0;
    }
    return 1;

}