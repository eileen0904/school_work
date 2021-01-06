/*代表迷宮的二維陣列，請判斷這個迷宮能不能從起點走到終點
1標示障礙物、0標示可以移動的空間。
輸入的第一行會包含一個數字n，代表陣列的大小是 n * n。
接下來的 n 行，每行會有 n 個值，代表陣列的內容。
每個迷宮的入口都是最左上角，出口的是最右下角。
存在一條路徑的話請輸出 "Yes" ，反之則輸出 "No"。*/


#include<stdio.h>

int main(){
    int n,i,j,k;
    scanf("%d",&n);
    int maze[400][400];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&maze[i][j]);
        }
    }
    maze[0][0]=2;
    for(i=0;i<=n*n;i++){
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                if(maze[j][k]==0 && (maze[j-1][k]==2 || maze[j+1][k]==2 || maze[j][k-1]==2 || maze[j][k+1]==2)){
                    maze[j][k]=2;
                }
            }
        }
    }
    if(maze[n-1][n-1]==2){printf("Yes");}
    if(maze[n-1][n-1]==0){printf("No");}

    return 0;
}

