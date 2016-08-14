#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delete_char(char *str, size_t index)
{
  if (str[index])
  {
    while (str[index + 1])
    {
      str[index] = str[index + 1];
      index++;
    }
    str[index] = '\0';
  }
}

int main(void)
{
  char *str;

  str = strdup("0123456789");
  delete_char(str, 3);
  // printf("New str = [%s]\n", str);
  return (0);
}
