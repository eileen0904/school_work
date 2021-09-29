#include<stdio.h>

int main(){
    int A=0, B=0, i, j;
    char str1[100], str2[100];
    scanf("%s", str1);
    scanf("%s", str2);
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(str1[i]==str2[j] && i==j){
                A++;
            }
            if(str1[i]==str2[j] && i!=j){
                B++;
            }
        }
    }
    printf("%d %d", A, B);
    return 0;
}
