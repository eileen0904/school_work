#include<stdio.h>

void allocArray(int ***p, int m, int n)
{
    *p = (int**)malloc(m*sizeof(int*)); //row
    for(int i=0;i<m;i++){
        (*p)[i] = (int*)malloc(n*sizeof(int));
    }
}

int main(){
    int **array, *a;
    int j, k;
    allocArray(&array, 5, 10);
    for(j = 0;j < 5;j ++)
        for(k = 0;k < 10;k ++)
            array[j][k] = j * 10 + k;
    for(j = 0;j < 5;j ++)
        for(k = 0;k < 10;k ++)
            printf("%p ", &(array[j][k]));
    for(int i = 0; i < 5; i++)
        free(array[i]);
    free(array);
    
    return 0;
}