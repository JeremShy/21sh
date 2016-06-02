/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 19:25:53 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/02 18:39:40 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*pos_quote_end(char en_cours, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == en_cours)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*quote_mgmt(char en_cours, char *str, int taille)
{
	char	*ret;

	ret = (char*)malloc(taille * sizeof(char));
	if (!ret)
		return(NULL);
	ft_strncpy(ret, str, taille - 1);
	ret[taille - 1] = '\0';
	printf("ret : %s\n", ret);
	return(ret);
}

/*
int count(char *str)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (av[i] && av[i] != '|' && av[i] != ';')
	{
		if (is_quote(av[i]))
		{
			suite = pos_quote_end(av[i], av + i + 1)));
			actuel = ft_strjoinaf12(actuel, quote_mgmt(av[i], av + i + 1, (size_t)(suite - (av + i + 1) + 1)));
			i = suite - av;
		}
		i++;
	}
	return (0);
} */

int nb_arg(char *av, char **new_av)
{
	size_t	i;
	size_t	count;
	char		*suite;
	char		*between;
	char		*actuel;
	size_t	tmp;

	i = 0;
	count = 0;
	actuel = ft_strdup("");
	if (av[0] == '|')
	{
		ft_putstr_fd("zsh: parse error near '|'\n", 2);
		return (-1);
	}
	while (av[i])
	{
		while (ft_isspace2(av[i]))
			i++;
		if (!ft_isspace2(av[i]) && av[i] != '\0')
		{
			count++;
			tmp = i;
			while (!ft_isspace2(av[i]) && av[i] != '\0')
			{
				if (av[i] == '|' || av[i] == ';')
				{
					*new_av = av + i;
					return (tmp == i ? count - 1 : count);
				}
				if (is_quote_open(av[i]))
				{
					suite = pos_quote_end(av[i], av + i + 1);
					i = suite - av;
				}
				i++;
			}
		}
	}
	return (count);
}

int	main(int ac , char **av)
{
	size_t	count;
	char		*new_av;
	size_t	i;

	if (ac == 1)
	{
		printf("KAKA\n");
		return (0);
	}
	i = 0;
	while (av[i])
	{
		count = nb_arg(av[1], &new_av);
		if (count == -1)
			//return (NULL);
			return(0);
		//...
		i = new_av - av[1];
	}
	printf("CA MARCHE : %zu\n", i);
	return (1);
}
