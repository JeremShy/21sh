/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 16:22:40 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/15 20:35:34 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	join_inside_quote(size_t *i, char *str)
{
	size_t	tmp;
	char	open;

	open = str[*i];
	// printf("open : %c\n", open);
	while (is_quote_close(open, str[*i + 1]) == 0 && str[*i + 1])
	{
		str[*i] = str[*i + 1];
		(*i)++;
	}
	tmp = *i;
	while (str[tmp + 2])
	{
		str[tmp] = str[tmp + 2];
		tmp++;
	}
	str[tmp] = '\0';
	// printf("str : =%s=\n", str);
	if (*i == 0 || is_quote_open(str[0]))
		return ;
	(*i)--;
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
			else if (ft_strnstr(data->cmd + i, "<<", 2))
			{
				data->c = '<';
				data->end_hd = i - (ft_strlen(data->cmd) - data->real_len_cmd);
				while (ft_isspace2(data->cmd[i]))
					i++;
				data->key_here = skip_quotes(data->cmd, &tmp, NULL); // On enleve les quotes.
			}
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
