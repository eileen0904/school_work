//請寫一個程式在許多的整數中找到最大的數跟最小的的數//

#include<stdio.h>

int main(){
    int i,max,min;
    int num;
    scanf("%d", &num);
    max=num;
    min=num;
    while(scanf("%d", &num) != EOF){
    if(num>max){
       max=num;
    }
    if(num<min){
        min=num;
    }
    }
    printf("%d %d",max,min);

    return 0;
}