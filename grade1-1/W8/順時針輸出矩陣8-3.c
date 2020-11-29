/*給定一矩陣。 請輸出順時針序
第一行是兩個整數 n, m，代表列數和行數。
下面的 m 列是矩陣的內容。*/


#include<stdio.h>

int main(){
    int n,m,i,j;
    scanf("%d %d",&n,&m);
    int v[n][m];
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&v[i][j]);
        }
    }
    int k=0,l=0;
    while(k<n && l<m){
        for(i=l;i<m;i++){
            printf("%d ",v[k][i]);
        }
        k++;
        for(i=k;i<n;i++){
            printf("%d ",v[i][m-1]);
        }
        m--;
        if(k<n){
            for(i=m-1;i>=l;i--){
                printf("%d ",v[n-1][i]);
            }
        n--;
        }
        if(l<m){
            for(i=n-1;i>=k;i--){
                printf("%d ",v[i][l]);
            }
        l++;
        }
    }
    return 0;

 }