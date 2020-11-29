//計算裁剪平均值，捨棄的資料為最高跟最低的三筆資料//
//正整數 N(N > 6) 表示樣本數，接下來 N 個數為要計算的樣本//

#include<stdio.h>

int main(){
    int n,i,j,k,t;
    int a[10000];
    float sum,ave;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&(a[i]));
    }
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1;j++){
            if(a[j]>a[j+1]){
                k=a[j];
                a[j]=a[j+1];
                a[j+1]=k;
                }
            }
        }
    for(t=0;t<n;t++){
        sum=sum+a[t];
    }

    ave=(sum-a[0]-a[1]-a[2]-a[n-3]-a[n-2]-a[n-1])/(n-6);
    printf("%.2f",ave);

    return 0;
}