/*�Ө�Ʒ|�ǤJ�T�Ӿ�ƫ��� a �A b �A c �A
�M��|�N���� a ���᪺���Ӿ�ƥH�Ϋ��� b �᪺���Ӿ�ƨ̷ӥѤp��j�����ǩ�J���� c ����*/


int merger(int *a, int *b, int *c)
{
  int v[10],i,j,temp=0;
  for(i=0;i<5;i++){
    v[i]=*a;
    a++;
  }
  for(i=5;i<10;i++){
    v[i]=*b;
    b++;
  }
  for(i=0;i<10;i++){
    for(j=0;j<9-i;j++){
      if(v[j]>v[j+1]){
        temp=v[j+1];
        v[j+1]=v[j];
        v[j]=temp;
      }
    }
  }
  for(i=0;i<10;i++){
    *c=v[i];
    c++;
  }
}
