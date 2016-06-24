/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 16:22:40 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/24 15:15:28 by jcamhi           ###   ########.fr       */
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
	size_t	tmp;
//	printf("\ncmd : [%s]\n", data->cmd);
//	printf("data->c : %c\n", data->c);
	i = ft_strlen(data->cmd) - data->real_len_cmd;
	tmp = i;
	// printf("AVANT VERIF QUOTE OPEN i vaut [%zu]\n", i);
	while(data->cmd[i])
	{
		if (data->c == '\0')
		{
			if (is_quote_open(data->cmd[i]))
			{
				// printf("-- QUOTE OPEN // data->c = [%c] /// i = [%zu]\n", data->c, i);
				data->c = data->cmd[i];
			}
		}
		else if (is_quote_close(data->c, data->cmd[i]))
		{
			// printf("-- QUOTE CLOSE\n");
			data->c = '\0';
		}
		i++;
	}
	if (data->c)
	{
		// printf("--- QUOTE NON TERMINE /// data->c = [%c]\n", data->c);
		return (1);
	}
	i = data->end_hd;
	printf("TRY TO DETECT HEREDOC [%s]\n", data->cmd + i);
	while (data->c == '\0' && data->cmd[i])
	{
			if (ft_strnstr(data->cmd + i, "<<", 2))
			{
				data->old_index = data->index;
				i += 2;
				data->c = '<';
				while (ft_isspace2(data->cmd[i]))
					i++;
				if (!data->cmd[i])
				{
					ft_putstr_fd("21sh: parse error near '\\n'\n", 2);
					return (-1);
				}
				data->key_here = skip_quotes(data->cmd, &i, NULL); // On enleve les quotes.
				if (data->key_here == NULL)
					data->key_here = ft_strdup("");
				data->end_hd = i;
				data->ancienne_cmd = data->cmd;
				data->cmd = ft_strdup("");
				data->index = 0;
				printf("heredoc detected. key : %s\n", data->key_here);
			}
			i++;
	}
	if (data->c)
		return (1);
	return (0);
}
