/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 19:25:53 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/01 15:40:29 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*quote_ends(char en_cours, char *str)
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

int		count(char *str)
{
	int	ret;

	return (ret);
}

int nb_arg(char *av)
{
	size_t	i;
	char		*suite;
	char		*between;
	char		*actuel;

	i = 0;
	actuel = ft_strdup("");
	while (*av)
	{
		if (is_quote(av[i]))
		{
			if (!(suite = quote_ends(av[i], av + i + 1)))
				exit(EXIT_FAILURE); // On attends la fin de l'entree.
			else
			{
				actuel = ft_strjoinaf12(actuel, quote_mgmt(av[i], av + i + 1, (size_t)(suite - (av + i + 1) + 1)));
				av = suite;
			}
		}
		else
		{
			if(ft_isspace(*av))
			{

			}
		}
	av++;
	}
	return (0);
}

int	main(int ac , char **av)
{
	if (ac == 1)
	{
		printf("KAKA\n");
		return (0);
	}
	nb_arg(av[1]);
	printf("CA MARCHE\n");
	return (1);
}