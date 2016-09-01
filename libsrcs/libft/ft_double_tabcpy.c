/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_tabcpy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 01:01:27 by adomingu          #+#    #+#             */
/*   Updated: 2015/10/02 06:07:25 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_double_tabcpy(char **tab)
{
	char	**cp;
	int		i;

	i = 0;
	cp = (char **)malloc(sizeof(char *) * (ft_double_tablen(tab) + 1));
	while (tab && tab[i])
	{
		cp[i] = ft_strdup(tab[i]);
		i++;
	}
	cp[i] = NULL;
	return (cp);
}
