/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:44:33 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/08 18:47:15 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		is_aggr(size_t *i, char *str)) // vers un fd
{
	if ((str[*i] == '>' && str[*i + 1] == '&' && ft_is_digit(str[*i + 2]))
	{
		*i += 2;
		while (ft_is_digit(str[*i]))
			i++;
		return (1);
	}
	else if (ft_is_digit(str[*i]) && str[*i + 1] == '>' && str[*i + 2] == '&' && ft_is_digit(str[*i + 3]))
	{
		*i += 3;
		while (ft_is_digit(str[*i]))
			i++;
		return (1);
	}
	return (0);
}

int		is_redir(size_t *i, char *str)) // vers un fichier
{
	size_t tmp;

	tmp = *i;
	// if ((str[*i] == '>' || )// == '&' && ft_is_digit(str[*i + 2]))
	// {
	// 	while (ft_isspace2(str[tmp]))
	// 		tmp++;
	// 	if ()
	// 	while (ft_is_digit(str[*i]))
	// 		i++;
	// 	return (1);
	// }
	else if (ft_is_digit(str[*i]) && str[*i + 1] == '>' && str[*i + 2] == '&' && ft_is_digit(str[*i + 3]))
	{
		if ((str[tmp + 1] == '>' && str[tmp + 2] == '>') || str[tmp + 1] == '<' && str[tmp + 2] == '<'))
			tmp += 2;
		else if (str[tmp + 1] == '>' || str[tmp + 1] == '<')
		*i += 3;
		while (ft_is_digit(str[*i]))
			i++;
		return (1);
	}
	return (0);
}

int is_special(char *str, int quote)
{
	if (quote == 1)
		str++;
	if (ft_strnstr(str, ">>", 2) || ft_strnstr(str, "<<", 2) || ft_strnstr(str, "&&", 2) || ft_strnstr(str, "2>", 2) || ft_strnstr(str, "2>>", 3) || str[0] == '|' || str[0] == '>' || str[0] == '<' || str[0] == ';')
		return (1);
	return (0);
}

int	is_aggr(char *str, int quote)
{
	if (quote == 1)
		str++;
	if (ft_strnstr(str, "2>&1", 4) || ft_strnstr(str, "1>&2", 4) || ft_strnstr(str, ">&1", 3) || ft_strnstr(str, ">&2", 3) || ft_strnstr(str, "2>&2", 4) || ft_strnstr(str, "1>&1", 4))
		return (1);
	return (0);
}

int is_quote(char car)
{
	if (car == '\'' || car == '"' || car == '`' ||  car == '(' || car == ')'
		|| car == '[' || car == ']' || car == '{' || car == '}')
		return (1);
	return (0);
}

int 	is_quote_open(char car)
{
	if (car == '\'' || car == '"' || car == '`' || car == '('
		|| car == '[' || car == '{')
		return (1);
	return (0);
}

int 	is_quote_close(char car, char open)
{
	if (car == '\'' && open == '\'')
		return (1);
	else if (car == '"' && open == '"')
		return (1);
	else if (car == '`' && open == '`')
		return (1);
	else if (car == '(' && open == ')')
		return (1);
	else if (car == '[' && open == ']')
		return (1);
	else if (car == '{' && open == '}')
		return (1);
	return (0);
}

int		is_quote_end(t_data *data)
{
	size_t	i;

//	printf("\ncmd : [%s]\n", data->cmd);
//	printf("data->c : %c\n", data->c);
	i = ft_strlen(data->cmd) - data->real_len_cmd;
	while(data->cmd[i])
	{
		if (data->c == '\0')
		{
			if (is_quote_open(data->cmd[i]))
				data->c = data->cmd[i];
		}
		else if (is_quote_close(data->c, data->cmd[i]))
			data->c = '\0';
		i++;
	}
	if (data->c)
		return (1);
	else
		return (0);
}

int	ft_isspace2(char car)
{
	if (car == ' ' || car == '\t' || car == '\v' || car == '\f' || car == '\r')
		return (1);
	return (0);
}
