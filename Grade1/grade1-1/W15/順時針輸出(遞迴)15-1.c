#include<stdio.h>

void clockwise(int arr[][1000], int n, int m, int counter, int nmax, int nmin, int mmax, int mmin) {
    /*for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col)
            printf("%d%c", arr[row][col], (col == m-1)?'\n':' ');
    }*/
    int i;
    int k=n*m;
    for(i=mmin;i<mmax;i++){//right
        printf("%d ",arr[nmin][i]);
        counter++;
        if(counter==k){
            return ;
        }
    }
    for(i=nmin+1;i<nmax;i++){//down
        printf("%d ",arr[i][mmax-1]);
        counter++;
        if(counter==k){
            return ;
        }
    }
    for(i=mmax-1-1;i>=mmin;i--){//left
        printf("%d ",arr[nmax-1][i]);
        counter++;
        if(counter==k){
            return ;
        }
    }
    for(i=nmax-2;i>nmin;i--){//up
        printf("%d ",arr[i][nmin]);
        counter++;
        if(counter==k){
            return ;
        }
    }
    return clockwise(arr, n, m, counter, nmax-1, nmin+1, mmax-1, mmin+1);
}

int main(){
    int n,m,i,j;
    scanf("%d %d",&n,&m);
    int a[n][1000];
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d", &a[i][j]);
        }
    }
    clockwise(a, n, m, 0, n, 0, m, 0);
    return 0;
}
