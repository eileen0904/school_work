#include<stdio.h>
#include<string.h>

int main(){
    char str[1000],str2[1000][1000];
    scanf("%[^\n]",str);
    int i,index=0,k=0;
    int len=strlen(str);
    for(i=0;i<len;i++){
        if(str[i]==' '){
            index++;
            k=0;
            continue;
        }
        str2[index][k]=str[i];
        k++;
    }
    for(i=index;i>=0;i--){
        printf("%s",str2[i]);
        printf(" ");
    }

    return 0;
}
