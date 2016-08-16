#include <sh21.h>

int eot(t_cmd *cmd)
{
	putchar_builtin(cmd, 4, 1);
	exec_tcap("mr");
	putchar_builtin(cmd, '%', 1);
	exec_tcap("me");
	exec_tcap("do");
	return (1);
}

int	special_car(char c, t_cmd *cmd)
{
	if (c == 'a')
		putchar_builtin(cmd, '\a', 1);
	else if (c == 'b')
		putchar_builtin(cmd, '\b', 1);
	else if (c == 'f')
		putchar_builtin(cmd, '\f', 1);
	else if (c == 'n')
		putchar_builtin(cmd, '\n', 1);
	else if (c == 'r')
		putchar_builtin(cmd, '\r', 1);
	else if (c == 't')
		putchar_builtin(cmd, '\t', 1);
	else if (c == 'v')
		putchar_builtin(cmd, '\v', 1);
	else if (c == '\\')
		putchar_builtin(cmd, '\\', 1);
	else if (c == 'c')
		return (1);
	return (0);
}

int ft_echo(char **scmd, t_cmd *cmd)
{
	int				flag;
	int				i;
	int				j;
	char			c;
	(void)			c;
	// char			*str;

	i = 0;
	flag = 0;
	while (scmd[i] && scmd[i][0] == '-')
	{
		if (ft_strchr(scmd[i], 'n'))
			flag = 1;
		i++;
	}
	while (scmd[i])
	{
		j = 0;
		while (scmd[i][j])
		{
			if (scmd[i][j] == '\\')
			{
				// j++;
				// if (scmd[i][j] == '\\')
				// {
					c = scmd[i][j + 1];
					if (special_car(scmd[i][j + 1], cmd))
						return (1);
					j++;
				// }
				// else
				// 	putchar_builtin(cmd, scmd[i][j], 1);
			}
			else
				putchar_builtin(cmd, scmd[i][j], 1);
			if (scmd[i][j])
				j++;
		}
		if (scmd[i + 1])
			putchar_builtin(cmd, ' ', 1);
		// }
		i++;
	}
	if (flag == 0)
		putchar_builtin(cmd, '\n', 1);
	// else
		// eot(cmd);
	return (1);
}
