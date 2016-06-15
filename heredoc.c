/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 20:37:13 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/15 20:45:37 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char *get_key_heredoc(char *str, size_t i)
{
	size_t		start;

	if (is_quote_open(str[*i]) && !verif_empty_quote(str, i))
		return (NULL);

 	start = *i;
	while(str[*i] && !ft_isspace2(str[*i])
	{
		if (is_quote_open(str[*i]))
		{
			join_inside_quote(i, str);
		}
		(*i)++;
	}
	if (start != *i)
		return(ft_strsub(str, start, *i - start));
	// }
	return(ft_strdup("");
}
