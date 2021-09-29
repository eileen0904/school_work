//第一行是 2 個整數 n 和 m, 代表候選人數和選票數。第二行是 m 個整數，代表選票。//
//1 < n < 200。1 <= m <= 1000000。n = m = 0 表示測試結束。//

#include<stdio.h>

int main()
{
    int n,m,i,j,k,t,win,number=0;
    int a[100000],vote[200];
    while(scanf("%d %d",&n,&m))
    {
        number = 0;
        win = 0;
        if(n==m && m==0){break;}

        for(i=1; i<=m; i++)
        {
            scanf("%d",&vote[i]); //票數//
        }
        for(k=1; k<=n; k++)
        {
            a[k]=0;               //候選人//
        }
        for(j=1; j<=m; j++)
        {
            if(vote[j]<=n)        //判斷廢票//
            {
                a[vote[j]]++;     //票存到候選人號碼//
            }
        }
        int counter = 0;
        for(t=1; t<=n; t++)
        {
            if(a[t]>number)       //輸贏//
            {
                win=t;
                number=a[t];
                counter = 0;
            }
            else if (a[t] == number) //平手//
            {
                counter++;
            }
        }

        if(number>m/2)
        {
            printf("Majoritarian winner %d\n",win);
        }
        else if(counter>0)
        {
            printf("No winner\n");
        }
        else
        {
            printf("Plurality winner %d\n",win);
        }
    }
    return 0;
}