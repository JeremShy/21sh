#include <sh21.h>

int		is_escaped_char(char *str, int index)
{
	int ret;

	ret = 0;
	index--;
	while (index >= 0 && str[index] == '\\')
	{
		ret++;
		index--;
	}
	return (ret % 2);
}

int		is_quote_true_open(char car, char *str, int prec)
{
	if (!is_escaped_char(str, prec))
	{
		if (car == '\'' || car == '"' || car == '`' || car == '('
				|| car == '[' || car == '{')
			return (1);
	}
	return (0);
}

int		is_quote_true_close(char car, char open, char *str, int prec)
{
	if (!is_escaped_char(str, prec))
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
	}
	return (0);
}

int		delete_var(char **str, size_t index, size_t length, char *arg)
{
	char *new_str;

	if (index > 0)
		new_str = ft_strsub(*str, 0, index - 1);
	else
		new_str = ft_strdup("");
	new_str = ft_strjoinaf1(new_str, (*str) + length);
	free(*str);
	free(arg);
	*str = new_str;
	return (1);
}

void	while_arg_add_backslah(char *arg, int *i, int *j, char *ret)
{
	while (arg[*i])
	{
		if (is_quote(arg[*i]) || arg[*i] == '$'
			|| arg[*i] == '!' || arg[*i] == '\\')
		{
			ret[*j] = '\\';
			(*j)++;
		}
		ret[*j] = arg[*i];
		(*j)++;
		(*i)++;
	}
}

char	*arg_add_backslash(char *arg)
{
	size_t		count;
	int			i;
	char		*ret;
	int			j;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (is_quote(arg[i]) || arg[i] == '$'
			|| arg[i] == '!' || arg[i] == '\\')
			count++;
		count++;
		i++;
	}
	ret = malloc(sizeof(char) * (count + 1));
	i = 0;
	j = 0;
	while_arg_add_backslah(arg, &i, &j, ret);
	free(arg);
	ret[j] = '\0';
	return (ret);
}

int		delete_var_and_replace(char **str,
	size_t index, size_t length, char *arg)
{
	char	*new_str;
	size_t	real_length;

	if (index > 0)
		new_str = ft_strsub(*str, 0, index);
	else
		new_str = ft_strdup("");
	arg = arg_add_backslash(arg);
	real_length = ft_strlen(arg);
	new_str = ft_strjoinaf12(new_str, arg);
	new_str = ft_strjoinaf1(new_str, (*str) + length);
	free(*str);
	*str = new_str;
	return (real_length);
}

void	is_var_and_replace(t_data *data, char **str, size_t *index)
{
	size_t	length;
	char	*arg;
	char	tmp_char;
	size_t	index_begin;

	if (!is_escaped_char(*str, *index) && (*str)[*index] == '$')
	{
		index_begin = *index;
		length = *index + 1;
		if ((*str)[*index + 1] == '?')
		{
			length++;
			arg = ft_strdup(ft_itoa_base(data->ret, 10));
			delete_var_and_replace(str, *index, length, arg);
			return ;
		}
		while (ft_isalnum((*str)[length]))
			length++;
		tmp_char = (*str)[length];
		(*str)[length] = '\0';
		arg = find_var_env(data, *str + *index + 1, data->env);
		(*str)[length] = tmp_char;
		if (length - (*index + 1) == 0)
		{
			free(arg);
			return ;
		}
		if (ft_strequ(arg, ""))
		{
			delete_var(str, *index + 1, length, arg);
			*index = index_begin;
			return ;
		}
		else
		{
			delete_var_and_replace(str, *index, length, arg);
		}
		*index = length - (*index + 1);
	}
}

char	*find_subs_in_parsing(t_data *data, char *str, size_t length)
{
	t_history	*list;
	char		*arg;
	char		*pattern;
	int			len;

	if (data->history == NULL)
		return (NULL);
	list = data->history;
	arg = NULL;
	pattern = ft_strsub(str, 0, length);
	len = (int)ft_strlen(pattern);
	while (list)
	{
		if (ft_strnequ(pattern, list->line, len))
		{
			free(pattern);
			return (ft_strdup(list->line));
		}
		list = list->prec;
	}
	free(pattern);
	return (arg);
}

void	delete_subs_and_replace(char **str,
	size_t index, size_t length, char *arg)
{
	char *new_str;

	if (index > 0)
		new_str = ft_strsub(*str, 0, index);
	else
		new_str = ft_strdup("");
	new_str = ft_strjoinaf12(new_str, arg);
	new_str = ft_strjoinaf1(new_str, *str + length);
	free(*str);
	*str = new_str;
}

int		is_subs_and_replace(t_data *data, char **str, size_t *index, int flag)
{
	size_t	length;
	char	*arg;

	length = *index + 1;
	data->flag_enter = 1;
	if (!is_escaped_char(*str, *index) && (*str)[*index] == '!')
	{
		if ((*str)[length] == '!')
		{
			if (data->history != NULL)
				arg = ft_strdup(data->history->line);
			else
				return (0);
			length++;
		}
		else if (ft_isdigit((*str)[length]))
		{
			while (ft_isdigit((*str)[length]))
				length++;
			if ((arg = history_subsitution_nb_arg(data, *str + *index + 1))
				== NULL)
				return (0);
		}
		else
		{
			if (flag == 0)
			{
				while (ft_isspace2((*str)[length]) == 0 && (*str)[length])
					length++;
			}
			else if (flag == 1)
			{
				while (ft_isspace2((*str)[length]) == 0 && (*str)[length] != '"'
					&& (*str)[length])
					length++;
			}
			if (length - (*index + 1) == 0)
			{
				ft_putstr_fd("42sh: incorrect pattern for '!'\n", 2);
				return (0);
			}
			if ((arg = find_subs_in_parsing(data, *str + *index + 1,
				length - (*index + 1))) == NULL)
			{
				ft_putstr_fd("42sh: event not found\n", 2);
				return (0);
			}
		}
		delete_subs_and_replace(str, *index, length, arg);
		(*index)--;
		data->flag_enter = 0;
	}
	return (1);
}

int		is_tilde_and_replace(t_data *data, char **str, size_t *index)
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

int		true_var_and_subs(t_data *data, char **str)
{
	size_t	index;
	char	open_quote;

	index = 0;
	open_quote = '\0';
	while ((*str)[index])
	{
		while (ft_isspace2((*str)[index]))
			index++;
		if (!(*str)[index])
			continue ;
		while ((*str)[index] && !ft_isspace2((*str)[index]))
		{
			if (open_quote == '\0' &&
				is_quote_true_open((*str)[index], *str, index))
				open_quote = (*str)[index];
			else if (open_quote != '\0' && is_quote_true_close((*str)[index], open_quote, *str, index))
				open_quote = '\0';
			else if (open_quote == '\0'
				&& (*str)[index])
			{
				if (is_subs_and_replace(data, str, &index, 0) == 0)
					return (0);
				if (data->flag_enter && (*str)[index])
				{
					is_var_and_replace(data, str, &index);
					if ((*str)[index])
						is_tilde_and_replace(data, str, &index);
				}
			}
			else if (open_quote == '"' && (*str)[index])
			{
				if (is_subs_and_replace(data, str, &index, 1) == 0)
					return (0);
				if (data->flag_enter && (*str)[index])
					is_var_and_replace(data, str, &index);
			}
			if ((*str)[index])
				index++;
		}
	}
	return (1);
}
