//給你十個數字，請從小到大輸出這十個數字。//

#include<stdio.h>

int main(){
    int a[10],i,j,k;
    for(i=0;i<10;i++){
        scanf(" %d",&a[i]);
    }
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(a[j]>a[j+1]){
                k=a[j];
                a[j]=a[j+1];
                a[j+1]=k;
                }
            }
        }
    for(i=0;i<10;i++){
        printf("%d ",a[i]);
    }

    return 0;
}
