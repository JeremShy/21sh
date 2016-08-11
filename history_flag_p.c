
#include <sh21.h>

int history_flag_p(char **scmd)
{
  int   j;

  j = 0;
  while (scmd[j] != NULL)
  {
    ft_putstr(scmd[j]);
    ft_putchar('\n');
    j++;
  }
  return (0);
}
