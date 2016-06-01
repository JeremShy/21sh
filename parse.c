/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 19:25:53 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/01 14:36:59 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*quote_mgmt(char en_cours, char *str)
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

int nb_arg(char *av)
{
	size_t	i;
	char		*suite;

	i = 0;
	while (av[i])
	{
		if (is_quote(av[i]))
		{
			if (!(suite = quote_mgmt(av[i], av + i + 1)))
				exit(EXIT_FAILURE); // On attends la fin de l'entree.
			else
			{
				
			}
		}
		i++;
	}
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
