//摩斯電碼//

#include<stdio.h>

int main(){
    int i;
    char str[100];
    scanf("%s",str);
    for(i=0;i<=9;i++){
        switch(str[i]){
            case '0':
                printf("----- ");
                break;
            case '1':
                printf(".---- ");
                break;
            case '2':
                printf("..--- ");
                break;
            case '3':
                printf("...-- ");
                break;
            case '4':
                printf("....- ");
                break;
            case '5':
                printf("..... ");
                break;
            case '6':
                printf("-.... ");
                break;
            case '7':
                printf("--... ");
                break;
            case '8':
                printf("---.. ");
                break;
            case '9':
                printf("----. ");
                break;
        }
    }
    return 0;

}