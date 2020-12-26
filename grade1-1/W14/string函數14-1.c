#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *replace(char *source, char const *pattern, char const *replacement){
    char *find;
    char result[1000], substr[1000];
    static char endreplace[1000], endsource[1000];
    int palen=strlen(pattern);
    int relen=strlen(replacement);
    int loc=0;
    if(source!=NULL && strstr(source, pattern)!=NULL){
        find=strstr(source, pattern);
        loc=strlen(source)-strlen(find);//從哪開始換
        memset(result, '\0', strlen(result));
        strncpy(result, source, loc);//不用換的
        strcat(result+loc, replacement);//把replacement接上去
        strcat(result, find+palen);//後面剩下的
        strcpy(endreplace, find+palen);//結尾
        strcpy(endsource, result);
        strcpy(source, result);
        return source;
    }

    if(source==NULL && strstr(endreplace, pattern)!=NULL){
        int* new_source = (int *)malloc(sizeof(int) * 1000);
        find = strstr(endsource, endreplace);
        loc=strlen(endsource)-strlen(find);
        strncpy(new_source, endsource, loc);
        strcpy(substr, endreplace + 1);
        *(endreplace) = '\0';
        strcat(endreplace, replacement);
        strcat(endreplace, substr);
        strcat(new_source, endreplace);
        return new_source;
    }
    if(source==NULL && strstr(endreplace, pattern)==NULL){
        source=&endsource;
        return source;
    }
    if(source!=NULL && strstr(source, pattern)==NULL){
        source=&endsource;

        return source;
    }

}
