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
	while (str[tmp + 1] && str[tmp + 2])
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
	char		*boucle_cmd;

	// i = ft_strlen(data->cmd) - data->real_len_cmd;
	i = data->quote_old_index;
	boucle_cmd = ft_strjoin(data->cmd_tmp, data->cmd);
	while(boucle_cmd[i])
	{
		if (data->c == '\0')
		{
			if (is_quote_open(boucle_cmd[i]) && !is_escaped_char(boucle_cmd, i))
				data->c = boucle_cmd[i];
		}
		else if (is_quote_close(data->c, boucle_cmd[i]) && !is_escaped_char(boucle_cmd, i))
		{
			data->c = '\0';
		}
		i++;
	}
	data->quote_old_index = i;
	free(boucle_cmd);
	if (data->c)
	{
		data->quote_or_hd = 0;
		return (1);
	}
	i = data->end_hd;
	boucle_cmd = ft_strjoin(data->cmd_tmp, data->cmd);
	while (data->c == '\0' && boucle_cmd[i])
	{
		if (ft_strnstr(boucle_cmd + i, "<<", 2))
		{
			printf("heredoc detected\n");
			data->command_save = ft_strdup(boucle_cmd);
			data->old_index = data->index;
			i += 2;
			data->c = '<';
			while (ft_isspace2(boucle_cmd[i]))
				i++;
			if (!boucle_cmd[i])
			{
				ft_putstr_fd("21sh: parse error near '\\n'\n", 2);
				return (-1);
			}
			data->key_here = skip_quotes(boucle_cmd, &i, NULL); // On enleve les quotes.
			if (data->key_here == NULL)
			{
				free(boucle_cmd);
				data->key_here = ft_strdup("");
			}
			data->end_hd = i;
			data->cmd_tmp = data->cmd;
			data->cmd = ft_strdup("");
			data->index = -1;
			data->first_line_of_hd = 1;
		}
		i++;
	}
	free(boucle_cmd);
	if (data->c)
	{
		return (1);
	}
	return (0);
}
