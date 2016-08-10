#include <sh21.h>

int eot()
{
	ft_putchar(4);
	exec_tcap("mr");
	ft_putchar('%');
	exec_tcap("me");
	exec_tcap("do");
	return (1);
}

int	special_car(char c)
{
	if (c == 'a')
		ft_putchar('\a');
	else if (c == 'b')
		ft_putchar('\b');
	else if (c == 'f')
		ft_putchar('\f');
	else if (c == 'n')
		ft_putchar('\n');
	else if (c == 'r')
		ft_putchar('\r');
	else if (c == 't')
		ft_putchar('\t');
	else if (c == 'v')
		ft_putchar('\v');
	else if (c == '\\')
		ft_putchar('\\');
	else if (c == 'c')
		return (eot());
	return (0);
}

int ft_echo(char **scmd)
{
	int				flag;
	int				i;
	int				j;
	char			c;
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
		// if (scmd[i][0] == '$')
		// {
		// 	str = find_arg(env, scmd[i] + 1);
		// 	ft_putstr(str);
		// 	free(str);
		// }
		// else
		// {
		while (scmd[i][j])
		{
			if (scmd[i][j] == '\\')
			{
				j++;
				if (scmd[i][j] == '\\')
				{
					c = scmd[i][j + 1];
					if (special_car(c))
						return (1);
					j++;
				}
				else
					write(1, &scmd[i][j], 1);
			}
			else
				write(1, &scmd[i][j], 1);
			if (scmd[i][j])
				j++;
		}
		if (scmd[i + 1])
			write(1, " ", 1);
		// }
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	else
		eot();
	return (1);
}
