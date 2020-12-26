#include<stdio.h>
#include<string.h>

void reverse(char *s){
    if(*s==NULL){
        return NULL;
    }
    int len=strlen(s);
    if(len>1){
        char temp=s[0];
        s[0]=s[len-1];
        s[len-1]='\0';
        reverse(s+1);
        s[len-1]=temp;
    }
    return s;
}

int main(){
    char str[100];
    gets(str);
    reverse(str);
    puts(str);
    return 0;
}
