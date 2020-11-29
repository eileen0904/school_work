//使用者會輸入一個字串，請判斷該字串是否為回文//
//只包含英文字母的字串，請把大小寫視為相同//

#include<stdio.h>
#include<string.h>

int main(){
    char str1[100],str2[100];
    int i,j=0,n,k;
    scanf("%s",str1);
    strcpy(str2,str1);
    n=strlen(str1);
    for(k=0;k<n;k++){
        if(str1[k]<'a'){
            str1[k]=str1[k]+32;
        }
    }
    for(i=0;i<n/2;i++){
        if(str1[i]==str1[n-i-1]){
            j++;
        }
    }
    if(j==i){
        printf("%s is a palindrome.",str2);
    }
    else{
        printf("%s is not a palindrome.",str2);
    }

    return 0;
}