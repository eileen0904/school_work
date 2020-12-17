//函數 trim 會把傳入的字串 dest 中前後的空白字元都移除，//
//所謂的空白字元包含換行，空格以及 tab，然後回傳 dest//


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
