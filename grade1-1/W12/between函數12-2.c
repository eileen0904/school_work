/*��� between ����ӰѼ� a �� b �A��ӰѼƳ��O���V��ƪ����СA
��� between �|�^�ǫ��� a �������� b ���e�Ҧ���ƪ��M�C*/


int between(int *a, int *b)
{
  int sum=0;
  while(b>a){
  	sum=sum+*a;
  	a++;
  }
  return sum;
}
