/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 18:45:34 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/18 19:35:13 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int ft_echo(char **scmd, t_env *env)
{
	int				flag;
	int				i;
	int				j;
	char			c;
	char			*str;

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
		if (scmd[i][0] == '$')
		{
			str = find_arg(env, scmd[i] + 1);
			ft_putstr(str);
			free(str);
		}
		else
		{
			while (scmd[i][j])
			{
				if (scmd[i][j] == '\\')
				{
					c = scmd[i][j + 1];
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
						return (1);
					else
						printf("scmd : %c\n", c);
					j++;
				}
				else
					write(1, &scmd[i][j], 1);
				if (scmd[i][j])
					j++;
			}
			if (scmd[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (1);
}
