#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *replace(char *source, char *pattern, char *replacement)
{
    int solen=strlen(source);
    int palen=strlen(pattern);
    int relen=strlen(replacement);
    char result[10000];
    int i,pos=0;
    int loc=strstr(source, pattern)-source;
    memset(result, '\0', solen);
    strncpy(result, source, loc);
    pos=pos+loc; //紀錄位置(從第幾個開始替換)
    strncpy(result+pos, replacement, relen);
    pos=pos+relen;
    strcat(result, source+loc+palen);
    strcpy(source, result);
    return source;
}

char *replaceAll(char *source, char *pattern, char *replacement)
{
    while(strstr(source, pattern) != NULL){
        char *newstr = replace(source, pattern, "~");
        strcpy(source, newstr);
    }
    while(strstr(source, "~") != NULL){
        char *newstr = replace(source, "~", replacement);
        strcpy(source, newstr);
    }
    return source;
}

//test
/*int main() {
    char source[10000] = "1223456789", pattern[1000] = "2", replacement[1000] = "123";
    char *newstr = replaceAll(source, pattern, replacement);
    printf("%s", newstr);
    return 0;
}
