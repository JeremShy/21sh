#include "sh21.h"

void	print_cmd_not_found(char *scmd)
{
	ft_putstr_fd("21sh: command not found: ", 2);
	ft_putstr_fd(scmd, 2);
	ft_putchar_fd('\n', 2);
}

int		print_pipe_error(void)
{
	ft_putstr_fd("21sh: parse error near '|' or '&'\n", 2);
	return (1);
}
