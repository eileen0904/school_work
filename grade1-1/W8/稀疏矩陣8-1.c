/*輸入壓縮後的資料，將矩陣還原後輸出。
輸入的第一行有三個整數，前兩個代表原始矩陣的大小，第三個代表矩陣中共有多少資訊。
接下來的每一行都會有三個數字，前兩個數字代表行跟列，第三個數字代表資料。
輸出原始的矩陣，每個數字後都要跟著一個空白。*/


#include<stdio.h>

int main(){
    int n,m,d,a,b,c,i,j;
    scanf("%d %d %d",&n,&m,&d);
    int v[400][400];
    for(i=0;i<d;i++){
        scanf("%d %d %d",&a,&b,&c);
        v[a][b]=c;
    }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            printf("%d ",v[i][j]);
        }
        if(i<n-1){
            printf("\n");
        }
    }
    return 0;
}