#include <sh21.h>

int		is_aggr(size_t *i, char *str, int jump)
{
	size_t tmp;

	tmp = *i;
	if ((str[*i] == '>' || str[*i] == '<') && str[*i + 1] == '&' &&\
			(ft_isdigit(str[*i + 2]) || str[*i + 2] == '-'))
	{
		(*i) += 2;
		while (ft_isdigit(str[*i]) || str[*i] == '-')
			(*i)++;
		if (!jump)
			*i = tmp;
		return (1);
	}
	else if (ft_isdigit(str[*i]) && (str[*i + 1] == '>' ||\
				str[*i + 1] == '<') && str[*i + 2] == '&' && \
			(ft_isdigit(str[*i + 3]) || str[*i + 3] == '-'))
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

size_t	is_redir_move_tmp(size_t j, char *str)
{
	size_t		i;

	i = 0;
	if ((str[i] == '<' && str[i + 1] == '<') ||\
			(str[i] == '>' && str[i + 1] == '>'))
		i += 2;
	else if (str[i] == '<' || str[i] == '>')
		i++;
	else if (ft_isdigit(str[j]))
	{
		if ((str[i + 1] == '>' && str[i + 2] == '>'))
			i += 3;
		else if (str[i + 1] == '>')
			i += 2;
	}
	return (i);
}

char	*is_redir(size_t *i, char *str, int jump, t_cmd *cmd)
{
	size_t	tmp;

	tmp = *i;
	tmp += is_redir_move_tmp(*i, str + tmp);
	if (tmp != *i)
	{
		while (ft_isspace2(str[tmp]))
			tmp++;
		if (is_empty(str, &tmp))
		{
			if (cmd)
				cmd->p_error = 1;
			return (NULL);
		}
		skip_quotes_nb_arg(str, &tmp, cmd);
		if (jump)
			*i = tmp;
		return ("KAKA");
	}
	return (NULL);
}

int		is_sep(size_t *i, char *str, int jump, t_cmd *cmd)
{
	size_t	ret;

	ret = *i;
	if (ft_strnequ(str + *i, "||", 2))
		ret += 2;
	else if (ft_strnequ(str + *i, "&&", 2))
		ret += 2;
	else if (str[*i] == ';')
		ret++;
	else if (str[*i] == '|')
		ret++;
	else
		return (0);
	if (is_escaped_char(str, *i))
		return (0);
	if (cmd)
		cmd->sep = def_sep(str + *i);
	if (jump)
		*i = ret;
	return (1);
}
