//��� trim �|��ǤJ���r�� dest ���e�᪺�ťզr���������A//
//�ҿת��ťզr���]�t����A�Ů�H�� tab�A�M��^�� dest//


#include <string.h>
#include <ctype.h>
char *trim(char *dest)
{
  int index=strlen(dest)-1;
  while(isspace(*(dest+index))){
    index--;
  }
  while(isspace(*dest)){
    dest++;
  }
  *(dest+index-1)='\0';
  return dest;
}
