#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int calculator(int n1, char o, int n2){
    switch(o){
        case'+':
            return n1+n2;
        case'-':
            return n1-n2;
        case'*':
            return n1*n2;
        case'/':
            return n1/n2;
    }
}

int main(){
    char exp[100], op[100], first_num[10]={0}, number[10]={0};
    int real_num[100];
    int i, op_counter=0, real_ncounter=0;
    scanf("%[^\n]", exp);
    for(i=0;i<strlen(exp);i++){
        switch(exp[i]){
            case'+':
                op[op_counter]='+';
                op_counter++;
                break;
            case'-':
                op[op_counter]='-';
                op_counter++;
                break;
            case'*':
                op[op_counter]='*';
                op_counter++;
                break;
            case'/':
                op[op_counter]='/';
                op_counter++;
                break;
            case' ':
                break;
            default:
                if(i==0){
                    first_num[0]=exp[0];
                    first_num[1]=exp[1];
                    real_num[real_ncounter]=atoi(first_num);
                    real_ncounter++;
                }
                number[0]=exp[i];
                number[1]=exp[i+1];
                if((number[1]!=' ' && exp[i-1]==' ') || (number[1]==' ' && exp[i-1]==' ')){
                    real_num[real_ncounter]=atoi(number);
                    real_ncounter++;
                }
        }

    }
    if(real_ncounter<2) {
    printf("%d\n", real_num[0]);
    return 0;
    }
    int result=0;
    result=calculator(real_num[0], op[0], real_num[1]);
    for(i=1;i<op_counter;i++){
        result=calculator(result, op[i], real_num[i+1]);
    }
    printf("%d",result);
    return 0;
}

