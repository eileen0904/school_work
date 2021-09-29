#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int funtion(char *current){
    if(*current=='F'){
        return 1 + funtion(current+2);
    }
    else if(*current=='G'){
        int temp=0, counter=0;
        while(1){
            if(*(current+counter)=='G'){
                temp++;
            }
            if(*(current+counter)==','){
                temp--;
            }
            if(temp==0){
                break;
            }
            counter++;
        }
        return funtion(current+2) + funtion(current+counter+1);
    }
    else if(isdigit(*current)){
        return atoi(current);
    }
    return 0;
}

int main(){
    char exp[500];
    int result=0;
    scanf("%s", exp);
    result=funtion(&exp[0]);
    printf("%d", result);
}
