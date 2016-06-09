/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:44:33 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/09 22:53:18 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"


int		is_empty(char *str, size_t *i)
{
	size_t tmp;

	tmp = *i;
	while(str[tmp] != '\0')
	{
		if(!ft_isspace2(str[tmp]))
			return(0);
		tmp++;
	}
	return(1);
}

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
		// if (str[tmp + 2] == 0)
		// 	fd = cmd->fd_in->fd;
		// else if (str[tmp + 2] == 1)
		// 	fd = cmd->fd_out->fd;
		// else if (str[tmp + 2] == 2)
		// 	fd = cmd->fd_err->fd;
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

char	*is_redir(size_t *i, char *str, int jump, t_cmd	*cmd) // vers un fichier
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
		if ((str[tmp + 1] == '>' && str[tmp + 2] == '>') || (str[tmp + 1] == '<' && str[tmp + 2] == '<'))
			tmp += 3;
		else if (str[tmp + 1] == '>' || str[tmp + 1] == '<')
			tmp += 2;
		else
			return (NULL);
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
			// printf("on saute (comme...)\n");
			*i = ret;
		}
		return(1);
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

// int	is_aggr(char *str, int quote)
// {
// 	if (quote == 1)
// 		str++;
// 	if (ft_strnstr(str, "2>&1", 4) || ft_strnstr(str, "1>&2", 4) || ft_strnstr(str, ">&1", 3) || ft_strnstr(str, ">&2", 3) || ft_strnstr(str, "2>&2", 4) || ft_strnstr(str, "1>&1", 4))
// 		return (1);
// 	return (0);
// }

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
