
#include <sh21.h>

int history_flag_p(t_data *data, char **scmd)
{
  int   j;
  char  *arg;

  if (scmd[0] == NULL)
    return (0);
  else
  {
    j = 0;
    while (scmd[j] != NULL)
    {
      if (scmd[j][0] == '!')
      {
        if ((arg = get_history_substutition(data, scmd[j] + 1)) == NULL)
        {
          ft_putstr_fd("42sh: history: command not found\n", 2);
          return (1);
        }
      }
      else
        arg = scmd[j];
      ft_putstr(arg);
      if (scmd[j][0] == '!')
        free(arg);
      ft_putchar('\n');
      j++;
    }
  }
  return (0);
}
