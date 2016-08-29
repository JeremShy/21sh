#include "sh21.h"

void	print_cmd_not_found(char *scmd)
{
	ft_putstr_fd("21sh: command not found: ", 2);
	ft_putstr_fd(scmd, 2);
	ft_putchar_fd('\n', 2);
}

// void		print_tab_char(char **tab)
// {
// 	int		i;

// 	i = 0;
// 	while (tab && tab[i])
// 	{
// 		ft_putendl_fd(tab[i], 1);
// 		i++;
// 	}
// }