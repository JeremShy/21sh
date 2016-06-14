/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:44:33 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/14 16:24:16 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_empty(char *str, size_t *i)
{
	size_t tmp;

	tmp = *i;
	while(str[tmp] != '\0')
	{
		if(!ft_isspace2(str[tmp]))
			return(0);
		tmp++;
	}
	return(1);
}

int is_special(char *str, int quote)
{
	if (quote == 1)
		str++;
	if (ft_strnstr(str, ">>", 2) || ft_strnstr(str, "<<", 2) || ft_strnstr(str, "&&", 2) || ft_strnstr(str, "2>", 2) || ft_strnstr(str, "2>>", 3) || str[0] == '|' || str[0] == '>' || str[0] == '<' || str[0] == ';')
		return (1);
	return (0);
}

int	ft_isspace2(char car)
{
	if (car == ' ' || car == '\t' || car == '\v' || car == '\f' || car == '\r')
		return (1);
	return (0);
}
