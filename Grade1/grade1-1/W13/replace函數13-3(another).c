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
    static char substr[1000];
    char result[10000], end[1000],newstr[1000],endtemp[1000];
    int solen=strlen(source);
    int palen=strlen(pattern);
    int relen=strlen(replacement);
    int i,pos=0;
    int loc=strstr(source, pattern)-source;
    strncpy(result, source, loc);
    pos=pos+loc; //紀錄位置(從第幾個開始替換)
    strncpy(result+pos, replacement, relen);
    strcpy(substr, result);
    strcat(result, source+loc+palen);
    strcpy(end, source+loc+palen);
    while(strstr(end, pattern)!= NULL){
        int locend=strstr(end, pattern)-end;
        strncpy(newstr, end, locend);
        strncpy(newstr+locend, replacement, relen);
        strcat(substr, newstr);
        strcat(newstr, end+locend+palen);
        memset(endtemp, '\0', strlen(endtemp));
        strcpy(endtemp, end+locend+palen);
        memset(end, '\0', strlen(end));
        strcpy(end, endtemp);
        memset(newstr, '\0', strlen(newstr));
        locend=0;
    }
    strcat(substr, end);
    strcpy(source, substr);
    return source;
}

//test
/*int main() {
    char source[10000] = "1223456789", pattern[1000] = "2", replacement[1000] = "123";
    char *newstr = replaceAll(source, pattern, replacement);
    printf("%s", newstr);
    return 0;
}

