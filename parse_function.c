/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 22:10:43 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/09 14:20:42 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int verif_empty_quote(char *str, size_t *i) // ne supprime pas les quotes, si pas ok, renvoi un caractere apres la quote qui close
{
	size_t tmp;

	tmp = *i + 1;
	while (!is_quote_close(str[*i], str[tmp]) && str[tmp])
	{
		if (!is_quote(str[tmp]) && !ft_isspace2(str[tmp]))
			return(1);
		tmp++;
	}
	printf("tmp = %zu and current char = [%c]", tmp, str[tmp]);
	*i = tmp + 1;
	return (0);
}

char *skip_quotes(char *str, size_t *i)
{
	size_t		start;

	if (!verif_empty_quote(str, i))
		return (NULL);
	start = *i;
	while(str[*i] && !ft_isspace2(str[*i]))
	{
		if (is_quote_open(str[*i]))
			join_inside_quote(i, str);
		(*i)++;
	}
	//printf("END OF WORD WITH i = %zu\n", *i);
	if (start != *i)
		return(ft_strsub(str, start, *i - start));
	return(NULL);
}