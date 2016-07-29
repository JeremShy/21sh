/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:44:33 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/29 00:04:37 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_empty_border(char *str, size_t beg, size_t end)
{
	size_t i;

	// printf("coord : %zu et %zu. Chaine : [%s]\n", beg, end, str);
	i = beg;
	while(str[i] != '\0' && i <= end)
	{
		if (!ft_isspace2(str[i]))
			return(0);
		i++;
	}
	return (1);
}

int	is_parse_error(char *str)
{
	size_t i;
	int			there_is_a_pipe;

	i = 0;
	// printf("ON ENVOIE [%s]\n", str);
	there_is_a_pipe = 0;
	while (str[i])
	{
		while (ft_isspace2(str[i]))
			i++;
		if (str[i] == '|' || (str[i] == '\0' && there_is_a_pipe))
		{
			printf("121sh: parse error near '|'\n");
			printf("str[i] = %c\n\n", str[i]);
			return (1);
		}
		there_is_a_pipe = 1;
		while (str[i] != '|' && str[i] != '\0')
		{
			if (is_quote_open(str[i]))
				get_pos_after_quote(&i, str);
			else
				i++;
		}
		if (str[i])
			i++;
	}
	return (0);
}

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
