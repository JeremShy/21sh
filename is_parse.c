/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 16:17:58 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/14 18:19:10 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_aggr(size_t *i, char *str, int jump)
{
	size_t tmp;
	int			avant;
	int			apres;

	tmp = *i;
	avant = 1;
	if (str[*i] == '>' && str[*i + 1] == '&' && (ft_isdigit(str[*i + 2]) || str[*i + 2] == '-'))
	{
		(*i) += 2;
		while (ft_isdigit(str[*i]) || str[*i] == '-')
			(*i)++;
		if (!jump)
			*i = tmp;
		return (1);
	}
	else if (ft_isdigit(str[*i]) && str[*i + 1] == '>' && str[*i + 2] == '&' && (ft_isdigit(str[*i + 3]) || str[*i + 3] == '-'))
	{
		(*i) += 3;
		while (ft_isdigit(str[*i]) || str[*i] == '-')
			(*i)++;
		if (!jump)
			*i = tmp;
		return (1);
	}
	return (0);
}

char	*is_redir(size_t *i, char *str, int jump, t_cmd	*cmd)
{
	size_t	tmp;
	char		*quote;

	tmp = *i;
	if ((str[tmp] == '<' && str[tmp + 1] == '<') || (str[tmp] == '>' && str[tmp + 1] == '>'))
		tmp += 2;
	else if (str[tmp] == '<' || str[tmp] == '>')
		tmp++;
	else if (ft_isdigit(str[*i]))
	{
		if ((str[tmp + 1] == '>' && str[tmp + 2] == '>'))
			tmp += 3;
		else if (str[tmp + 1] == '>')
			tmp += 2;
		else
		{
			cmd->p_error = 1;
			// return (NULL);
		}
	}
	if (tmp != *i)
	{
		while (ft_isspace2(str[tmp]))
			tmp++;
		if (is_empty(str, &tmp))
		{
			cmd->p_error = 1;
			return(NULL);
		}
		quote = skip_quotes(str, &tmp, cmd);
		if (!quote)
			quote = ft_strdup("");
		if (jump)
			*i = tmp;
		return (quote);
	}
	return (NULL);
}

int		is_sep(size_t *i, char *str, int jump)
{
	size_t	ret;

	ret = *i;
	if (str[*i] == ';')
		ret++;
	else if (str[*i] == '|')
		ret++;
	else if (ft_strnstr(str + *i, "&&", 2))
		ret += 2;
	if (ret != *i)
	{
		if (jump)
		{
			*i = ret;
		}
		return(1);
	}
	return (0);
}
