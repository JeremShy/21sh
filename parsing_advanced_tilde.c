/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_advanced_tilde.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:30:26 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 17:30:33 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int			is_tilde_and_replace(t_data *data, char **str, size_t *index)
{
	char	*home;
	char	*tmp;

	if (((*str)[*index] == '~' && !is_escaped_char(*str, *index) &&
		(ft_isspace2((*str)[*index]) || (*str)[*index + 1] == '/'
		|| (*str)[*index + 1] == '\0')))
	{
		home = find_var_env(data, "HOME", data->env);
		if (home)
		{
			(*str)[*index] = '\0';
			tmp = ft_strjoinaf1(ft_strjoin(*str, home), *str + *index + 1);
			free(*str);
			*str = tmp;
			(*index) += ft_strlen(home);
		}
		free(home);
	}
	return (1);
}
