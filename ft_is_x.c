/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:44:33 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/07 16:46:42 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int is_special(char *str, int quote)
{
	if (quote == 1)
		str++;
	if (ft_strnstr(str, ">>", 2) || ft_strnstr(str, "<<", 2) || ft_strnstr(str, "&&", 2) || str[0] == '|' || str[0] == '>' || str[0] == '<' || str[0] == ';')
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
