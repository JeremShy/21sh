/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 22:10:43 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/08 22:44:53 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char *skip_quotes(char *str, size_t i)
{
	char			*ret;
	size_t		start;
	char				open;

	while(ft_isspace2(str[i]))
		i++;
	start = i;
	ret = ft_strdup("");
	while(!ft_isspace2(str[i]))
	{
		if (is_quote_open(str[i]))
			join_inside_quote(&i, str);
			// while(!ft_isspace2(str[i]) && !is_quote_open(str[i]) && str[i])
			// 	i++;
			// if (ft_isspace2(str[i]))
			// {
			// 	i--;
			// 	break;
			// }
		i++;
	}
	if (start != i)
	{
		free(ret);
		ret = ft_strsub(str, start, i - start);
	}
	return(ret);
}
