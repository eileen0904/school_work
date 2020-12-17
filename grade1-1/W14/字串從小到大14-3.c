#include<stdio.h>
#include<string.h>

int main(){
    int n=0,i,j;
    scanf("%d",&n);
    char str[n][100],temp[100];
    for(i=0;i<n;i++){
        scanf("%s",str[i]);
    }
    for(i=1;i<n;i++){
        for(j=0;j<n-i;j++){
            if(strcmp(str[j], str[j+1])>0){
                strcpy(temp, str[j]);
                strcpy(str[j], str[j+1]);
                strcpy(str[j+1], temp);
            }
        }
    }

    for(i=0;i<n;i++){
        printf("%s",str[i]);
        if(i<n-1){printf("\n");}
    }
    return 0;
}
