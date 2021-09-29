#include<stdio.h>

int line(int arr[5][5]){
    int i,j,k,line=0,counter=0;
    for(i=0;i<5;i++){
        if(arr[i][0]+arr[i][1]+arr[i][2]+arr[i][3]+arr[i][4]==5){//橫
            line++;
        }
        if(arr[0][i]+arr[1][i]+arr[2][i]+arr[3][i]+arr[4][i]==5){//直
            line++;
        }
        if(line==1){
            for(j=0;j<5;j++){
                for(k=0;k<5;k++){
                    counter=counter+arr[j][k];
                }
            }
            return counter;
        }
    }
    line=0;
    if(arr[0][0]+arr[1][1]+arr[2][2]+arr[3][3]+arr[4][4]==5){//左上右下
       for(j=0;j<5;j++){
            for(k=0;k<5;k++){
                counter=counter+arr[j][k];
            }
        }
        return counter;
    }
    if(arr[0][4]+arr[1][3]+arr[2][2]+arr[3][1]+arr[4][0]==5){//右上左下
        for(j=0;j<5;j++){
            for(k=0;k<5;k++){
                counter=counter+arr[j][k];
            }
        }
        return counter;
    }
    counter=0;
    return 0;
}

int main(){
    int n, i, j, k, l=0, bingo=0, temp=0, counter=0, b=1, change=0;
    int a[400][400], t[25], check[5][5];
    scanf("%d", &n);
    int stu[n], score[30], grade[30];
    if(1<=n<=30){
        for(i=0;i<5*n;i++){
            for(j=0;j<5;j++){
                scanf("%d", &a[i][j]);
            }
        }
        for(i=0;i<25;i++){
            scanf("%d", &t[i]);
        }
        while(temp<n){
            for(i=0;i<5;i++){
                for(j=0;j<5;j++){
                    check[i][j]=0;
                }
            }
            for(i=0;i<25;i++){
                for(j=l;j<5+l;j++){
                    for(k=0;k<5;k++){
                        if(a[j][k]==t[i]){
                            check[j-l][k]=1;
                            bingo=line(check);
                            if(bingo>1){
                                break;
                            }
                        }
                    if(bingo>1){break;}
                    }
                if(bingo>1){break;}
                }
            if(bingo>1){break;}
            }
            stu[temp]=bingo;
            score[temp]=bingo;
            bingo=0;
            temp++;
            l=l+5;
        }
        grade[0]=score[0];
        //printf("g:%d\n",grade[0]);
        for(i=1;i<n;i++){
            counter=0;
            for(j=0;j<i;j++){
                if(score[i]==score[j]){
                    counter++;
                }
            }
            if(counter==0){
                grade[b]=score[i];
                b++;
            }
        }
        for(i=0;i<b;i++){
            for(j=0;j<b-1-i;j++){
                if(grade[j]>grade[j+1]){
                    change=grade[j+1];
                    grade[j+1]=grade[j];
                    grade[j]=change;
                }
            }
        }
        for(i=0;i<b;i++){
            printf("%d:", grade[i]);
            for(j=0;j<n;j++){
                if(stu[j]==grade[i]){
                    printf(" %d", j+1);
                }
            }
            if(i<b-1)printf("\n");
        }
    }
    return 0;
}
