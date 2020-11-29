/*有一隻蝸牛沿著高度為10公尺的牆從牆底往上爬，
這隻蝸牛每天可以往上爬4公尺，
可是他晚上休息的時候會往下滑3公尺，
在第7天的時候蝸牛可以爬到牆頂。
請寫一個程式要求使用者輸入牆高，
蝸牛每天爬的高度以及往下滑的距離，
計算出在第幾天蝸牛可以爬到牆頂
如果蝸牛永遠都無法爬上牆，則輸出-1*/

#include<stdio.h>

int main(){
    int h,up,down,n;
    scanf("%d %d %d",&h,&up,&down);
    if(up>=h){      //一天爬上牆//
        printf("1");
    }
    else if(up<=down){ //永遠爬不上//
        printf("-1");
    }
    else{
        if((h-up)%(up-down)!=0){
            n=(h-up)/(up-down)+2;
        }
        else{
            n=(h-up)/(up-down)+1;
        }
        printf("%d",n);
    }


    return 0;
}