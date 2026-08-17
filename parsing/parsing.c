#include <stdio.h>
#include <string.h>
#include "../errors.h"

int get_len(int *ptr_tab)
{
  int i=0;
  while (ptr_tab[i] != '\0')
    i++;
  return i;
}

int is_int(char* src, Errors Err)
{
  int len = strlen(src);

  for (int j=0; j<len; j++)
  {
    if (src[0] == '-')
    {
      printf("%s", Err.err_0);
      return 1;
    }else if(src[j] < 48 || src[j] > 57)
    {
      printf("%s", Err.err_1);
      return 1;
    }
  }
  return 0;
}
