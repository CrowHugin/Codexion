#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "parsing/parsing.h"

const Errors ERR  ={
  .err_0 = "Numbers cannot be negatives\n",
  .err_1 = "is not a number\n",
  .err_2 = "You do not have 8 positive ints\n",
};

int main(int argc, char* argv[])
{
  int options[argc];
  int j;
  int i;

  j = 0;
  i = 1;
  while (i != argc)
  {
    if (is_int(argv[i], ERR) == 0)
      options[j] = atoi(argv[i]);
    j++;
    i++;
  }
  if (get_len(options) != 8)
  {
    printf("%s", ERR.err_2);
    exit(1);
  }
  return 0;
} 
