/*你有 2 個表單,courses和scores。courses有 3 個欄位，sid、student_id、course_id。
scores有 2 個欄位，sid和score。請分析有多少學生被當掉至少一科。
第一行有 2 個整數 m 和 n，代表courses和scores中有多少行。
接著的 m 行是courses的內容。student_id是個非 0 開頭的 8 位數字。sid和scores是個未滿 1000 的正整數。
接著的 n 行是scores的內容。sid是個未滿 1000 的正整數。score是介於 [0, 100] 間的整數。
輸出包含 2 個整數，分別是學生人數和至少有一科被當的學生人數。*/


#include<stdio.h>

int main(){
    int m=0,n=0,i,j;
    scanf("%d %d",&m,&n);
    int course[1000][6];
    for(i=0;i<m;i++){
        scanf("%d %d %d",&course[i][0],&course[i][1],&course[i][2]);    //表格化//
    }
    int people=1,counter=0,student[m];
    student[0]=course[0][1];
    for(i=1;i<m;i++){
        counter = 0;
        for(j=0;j<i;j++){
            if(course[i][1]==course[j][1]){    //計算學生人數//
                counter++;
            }
        }
        if(counter==0){                         //counter判斷是否重複//
            student[people]=course[i][1];
            people++;
        }
    }
    int sid=0,score=0;
    for(i=0;i<m;i++){
        course[i][3]=0;
        course[i][4]=0;
    }
    for(i=0;i<n;i++){                           //總共有幾個成績//
        scanf("%d",&sid);
        for(j=0;j<m;j++){                       //總共有幾個事件//
            if(sid==course[j][0]){                //事件數相符//
                scanf("%d",&score);                //把成績輸進來//
                course[j][3]=course[j][3]+score;
                course[j][4]++;
            }
        }
    }
    int v[people];
    int k,fail=0;
    for(i=0;i<people;i++){
        v[i]=0;
    }
    for(i=0;i<m;i++){
        course[i][5]=course[i][3]/course[i][4];
        for(k=0;k<people;k++){
            if(course[i][5]<60 && course[i][1]==student[k]){
                // fail++;
                v[k]++;
            }
        }
    }
    /*for(i=0;i<people;i++){
        printf("%d %d\n",i,v[i]);
    }*/
    for(i=0;i<people;i++){
        if(v[i]>0){
            fail++;
        }
    }
    printf("%d %d",people,fail);
    return 0;
}